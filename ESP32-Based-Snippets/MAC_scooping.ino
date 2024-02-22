/*
  Packages Required : ArduinoJSON Library 
                    : Arduino Http Client Library
                    
  Version : 02.09.2021
  Business Requirements : Post data using http protocol (POST Method)
 */

#include <WiFi.h>           //Wifi-Library for ESP32
#include <HTTPClient.h>     //HTTP-Client Library for GET, PUT, POST, PATCH and DELETE Resources
#include <ArduinoJson.h>    //Arduino JSON Library
#include <esp_wifi.h>

// Set your new MAC Address
uint8_t newMACAddress[] = {0xCC, 0x50, 0xE3, 0xAB, 0xB9, 0x8C};
const char* ssid = "acts";  //SSID Name to which ESP32 (Teche mote is about to connect to )
const char* password = "";  //SSID Password

/*
 * 
 * Server URL : Docs : https://thingsboard.io/docs/reference/http-api/
 * TB - http(s)://host:port/api/v1/$ACCESS_TOKEN/telemetry
 * 
 * After v1 make sure to keep your access token obtained from the device(manage credentails) section
*/

const char* serverName = "https://demo.thingsboard.io/api/v1/esp32-http-demo/telemetry"; // Server URL

unsigned long lastTime = 0;

// Set timer to 10 seconds (10000) to publish telemetry
unsigned long timerDelay = 10000;

//Prepare JSON Document with a buffer size of 1024 bytes

DynamicJsonDocument sensor_data(1024);  

/*
 * Key : value JSON - Java Script Object Notation (data Exchange format)
 * {
 *    "sensor_name"  : "DHT11",
 *    "temperature"  : 20
 * }
 * 
 * 
 */

void setup() 
{
  Serial.begin(115200); //Serial Port debug message baud rate
  WiFi.mode(WIFI_STA);
  //esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);
  WiFi.begin(ssid, password);   // Start the Wi-Fi
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(10000);
    Serial.println("Not Connected with Access Point ....");
  }

  //If connected print the IP of ESP32 assigned by Router
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer Delay : 10 Second for sending second unit");
}

void loop() 
{

  /*
   * While Using Any sensor assign the value to key
   * sensor_data["temperature"] = gettemperature();
   * 
   */
  
   sensor_data["Location"] = "Pune";   
   sensor_data["Temperature"] = 27;
   sensor_data["Humidity"] = 80;
   sensor_data["Pressure"] = 960;
  
  //Send an HTTP POST request every 10 seconds
  if ((millis() - lastTime) > timerDelay) 
  {
    //Check WiFi connection status : If connected 
    if(WiFi.status()== WL_CONNECTED)
    {
      HTTPClient http;
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      //
      String json;
      /*
       * serializeJson() serializes a JsonDocument to create a minified JSON document, 
       * i.e. a document without spaces or line break between values.
       * 
       */
      serializeJson(sensor_data, json);
      //Post data to the IoT Platform/Teche IoT Platform
      //Return code : Response code : 2.X.X - Success , 4.X.X - Error
      int responsecode = http.POST(json);   //POST method
      Serial.print("HTTP Response code: ");
      Serial.println(responsecode);  // Print the Response code
      // Free resources Close the resuest
      http.end();
    }
    else 
    {
      Serial.println("WiFi Disconnected");
    }
    
    lastTime = millis();
  }
}
