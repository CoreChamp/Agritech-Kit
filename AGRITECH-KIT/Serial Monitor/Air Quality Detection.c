int sensorvalue = 0;
int buzzer = 6;
void setup() {
  pinMode(A3,INPUT);
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);

}

void loop() {
  sensorvalue = analogRead(A3);
  Serial.print("Sensor value =");
  Serial.print(sensorvalue);
  Serial.print('\n');
  delay(1000);

  if(sensorvalue <33){
    Serial.print(" Very Good air quality");
    }
    else if(sensorvalue <=66){
      Serial.println("Good air quality");
      }
      else if(sensorvalue <=99){
        Serial.println("Normal air quality");
        }
        else if(sensorvalue <=149){
        Serial.println("Poor air quality");
        }
        else if(sensorvalue <=200){
        Serial.println("Very Poor air quality");
        digitalWrite(buzzer,HIGH);
        }
        else if(sensorvalue >200){
        Serial.println("Hazardous air quality");
        digitalWrite(buzzer,HIGH);
        }
        
 }
