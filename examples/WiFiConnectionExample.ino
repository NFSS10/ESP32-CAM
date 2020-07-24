#include <WiFi.h>

const char *ssid = "Rede";
const char *password = "rede_password";

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi !!!\n");
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nPing me: ");
        Serial.println(WiFi.localIP());
        delay(15000);
    }
    else
    {
        Serial.println("Connection lost :(");
    }
}