#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

SoftwareSerial NodeMCU(D2,D3);

#define FIREBASE_HOST "test-68a20.firebaseio.com/"                          // the project name address from firebase id
#define FIREBASE_AUTH "xxx "                                           //Your API key   

#define WIFI_SSID "Tachyon"                                             // input your home or public wifi name void setup() {
#define WIFI_PASSWORD "bepa8139"                                    //password of wifi ssid



void setup(){
  Serial.begin(9600);
  NodeMCU.begin(4800);
  pinMode(D3,INPUT);
  pinMode(D2,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
}
int ldr;
int smoke;
int co2;
float hum;
int temp;
int mst;


void loop(){
  while(NodeMCU.available()>0)
  {
    val= NodeMCU.parseFloat();
    if(NodeMCU.read()=='\n'){
      Serial.println(val);
      ldr =val;
    }
    val= NodeMCU.parseFloat();
    if(NodeMCU.read()=='\n'){
      Serial.println(val);
      smoke=val;
    }
    val= NodeMCU.parseFloat();
    if(NodeMCU.read()=='\n'){
      Serial.println(val);
      co2=val;
    }
    val= NodeMCU.parseFloat();
    if(NodeMCU.read()=='\n'){
      Serial.println(val);
      hum=val;
    }
    val= NodeMCU.parseFloat();
    if(NodeMCU.read()=='\n'){
      Serial.println(val);
      temp=val;
    }
    val= NodeMCU.parseFloat();
    if(NodeMCU.read()=='\n'){
      Serial.println(val);
      mst=val;
    }
  } 
   x=String(String(ldr) + ",ldr," + String(smoke) + ",smk," + String(co2) + ",co2," + String(hum) + ",hum," + String(temp)+ ",temp," + String(mst)+ ",mst," );
    Serial.println(x);
    Firebase.pushString("GreenHouse", x);
    delay(5000);
  }
} 
