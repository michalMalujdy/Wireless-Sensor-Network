#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>

#define DEVICE_ID 1

#define GPIO_0 0
#define GPIO_1 1
#define GPIO_2 2

#define AP_SSID "ONO288B"
#define AP_PASSWORD  "BVfc587uZweM"

#define HOST "192.168.1.32"
#define PORT "320"
#define POST_ENDPOINT "api/Data/Light"

ESP8266WiFiMulti WiFiMulti;
 
void setup() {
  InitBoard();

  delay(10000);

  InitWifi(AP_SSID, AP_PASSWORD);
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED)
  {
    PostReadings();    
  } 
  else
  { 
    Serial.println("Disconnected from WiFi. Reconnecting ...");
    InitWifi(AP_SSID, AP_PASSWORD);
  }
 
  delay(5000);  //Send a request every 3 seconds
 
}

void InitBoard()
{
  pinMode(GPIO_2, OUTPUT);
  digitalWrite(GPIO_2, HIGH);
 
  Serial.begin(115200);  
}

void InitWifi(const char* ssid, const char* password)
{      
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}

void PostReadings()
{
  String url = ConcatUrl(HOST, PORT, POST_ENDPOINT);
  PostJson(url, PrepareReadingPayload(DEVICE_ID, 2, 1234));
}

String PrepareReadingPayload(int deviceId, int state, int timestamp)
{
  StaticJsonBuffer<200> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject(); 

  JSONencoder["DeviceId"] = deviceId;
  JSONencoder["State"] = state;
  //JSONencoder["Timestamp"] = timestamp;

  char JSONmessageBuffer[200];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  return JSONmessageBuffer;
}

void PostJson(String url, String payload)
{
  digitalWrite(GPIO_2, HIGH);
  HTTPClient http;
  Serial.println("--------------------------------------");
  Serial.print("Sending [POST] to: ");
  Serial.println(url);
  Serial.println("Payload:");
  Serial.println(payload);
  Serial.println("--------------------------------------");
  
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(payload);
  String responsePayload = http.getString();

  if(httpCode == -1)
  {
    Serial.print("Couldnt connect to ");
    Serial.println(url);
  }

  else
  {
    Serial.print("Response HTTP status: ");
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println("Response payload:");
    Serial.println(responsePayload);    //Print request response payload
  }

  http.end();  //Close connection
  digitalWrite(GPIO_2, LOW);
}

String ConcatUrl(String host, String port, String endpointUri)
{
  return ("http://" + host + ":" + port + "/" + endpointUri);
}
