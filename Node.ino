#include<ESP8266WiFi.h>
#include <NewPing.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Adafruit.io details
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "Tachyon01"
#define AIO_KEY  "19d6e75a354a423a8a64d198eef9cc76"
WiFiClient client;

//To connect to Adafruit server
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish Light = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Light");
Adafruit_MQTT_Publish Humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Humidity");
Adafruit_MQTT_Publish Moisture = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Moisture");
Adafruit_MQTT_Publish Smoke = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Smoke");
Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperature");  

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}

void Wifi()           //Connect to Wifi
{
  WiFi.disconnect();
  delay(1000);
  Serial.println("START");
  WiFi.begin("Tachyon","bepa8139");     //Change to your credentials
  while(!(WiFi.status() == WL_CONNECTED))
  {
    delay(300);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Your IP is ");
  Serial.print(WiFi.localIP().toString());
  
}

void setup()
{
  Serial.begin(9600);
  Wifi();
  MQTT_connect();
  pinMode(D4,OUTPUT);
  digitalWrite(D4,HIGH);
}

int ldr;
int smoke;
int co2;
float hum;
int temp;
int mst;
float val;
String x;

void loop(){
  while(Serial.available()>0)
  {
    val= Serial.parseFloat();
    if(Serial.read()=='\n'){
      Serial.println(val);
      ldr =val;
      Light.publish(ldr);
    }
    val= Serial.parseFloat();
    if(Serial.read()=='\n'){
      Serial.println(val);
      smoke=val;
      Smoke.publish(smoke);
    }
    
    val= Serial.parseFloat();
    if(Serial.read()=='\n'){
      Serial.println(val);
      hum=val;
      Humidity.publish(hum);
    }
    val= Serial.parseFloat();
    if(Serial.read()=='\n'){
      Serial.println(val);
      temp=val;
      Temperature.publish(temp);
    }
    val= Serial.parseFloat();
    if(Serial.read()=='\n'){
      Serial.println(val);
      mst=val;
      Moisture.publish(mst);
    }
    delay(10000);
  } 
}











//#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>
//#include <FirebaseArduino.h>
//
//SoftwareSerial Serial(D2,D3);
//
//#define FIREBASE_HOST "test-68a20.firebaseio.com/"                          // the project name address from firebase id
//#define FIREBASE_AUTH "xxx"                                           //Your API key   
//
//#define WIFI_SSID "Tachyon"                                             // input your home or public wifi name void setup() {
//#define WIFI_PASSWORD "bepa8139"                                    //password of wifi ssid
//
//
//
//void setup(){
//  Serial.begin(9600);
//  Serial.begin(4800);
//  pinMode(D3,INPUT);
//  pinMode(D2,OUTPUT);
//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
//  Serial.print("Connecting to ");
//  Serial.print(WIFI_SSID);
//  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print(".");
//    delay(500);
//  }
//  Serial.println();
//  Serial.print("Connected to ");
//  Serial.println(WIFI_SSID);
//  Serial.print("IP Address is : ");
//  Serial.println(WiFi.localIP());                                            //print local IP address
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
//}
//int ldr;
//int smoke;
//int co2;
//float hum;
//int temp;
//int mst;
//float val;
//String x;
//
//void loop(){
//  while(Serial.available()>0)
//  {
//    val= Serial.parseFloat();
//    if(Serial.read()=='\n'){
//      Serial.println(val);
//      ldr =val;
//    }
//    val= Serial.parseFloat();
//    if(Serial.read()=='\n'){
//      Serial.println(val);
//      smoke=val;
//    }
//    
//    val= Serial.parseFloat();
//    if(Serial.read()=='\n'){
//      Serial.println(val);
//      hum=val;
//    }
//    val= Serial.parseFloat();
//    if(Serial.read()=='\n'){
//      Serial.println(val);
//      temp=val;
//    }
//    val= Serial.parseFloat();
//    if(Serial,.read()=='\n'){
//      Serial.println(val);
//      mst=val;
//    }
//  } 
//   x=String(String(ldr) + ",ldr," + String(smoke) + ",smk," + String(hum) + ",hum," + String(temp)+ ",temp," + String(mst)+ ",mst," );
//    Serial.println(x);
//    Firebase.pushString("GreenHouse", x);
//    delay(5000);
//  }
// 
