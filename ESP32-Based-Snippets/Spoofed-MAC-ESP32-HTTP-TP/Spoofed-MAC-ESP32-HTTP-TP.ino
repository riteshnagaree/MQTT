/*
  Packages Required : ArduinoJSON Library 
                    : Arduino Http Client Library
                    
  Version : 01.07.2023
  Maintained By : @bhupendra.jmd@gmail.com, Developed for PG-DESD, Students @ACTS,PUNE
  Business Requirements : Post data using http protocol (POST Method) to Thingspeak (Bulk Upload)

  Additional features:
  Customized MAC using esp_wifi library
  
 */

#include <WiFi.h>           //Wifi-Library for ESP32
#include <HTTPClient.h>     //HTTP-Client Library for GET, PUT, POST, PATCH and DELETE Resources
#include <ArduinoJson.h>    //Arduino JSON Library
#include <esp_wifi.h>

// Set the custom MAC address in case your ESP32 is not regsitered with the acts network
uint8_t newMACAddress[] = {0xf4, 0x96, 0x34, 0x9d, 0xe6, 0x2b};


/*
 * Replaced the ssid and password based on the router credentials
 */
const char* ssid = "forestiot";  //SSID Name to which ESP32 will connect 
const char* password = "sidver1234";  //SSID Password

/*
 * 
 * Docs : Docs : https://in.mathworks.com/help/thingspeak/
 *        (Bulk JSON Data Write API reference)
 *        https://in.mathworks.com/help/thingspeak/bulkwritejsondata.html
 *        HTTP Method : POST
          URL : https://api.thingspeak.com/channels/<channel_id>/bulk_update.json
          Note : Replace the channel id with your account channel Id
          Example: https://api.thingspeak.com/channels/999990/bulk_update.json
 * 
 * API reference:
 * https://api.thingspeak.com/channels/2209618/bulk_update.json
*/

const char* serverName = "https://api.thingspeak.com/channels/2209723456/bulk_update.json"; // Server URL
unsigned long humidity_between_1_to_100;
unsigned long temperature_between_20_30;
unsigned long aqi_between_40_85;
unsigned long lastTime = 0;

// Set timer to 30 seconds (30000) to publish telemetry
unsigned long timerDelay = 30000;

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
  esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);
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
  Serial.println("Timer Delay : 30 Second for sending second unit");
}

void loop() 
{

  /*
   * While Using Any sensor assign the value to key
   * sensor_data["temperature"] = gettemperature();
   * 
   */
   // Random Number generation for sensor simulation
   humidity_between_1_to_100 = random(1,101);
   temperature_between_20_30 = random(20,31);
   aqi_between_40_85 = random(40,86);
         
   /* Update the Write API_KEY HERE */
   
   sensor_data["write_api_key"] = "OJTVRZUUY6AVV7GU";  

   /* field details   */
   
   sensor_data["updates"][0]["delta_t"] = 1;    // mandetory field if not used created_at
   sensor_data["updates"][0]["field1"] = temperature_between_20_30; 
   sensor_data["updates"][0]["field2"] = humidity_between_1_to_100;
   sensor_data["updates"][0]["field3"] =  aqi_between_40_85;
  /*
   * {
        "write_api_key": "ZXP8M07OGEF1GKLX",
        "updates": [
          {
            "delta_t": 1,
            "field1": 86,
            "field2": 67
          }
        ]
    }

   */
  
  //Send an HTTP POST request every 30 seconds (sample interval : 30 seconds)
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
      //Serial.println(json);
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
