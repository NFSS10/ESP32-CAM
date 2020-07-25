#include "wifi.h"
#include "http_client.h"

void setup()
{
  Serial.begin(115200);

  wifi_connect("Rede", "rede_password");
}

void loop()
{
  if ((WiFi.status() == WL_CONNECTED))
  {
    Serial.println("\nTesting GET request ...");
    response get_res = http_get("http://192.168.1.68:3000/");

    Serial.print("Status code: ");
    Serial.println(get_res.status_code);
    Serial.println("Response:");
    Serial.println(get_res.body);

    Serial.println("\nTesting POST request ...");
    response post_res = http_post("http://192.168.1.68:3000/", "POST from ESP32. Hi !");

    Serial.print("Status code: ");
    Serial.println(post_res.status_code);
    Serial.println("Response:");
    Serial.println(post_res.body);
  }

  delay(3000);
}