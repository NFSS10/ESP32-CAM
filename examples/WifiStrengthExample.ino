#include "lib/camera.h"
#include "lib/http_client.h"
#include "lib/wifi.h"

// ESP32 setup
#define GREEN 14 // GPIO 14
#define BLUE 2   // GPIO 2
#define RED 15   // GPIO 15

// Network setup
#define WIFI_SSID "Rede"
#define WIFI_PASSWORD "rede_password"

void setup()
{
    Serial.begin(115200);

    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(RED, OUTPUT);

    wifi_connect(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("\nTesting WIFI strength");
}

void loop()
{
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);

    // tries to reconnect to network
    if (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(GREEN, HIGH);
        digitalWrite(BLUE, HIGH);
        digitalWrite(RED, HIGH);
        wifi_connect(WIFI_SSID, WIFI_PASSWORD);
    }

    // wifi strength, the higher the number the better
    // best to worst: green, blue, red
    long rssi = WiFi.RSSI();
    Serial.print("RSSI: ");
    Serial.print(rssi);

    if (rssi > -55)
    {
        Serial.println(" GREEN");
        digitalWrite(GREEN, HIGH);
    }
    else if (rssi > -70)
    {
        Serial.println(" BLUE");
        digitalWrite(BLUE, HIGH);
    }
    else
    {
        Serial.println(" RED");
        digitalWrite(RED, HIGH);
    }

    delay(500);
}