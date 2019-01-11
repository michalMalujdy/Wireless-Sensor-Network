#include "WebService.h"

#define BAUD_RATE 115200

#define REGULAR_INTERVAL 1000
#define DETECTED_WAIT_MS 10000

#define AP_SSID "ONO288B"
#define AP_PASSWORD "BVfc587uZweM"

#define SERVER_NODE_HOSTNAME "192.168.1.41"
#define SERVER_NODE_PORT "80"
#define SERVER_NODE_ENDPOINT "data/sensor"

void setup() {
    // put your setup code here, to run once:
    pinMode(0, INPUT);
    Serial.begin(BAUD_RATE);

    delay(10000); // Time to open terminal for debugging

    IPAddress ip(192, 168, 1, 42);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    WebService::ConnectToAccessPointDinamically(AP_SSID, AP_PASSWORD, ip, gateway, subnet);
}

void loop() {
    delay(REGULAR_INTERVAL);

    if(digitalRead(0))
    {
        Serial.println("detected");

        SendMovementOccured();

        delay(DETECTED_WAIT_MS);
    }
    else
    {
        Serial.println("NOT detected");
    }
}

void SendMovementOccured()
{
    String payload = CreatePayload();
    String url = WebService::ConcatUrlHttp(
        SERVER_NODE_HOSTNAME,
        SERVER_NODE_PORT,
        SERVER_NODE_ENDPOINT);

    WebService::PostJson(url, payload);
}

String CreatePayload()
{
    DynamicJsonBuffer JSONbuffer;
    JsonObject& root = JSONbuffer.createObject();

    root["DeviceId"] = 2;
    root["Value"] = 1;
    root["DataType"] = 2;

    String json;
    root.printTo(json);

    return json;
}