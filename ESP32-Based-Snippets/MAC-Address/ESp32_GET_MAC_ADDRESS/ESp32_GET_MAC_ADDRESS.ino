/*
 * GET THE MAC Address of ESP32
 * GET it Registered with ACTS AP
 * 
 */

#include <WiFi.h>
void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}
 
void loop()
{
  //Do Nothing
}
