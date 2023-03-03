/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLAQTecbqy"
#define BLYNK_TEMPLATE_NAME "corechamp"
#define BLYNK_AUTH_TOKEN "EAQVIFIeZ_1IMYe8ktPaq_iRwdJQCADy"

#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Enter Wifi Name";
char pass[] = "Enter Password";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

WidgetLCD lcd(V2);

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);



BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH
int sensorvalue = 0;
int buzzer = 6;

void sendSensor()
{
  sensorvalue = digitalRead(2);

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")

  sensorvalue = digitalRead(8);
  Serial.print("Sensor value =");
  Serial.print(sensorvalue);
  Serial.print('\n');
  delay(1000);
  
  if(sensorvalue == 1){
  Serial.println("RAINING");
  lcd.print(5, 1, "RAINING");
  digitalWrite(buzzer,HIGH);
  delay(100);
  }
  else{
    Serial.println("NO RAIN");
    lcd.print(5, 1, "NO RAIN");
    digitalWrite(buzzer,LOW);
      delay(100);
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
   Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

  pinMode(2,INPUT);
  pinMode(buzzer,OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
}
