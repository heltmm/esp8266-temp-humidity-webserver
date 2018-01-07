#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid = "Quincy";
const char* password = "7608804370";

#define DHTPIN D4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(115200);
  delay(10);
                                    //Serial connection
  WiFi.begin(ssid, password);   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {

 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http;    //Declare object of class HTTPClient

   http.begin("http://weather-station-.herokuapp.com/devices/1/readings");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
   http.addHeader("api_key", "F52NQQ0Ry1SMTguKQiQO4gtt");

   float h;
   float f;
   h = dht.readHumidity();
   f = dht.readTemperature(true);


   int httpCode = http.POST("{\"temperature\":" + String(f) + ",\"humidity\":" + String(h)  + ",\"device_id\":" + "1" "}");   //Send the request
   String payload = http.getString();                  //Get the response payload

   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload

   http.end();  //Close connection

 }else{

    Serial.println("Error in WiFi connection");

 }

  //delay(30000);  //Send a request every 30 seconds
  delay(300000); //Send a request every 5 minutes

}
