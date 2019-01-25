#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

namespace WebService
{
    void ConnectToAccessPointDinamically(
        char* ssid,
        char* password,
        IPAddress ip,
        IPAddress gateway,
        IPAddress subnet,
        bool printToSerial = true)
    {
        WiFi.begin(ssid, password);
        WiFi.config(ip, gateway, subnet);

        if(printToSerial) Serial.print("Waiting to connect...");

        while (WiFi.status() != WL_CONNECTED)
        {
            if(printToSerial) Serial.print('.');

            delay(500);
        }

        if(printToSerial)
        {
            Serial.println();
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
        }
    }

    void PostJson(String url, String payload, bool printToSerial = true)
    {
        if(printToSerial)
        {
            Serial.println("--------------------------------------");
            Serial.print("Sending [POST] to: ");
            Serial.println(url);
            Serial.println("Payload:");
            Serial.println(payload);
            Serial.println("--------------------------------------");
        }

        HTTPClient http;
        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        int httpCode = http.POST(payload);
        String responsePayload = http.getString();

        if(printToSerial)
        {
            if(httpCode == -1)
            {
                Serial.print("Couldnt connect to ");
                Serial.println(url);
            }

            else
            {
                Serial.print("Response HTTP status: ");
                Serial.println(httpCode);
                Serial.println("Response payload:");
                Serial.println(responsePayload);
            }
        }

        http.end();
    }

    JsonObject& Deserialize(String json)
    {
        DynamicJsonBuffer JSONbuffer;
        JsonObject& jsonObj = JSONbuffer.parseObject(json);

        if (!jsonObj.success()) {
            Serial.println("Parsing failed");
        }

        return jsonObj;
    }

    String ConcatUrlHttp(String host, String port, String endpointUri)
    {
        return ("http://" + host + ":" + port + "/" + endpointUri);
    }
}

#endif
