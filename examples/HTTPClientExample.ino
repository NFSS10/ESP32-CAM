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
    response res = http_get("http://192.168.1.68:3000/");
    
    Serial.print("Status code: ");
    Serial.println(res.status_code);
    Serial.println("Response:");
    Serial.println(res.body);
  }

  delay(3000);
}