
#include <ESP8266WiFi.h>    //Biblioteca REDE WIFI
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "ThingSpeak.h"      //Biblioteca do API

const char* ssid     = "ALGAR_Torres2023";
const char* password = "t0rres!001";

unsigned long channel = 2555542; //Channel = variável com ID no ThingSpeak
unsigned long myChannelNumber = 2555542;
const char * myWriteAPIKey = "HM9V6JB10EKLMUZ8";
String apiKey = "HM9V6JB10EKLMUZ8";
String myStatus = "";

WiFiClient client;

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

void setup() {
Serial.begin(115200);

//if (!bme.begin()) {
if (!bme.begin(0x76)) {  
  Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  while (1);
}

 WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {

  // set the fields with the values
  ThingSpeak.setField(1, bme.readTemperature());
  ThingSpeak.setField(2, bme.readPressure());
  ThingSpeak.setField(3, bme.readAltitude(1013.25));

  // set the status
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }


//if (ThingSpeak.getLastReadStatus() == 200) {  
if (client.connect("api.thingspeak.com",80)) {
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(bme.readTemperature());
           postStr +="&field2=";
           postStr += String(bme.readPressure());
           postStr +="&field3=";
           postStr += String(bme.readAltitude(1013.25));
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure());
    Serial.println(" Pa");
    Serial.print("Altitude = ");
    Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
    Serial.println(" m");
    Serial.print(postStr);
  }
  client.stop();
   
  Serial.println("Waiting...\n");    
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);

}
