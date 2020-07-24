#include "wifi.h"

void setup()
{
    Serial.begin(115200);

    wifi_connect("Rede", "rede_password");
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("\nI'm Still connected, my IP address is: ");
        Serial.println(WiFi.localIP());
        delay(10000);
    }
    else
    {
        Serial.println("Connection lost :(");
    }
}