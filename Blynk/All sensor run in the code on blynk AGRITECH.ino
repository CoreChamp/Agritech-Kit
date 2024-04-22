#define BLYNK_TEMPLATE_ID "TMPL38XMR4mpm"
#define BLYNK_TEMPLATE_NAME "Agritech"
#define BLYNK_AUTH_TOKEN "f35disXgUCDWK-7OVT1rhCpOSTViCBX1"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX
WidgetLCD lcd(V2);
 //MQ135 Sensor
int gasSensor = A3;

// Flame Sensor
int flamePin = 8;

// Rain Sensor
int rainPin = 2;

// Soil Moisture Sensor
int soilMoisturePin = 10;
//MOTOR
int motorpin = 3;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Deepak'siPhone";
char pass[] = "deepak4010";


// Your ESP8266 baud rate:
#define ESP8266_BAUD 4800

ESP8266 wifi(&EspSerial);
#include "DHT.h"
#define DHTPIN 13 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
float t, h;

BlynkTimer timer;
int flame;
int rain;
int soilMoisture;

void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature();

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "INNOVA8"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
 
}
void sendflame(){
  int flameValue = digitalRead(flamePin);
  if(flameValue==1){
     flame=0;
  }
  else{
     flame=1;
  }
  
}
void sendrain(){
  int rainValue = digitalRead(rainPin);

  if(rainValue==1){
     rain=0;
  }
  else{
     rain=1;
  }
  
}
void sendsoil(){
 int soilMoistureValue = digitalRead(soilMoisturePin);

  if(soilMoistureValue==1){
     soilMoisture=0;
  }
  else{
     soilMoisture=1;
  }
  
}

void setup()
{
  // Debug console
  Serial.begin(4800);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
   Blynk.begin(auth, wifi, ssid, pass);
   Serial.println(t);
   pinMode(flamePin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(A0,INPUT);
  pinMode(motorpin,OUTPUT);
  digitalWrite(motorpin,LOW);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(100L, sendSensor);
  timer.setInterval(100L, sendflame);
  timer.setInterval(100L, sendrain);
  timer.setInterval(100L, sendsoil);
}


void loop()
{
  Blynk.run();
   float airQuality = analogRead(A3);
//gasSensor.getPPM();

  // Read flame sensor value (HIGH indicates flame detected)
//  int flameValue = digitalRead(flamePin);
//
//  // Read rain sensor value (HIGH indicates no rain)
//  int rainValue = digitalRead(rainPin);

  // Read soil moisture sensor value
 // int soilMoistureValue = digitalRead(soilMoisturePin);

  // Send sensor data to Blynk app
//  Blynk.virtualWrite(V1, temperature);
//  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, airQuality);
  Blynk.virtualWrite(V4, flame);
  Blynk.virtualWrite(V5, rain);
  Blynk.virtualWrite(V6, soilMoisture);

  delay(1000); 
  timer.run();
}
