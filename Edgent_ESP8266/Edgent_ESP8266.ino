
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLo9MdyFZe"
#define BLYNK_DEVICE_NAME "latihanUAS"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#include "DHT.h"
#define BLYNK_PRINT Serial
#define DHTPIN D4
#define DHTTYPE DHT11
#include <SimpleTimer.h>
//#define BLYNK_DEBUG
int buzzer = D5;
int green = D11;
#define APP_DEBUG


SimpleTimer timer;
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"


BLYNK_WRITE(V5){
  if (param.asInt() == HIGH){
    digitalWrite(buzzer,HIGH);
  }
  else {
    digitalWrite(buzzer,LOW);
    }
}

BLYNK_WRITE(V2){
  analogWrite(D11, param.asInt());
}
BLYNK_WRITE(V1){
  analogWrite(D10, param.asInt());
}
BLYNK_WRITE(V3){
  analogWrite(D9, param.asInt());
}

float volt = 0;
void potensio()
{ 
  int value = analogRead(A0);
  volt = (value/1023.0)*3.3;
  Blynk.virtualWrite(V4,value);
}
  


DHT dht(DHTPIN, DHTTYPE);
float t,h;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
//  if (isnan(h) || isnan(t)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V0, t);
  }


void setup()
{
  digitalWrite(D9,LOW);
  Serial.begin(115200);
  Serial.begin(9600);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(buzzer, OUTPUT);
  dht.begin();
  BlynkEdgent.begin();
  timer.setInterval(500L, sendSensor);
  timer.setInterval(250L, potensio);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}
