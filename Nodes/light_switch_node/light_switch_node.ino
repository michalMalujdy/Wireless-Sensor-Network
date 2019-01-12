#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WebService.h"

#define BAUD_RATE 115200

#define AP_SSID "ONO288B"
#define AP_PASSWORD "BVfc587uZweM"

#define SWITCH_ON_INTERVAL 15000
#define LED_PIN 0

ESP8266WebServer server(80);
unsigned long startIntervalMilis = 0;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    Serial.begin(BAUD_RATE);

    delay(10000); // Time to open terminal for debugging

    IPAddress ip(192, 168, 1, 43);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    WebService::ConnectToAccessPointDinamically(AP_SSID, AP_PASSWORD, ip, gateway, subnet);

    SetupServer();
}

void loop()
{
    server.handleClient();

    if(millis() - startIntervalMilis > SWITCH_ON_INTERVAL)
    {
        digitalWrite(LED_PIN, LOW);
    }
}

void SetupServer()
{
    server.on("/light/on", SwitchLightOn);
    server.on("/light/off", SwitchLightOff);
    server.begin();
    Serial.println("Node is listening");
}

void SwitchLightOn()
{
    Serial.println("Endpoint hit: /light/on ");
    startIntervalMilis = millis();
    digitalWrite(LED_PIN, HIGH);

    server.send(200, "text/plain", "OK\r\n");
}

void SwitchLightOff()
{
    Serial.println("Endpoint hit: /light/on ");
    digitalWrite(LED_PIN, LOW);
    server.send(200, "text/plain", "OK\r\n");
}