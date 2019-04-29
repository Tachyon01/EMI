#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
//# include <SoftwareSerial.h>
//SoftwareSerial ArduinoUno(3,2);

#define Mst A0
#define DHTPIN 7        // Pin which is connected to the DHT sensor.
#define ldr A1
#define smk A2
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
#define pump 6
#define buz 5

float m;
float l;
float s;
float t;
float h;
void setup()
{
  Serial.begin(9600);
//  ArduinoUno.begin(4800);
  dht.begin();
  pinMode(Mst,INPUT);
  pinMode(ldr,INPUT);
  pinMode(smk,INPUT);
  pinMode(buz,OUTPUT);
  pinMode(pump,OUTPUT);
  sensor_t sensor;
}

void loop()
{
  m=analogRead(Mst);
  m=1000-m;
  l=analogRead(ldr);
  s=analogRead(smk);
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  t=event.temperature;
  dht.humidity().getEvent(&event);
  h=event.relative_humidity;

//  Serial.println("Moisture  " + String(m));
//  Serial.println("ldr "+String(l));
//  Serial.println("Air Quality "+String(s));
//  Serial.println("Temperature "+String(t));
//  Serial.println("Humidity  "+String(h));
//  Serial.println('\n');
  if(m>10 && m<250)
  {
    digitalWrite(pump,LOW);
    delay(1000);
    digitalWrite(pump,HIGH);
  }

  if(s>300)
  {
    digitalWrite(buz,HIGH);
  }
  else
  {
    digitalWrite(buz,LOW);
  }
   Serial.print(l);
   Serial.println("\n");
   Serial.print(s);
   Serial.println("\n");
   Serial.print(h);
   Serial.println("\n");
   Serial.print(t);
   Serial.println("\n");
   Serial.print(m);
   Serial.println("\n");
   delay(10000);
}
