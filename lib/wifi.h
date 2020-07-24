#include <WiFi.h>

void wifi_connect(char* ssid, char* password)
{
    WiFi.begin(ssid, password);

    Serial.print("\nConnecting to ");
    Serial.print(ssid);
    Serial.print(" ...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.print("\n\nSuccessfully connected to ");
    Serial.println(ssid);

    Serial.print("Device's IP address: ");
    Serial.println(WiFi.localIP());
}