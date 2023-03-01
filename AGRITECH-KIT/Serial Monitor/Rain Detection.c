int sensorvalue = 0; // 0 means Soil having moisture
int buzzer = 6;

void setup() {
  pinMode(2,INPUT);
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  sensorvalue = digitalRead(2);
  Serial.print("Sensor value =");
  Serial.print(sensorvalue);
  Serial.print('\n');
  delay(1000);
  
  if(sensorvalue == 1){
  Serial.println("RAINING");
  digitalWrite(buzzer,HIGH);
  delay(100);
  }
  else{
    Serial.println("NOT RAINING");
      delay(100);
  }
}
