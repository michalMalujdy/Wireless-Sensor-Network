
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WebService.h"

#define BAUD_RATE 115200

#define AP_SSID "ONO288B"
#define AP_PASSWORD "BVfc587uZweM"

#define INTERVAL 4000
#define SENSOR_PIN 0

#define ROUTER_NODE_HOSTNAME "192.168.1.41"
#define ROUTER_NODE_PORT "80"
#define ROUTER_NODE_ENDPOINT "data/sensor"

unsigned long lastMillis;

void setup()
{
    pinMode(SENSOR_PIN, INPUT);
    Serial.begin(BAUD_RATE);

    delay(10000); // Time to open terminal for debugging

    IPAddress ip(192, 168, 1, 44);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    WebService::ConnectToAccessPointDinamically(AP_SSID, AP_PASSWORD, ip, gateway, subnet);
}

void loop()
{
    if(millis() - lastMillis > INTERVAL)
    {
        lastMillis = millis();

        if(digitalRead(SENSOR_PIN))
        {
            Serial.println("light");
        }
        else
        {
            Serial.println("dark");
        }

        SendLightReading();
    }
}

void SendLightReading()
{
    String payload = CreatePayload();
    String url = WebService::ConcatUrlHttp(
        ROUTER_NODE_HOSTNAME,
        ROUTER_NODE_PORT,
        ROUTER_NODE_ENDPOINT);

    WebService::PostJson(url, payload);
}

String CreatePayload()
{
    DynamicJsonBuffer JSONbuffer;
    JsonObject& root = JSONbuffer.createObject();

    root["DeviceId"] = 3;
    root["Value"] = digitalRead(SENSOR_PIN);
    root["DataType"] = 1;

    String json;
    root.printTo(json);

    return json;
}