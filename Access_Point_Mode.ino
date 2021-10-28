#include <ESP8266WiFi.h>

IPAddress    apIP(10, 10, 10, 1);   // Private network address: local & gateway
IPAddress    subnet(255, 255, 255, 0);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_AP);
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESP Board");
  if(result == true)
  {
    Serial.println("Ready");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println("Failed!");
  }
  WiFi.softAPConfig(apIP, apIP, subnet);
  Serial.println(WiFi.softAPIP());
}

void loop()
{
}
