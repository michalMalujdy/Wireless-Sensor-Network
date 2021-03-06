#include "WebService.h"
#include "ControllerNodeService.h"

#define GPIO_2 2
#define BAUD_RATE 115200

#define MONITOR_HOST "192.168.1.32"
#define MONITOR_PORT "320"
#define MONITOR_POST_ENDPOINT "api/SensorReadings"

#define LIGHT_SWITCH_HOST "192.168.1.43"
#define LIGHT_SWITCH_PORT "80"
#define LIGHT_SWITCH_POST_ENDPOINT "light/on"

#define MONITOR_BUFFER_CAPACITY 30
#define SEND_MONITOR_BUFFER_INTERVAL_MILLIS 12000

#define AP_SSID "Redmi"
#define AP_PASSWORD ".enter001"

ControllerNodeService* controllerNodeService;

void setup()
{
    Serial.begin(BAUD_RATE);

    delay(10000); // Time to open terminal for debugging

	IPAddress ip(192, 168, 1, 41);
	IPAddress gateway(192, 168, 1, 1);
	IPAddress subnet(255, 255, 255, 0);
    WebService::ConnectToAccessPointDinamically(AP_SSID, AP_PASSWORD, ip, gateway, subnet);

    controllerNodeService = new ControllerNodeService(
		MONITOR_HOST,
		MONITOR_PORT,
		MONITOR_POST_ENDPOINT,
		LIGHT_SWITCH_HOST,
		LIGHT_SWITCH_PORT,
		LIGHT_SWITCH_POST_ENDPOINT,
		MONITOR_BUFFER_CAPACITY,
		SEND_MONITOR_BUFFER_INTERVAL_MILLIS,
		GPIO_2);

	controllerNodeService->SetupServer();
}

void loop()
{
    controllerNodeService->HandleRequests();

    controllerNodeService->SendMonitorBufferIfTimePassed();
}