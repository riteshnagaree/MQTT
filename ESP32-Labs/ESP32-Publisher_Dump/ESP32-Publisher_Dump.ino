/*
 * 
 * This is sample code written for PG-DESD students of ACTS Batch to work with MQTT protocol
 * 
 */
#include <WiFi.h>
#include <PubSubClient.h>    
const char* ssid =   "forestiot";                          //ssid - service set Identifier (Replace it with your ssid name)
const char* password =  "sidver1234";                     // replace with ssid paasword
const char* mqttServer = "192.168.1.7";                  // broker address - replace it with your broker address/cloud broker - test.mosquitto.org
const int   mqttPort = 1883;                            // broker port number
const char* clientID = "techemotes";                   // client-id
const char* channelName1 = "teche/patient/temperature"; // topic names
const char* channelName2 =  "teche/patient/humidity";   
char* humidity;
char* temperature;
WiFiClient MQTTclient;
PubSubClient client(MQTTclient);
long lastReconnectAttempt = 0;
boolean reconnect()
{
  if (client.connect(clientID)) {
    //client.subscribe(channelName); // Subscribe to channel.
    Serial.println("Subscribed");
  }
  return client.connected();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect...");
  WiFi.begin(ssid, password); // Connect to WiFi.
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Couldn't connect to WiFi.");
  }
  client.setServer(mqttServer, mqttPort); // Connect to broker
  Serial.println("Connected to Broker");
  lastReconnectAttempt = 0;
}
void loop() {
  if (!client.connected())
  {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) { // Try to reconnect.
      lastReconnectAttempt = now;
      if (reconnect())
      { // Attempt to reconnect.192.168.1.5
        lastReconnectAttempt = 0;
      }
    }
  }
  else 
  { // Connected.
    client.loop();
    float h = 90;
    float t = 22;
    delay(2000);
    Serial.println(h);
    Serial.println(t);   
    client.publish(channelName1, String(t).c_str());  //(topicname, payload)
    client.publish(channelName2, String(h).c_str()); 
    Serial.println("Message Published");
    delay(1000);
  }
}
