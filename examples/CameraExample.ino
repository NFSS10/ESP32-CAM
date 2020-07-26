#include "camera.h"
#include "wifi.h"
#include "http_client.h"

const int intervalMS = 15000;
unsigned long lastSentMS = 0;

void setup()
{
    Serial.begin(115200);

    wifi_connect("Rede", "rede_password");
    initCamera();

    sendPhotoToServer();
    lastSentMS = millis();
}

void loop()
{
    if (millis() - lastSentMS >= intervalMS)
    {
        sendPhotoToServer();
        lastSentMS = millis();
    }
}

void sendPhotoToServer()
{
    camera_fb_t *fb = NULL;
    fb = takePhoto();
    if (!fb)
    {
        Serial.println("Failed to take a photo :(");
        return;
    }

    response post_res = http_post_jpg("192.168.1.68", 3000, "/fileUpload", fb->buf, fb->len, "esp_photo.jpg");
    freeCameraResources(fb);

    Serial.print("\nStatus code: ");
    Serial.println(post_res.status_code);
    Serial.print("Response:");
    Serial.println(post_res.body);
}
