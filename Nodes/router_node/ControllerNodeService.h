#ifndef CONTROLLERNODESERVICE_H
#define CONTROLLERNODESERVICE_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WebService.h"
#include "MonitorBufferItem.h"

ESP8266WebServer server(80);

class ControllerNodeService
{
    public:

    String monitorHost;
    String monitorPort;
    String monitorPostEndpoint;
    String lightSwitchHost;
    String lightSwitchPort;
    String lightSwitchEndpoint;
    int monitorBufferCapacity;
    int sendMonitorBufferIntervalMillis;
    int busyLedPin;

    ControllerNodeService(
        String monitorHost,
        String monitorPort,
        String monitorPostEndpoint,
        String lightSwitchHost,
        String lightSwitchPort,
        String lightSwitchEndpoint,
        int monitorBufferCapacity,
        int sendMonitorBufferIntervalMillis,
        int busyLedPin);

    void SetupServer();
    void HandleRequests();
    void SendMonitorBufferIfTimePassed();

    private:

    MonitorBufferItem* monitorBuffer;
    int currentBufferIndex;
    unsigned long lastMonitorBufferSentTime;
    int lastLightValue;
    int lastMovementValue;

    void HandleReceivedSensorData();
    void AddToMonitorBuffer(JsonObject& jsonObj);
    void SendMonitorBuffer();
    int CountReadingsToSend();
    String PreparePayload(MonitorBufferItem* monitorBuffer);
    void AddReadingToArray(JsonArray& readings, int index);
    void ClearMonitorBuffer();
    void SendLightSwitchCommandIfConditionsAreMet();
    void SetLastReadingData();
};

ControllerNodeService::ControllerNodeService(
    String monitorHost,
    String monitorPort,
    String monitorPostEndpoint,
    String lightSwitchHost,
    String lightSwitchPort,
    String lightSwitchEndpoint,
    int monitorBufferCapacity,
    int sendMonitorBufferIntervalMillis,
    int busyLedPin)
{
    this->monitorHost = monitorHost;
    this->monitorPort = monitorPort;
    this->monitorPostEndpoint = monitorPostEndpoint;
    this->lightSwitchHost = lightSwitchHost;
    this->lightSwitchPort = lightSwitchPort;
    this->lightSwitchEndpoint = lightSwitchEndpoint;
    this->monitorBufferCapacity = monitorBufferCapacity;
    this->sendMonitorBufferIntervalMillis = sendMonitorBufferIntervalMillis;
    this->busyLedPin = busyLedPin;

    pinMode(this->busyLedPin, OUTPUT);
    digitalWrite(this->busyLedPin, LOW);

    this->monitorBuffer = new MonitorBufferItem[this->monitorBufferCapacity];
    this->ClearMonitorBuffer();

    lastLightValue = 0;
    lastMovementValue = 0;
}

void ControllerNodeService::SetupServer()
{
    server.on("/data/sensor", [=](){ this->HandleReceivedSensorData(); });
    server.begin();
    Serial.println("Controller is listening");
}

void ControllerNodeService::HandleRequests()
{
    server.handleClient();
}

void ControllerNodeService::SendMonitorBufferIfTimePassed()
{
    unsigned long milisSinceLastMonitorBufferSent = millis() - this->lastMonitorBufferSentTime;

    if(milisSinceLastMonitorBufferSent >= this->sendMonitorBufferIntervalMillis)
    {
        if(this->CountReadingsToSend() > 0)
        {
            this->SendMonitorBuffer();
        }

        this->lastMonitorBufferSentTime = millis();
    }
}

void ControllerNodeService::HandleReceivedSensorData()
{
    if (server.hasArg("plain") == false)
    {
        server.send(404, "text/plain", "Body was empty");
        return;
    }

    String requestBody = server.arg("plain");
    server.send(200, "text/plain", "OK\r\n");

    Serial.println("Received:");
    Serial.println(requestBody);

    JsonObject& jsonObj = WebService::Deserialize(requestBody);
    this->AddToMonitorBuffer(jsonObj);

    SetLastReadingData();

    SendLightSwitchCommandIfConditionsAreMet();
}

void ControllerNodeService::AddToMonitorBuffer(JsonObject& jsonObj)
{
    MonitorBufferItem item = {
        jsonObj["DeviceId"],
        jsonObj["Value"],
        jsonObj["DataType"],
    };

    ++ this->currentBufferIndex;

    if(this->currentBufferIndex >= this->monitorBufferCapacity)
    {
        this->currentBufferIndex = 0;
    }

    this->monitorBuffer[this->currentBufferIndex] = item;
}

void ControllerNodeService::SendMonitorBuffer()
{
    digitalWrite(busyLedPin, HIGH);

    String payload = this->PreparePayload(this->monitorBuffer);
    String destinationUrl = WebService::ConcatUrlHttp(
        this->monitorHost, this->monitorPort, this->monitorPostEndpoint);

    WebService::PostJson(destinationUrl, payload);

    this->ClearMonitorBuffer();

    digitalWrite(busyLedPin, LOW);
}

int ControllerNodeService::CountReadingsToSend()
{
    int readingsToSent = 0;

    for(int i = 0; i < this->monitorBufferCapacity; i++)
    {
        if(this->monitorBuffer[i].DeviceId > 0)
        {
            readingsToSent ++;
        }
    }

    return readingsToSent;
}

String ControllerNodeService::PreparePayload(MonitorBufferItem* monitorBuffer)
{
    DynamicJsonBuffer JSONbuffer;
    JsonObject& root = JSONbuffer.createObject();
    JsonArray& readings = root.createNestedArray("Readings");

    for(int i = 0; i < this->monitorBufferCapacity; i++)
    {
        if(this->monitorBuffer[i].DeviceId != 0)
        {
            this->AddReadingToArray(readings, i);
        }
    }

    String json;
    root.printTo(json);
    return json;
}

void ControllerNodeService::AddReadingToArray(JsonArray& readings, int index)
{
    JsonObject& reading = readings.createNestedObject();

    reading["DeviceId"] = this->monitorBuffer[index].DeviceId;
    reading["Value"] = this->monitorBuffer[index].Value;
    reading["DataType"] = this->monitorBuffer[index].DataType;
}

void ControllerNodeService::ClearMonitorBuffer()
{
    for(int i = 0; i < this->monitorBufferCapacity; i++)
    {
        this->monitorBuffer[i].DeviceId = 0;
    }

    this->currentBufferIndex = 0;
}

void ControllerNodeService::SendLightSwitchCommandIfConditionsAreMet()
{
    int lastReadingType = this->monitorBuffer[this->currentBufferIndex].DataType;

    if(lastReadingType == 2 && this->lastMovementValue && !this->lastLightValue)
    {
        String lightSwitchNodeUrl = WebService::ConcatUrlHttp(
            this->lightSwitchHost,
            this->lightSwitchPort,
            this->lightSwitchEndpoint
        );

        WebService::PostJson(lightSwitchNodeUrl, "");
    }
}

void ControllerNodeService::SetLastReadingData()
{
    MonitorBufferItem lastReading = this->monitorBuffer[this->currentBufferIndex];

    if(lastReading.DataType == 1)
    {
        this->lastLightValue = lastReading.Value;
    }
    else if(lastReading.DataType == 2)
    {
        this->lastMovementValue = lastReading.Value;
    }
}

#endif
