#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


 
#define DHTPIN 13            // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11       // Type of DHT sensor (DHT11 or DHT22)
#define MQ135_PIN A3        // Analog pin for the MQ-135 sensor
#define RAIN_SENSOR_PIN 2   // Digital pin for the rain sensor
#define SOIL_MOISTURE_PIN A0 // Analog pin for the soil moisture sensor
#define FLAME_SENSOR_PIN 8   // Digital pin for the temperature sensor
#define NEXT_BUTTON_PIN 12    // Digital pin connected to the "Next" button
#define PREV_BUTTON_PIN 5// Digital pin connected to the "Previous" button

DHT dht(DHTPIN, DHTTYPE);
int nextButtonState = 0;
int prevButtonState = 0;
int currentSensor = 1; // Default sensor is DHT11


void setup() {
  Serial.begin(9600);
  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistors
  pinMode(PREV_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistors
  dht.begin();
  pinMode(RAIN_SENSOR_PIN, INPUT);

// Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  //display.display();
  //delay(1000);  // Pause for 2 seconds
  display.clearDisplay();
  displayCurrentSensor();
}

void loop() {
  // Read the button states
  nextButtonState = digitalRead(NEXT_BUTTON_PIN);
  prevButtonState = digitalRead(PREV_BUTTON_PIN);

  if (nextButtonState == LOW) {
    // Move to the next sensor when the "Next" button is pressed
    currentSensor++;
    if (currentSensor > 5) {
      currentSensor = 1;
    }
    displayCurrentSensor();
    delay(500); // Debounce delay
  } else if (prevButtonState == LOW) {
    // Move to the previous sensor when the "Previous" button is pressed
    currentSensor--;
    if (currentSensor < 0) {
      currentSensor = 5;
    }
    displayCurrentSensor();
    delay(500); // Debounce delay
  }

  // Read and display sensor data based on the currentSensor value
  switch (currentSensor) {
    case 1:
      readDHT11();
      break;
    case 2:
       readMQ135();
      break;
    case 3:
      readRainSensor();
      break;
    case 4:
      readSoilMoisture();
      break;
    case 5:
      readFlameSensor();
      break;
    default:
      break;
  }
}

void displayCurrentSensor() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Sensor: ");
  display.print(currentSensor);
  display.setCursor(0, 1);
  display.print("Reading: ");
  display.print(sensorName(currentSensor));
}

String sensorName(int sensor) {
  switch (sensor) {
    case 1:
      return "DHT11 Temp & Hum";
    case 2:
      return "MQ-135 Air Qual";
    case 3:
      return "Rain Sensor";
    case 4:
      return "Soil Moisture";
    case 5:
      return "Flame Sensor";
      
    default:
      return "Unknown";
      
  }
}

void readDHT11() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("DHT11 Temp: ");
  display.print(temperature);
  display.println("C");
  display.print("Humidity: ");
  display.print(humidity);
  display.println("%");
  display.display();
  
  Serial.print("DHT11 Sensor - Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  delay(1000);
}

void readMQ135() {
  int analogValue = analogRead(MQ135_PIN);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("MQ-135 Air Quality");
  display.setCursor(1, 40);
  display.print("Value: ");
  display.print(analogValue);
  display.display();
  
  Serial.print("MQ-135 Sensor - Air Quality: ");
  Serial.println(analogValue);
  
  delay(1000);
}

void readRainSensor() {
  int rainValue = digitalRead(RAIN_SENSOR_PIN);
  

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  if (rainValue == LOW) {
    display.print("Rain Detected");
    Serial.println("Rain Detected");
  } else {
    display.print("No Rain");
    Serial.println("No Rain");
  }
  display.display();
  
  delay(1000);
}

void readSoilMoisture() {
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Soil Moisture: ");
  display.setCursor(0, 40);
  display.print("Value: ");
  display.print(soilMoisture);
  display.display();
  
  Serial.print("Soil Moisture Sensor - Moisture Level: ");
  Serial.println(soilMoisture);
  
  delay(1000);
}

void readFlameSensor() {
  int flameValue = digitalRead(FLAME_SENSOR_PIN);

 display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  if (flameValue == LOW) {
     
    display.print("Flame Detected");
    Serial.println("Flame Detected");
  } else {
    
    display.print("No Flame");
    Serial.println("No Flame");
  }
  display.display();
  delay(1000);
}
