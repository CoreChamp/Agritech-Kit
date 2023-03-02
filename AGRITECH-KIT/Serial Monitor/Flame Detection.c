int sensorvalue = 0; // 0 means Soil having moisture
int buzzer = 6;

void setup() {
  pinMode(8,INPUT);
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  sensorvalue = digitalRead(8);
  Serial.print("Sensor value =");
  Serial.print(sensorvalue);
  Serial.print('\n');
  delay(1000);
  
  if(sensorvalue == 1){
  Serial.println("Warning FIRE");
  digitalWrite(buzzer,HIGH);
  delay(100);
  }
  else{
    Serial.println("No Flames");
    digitalWrite(buzzer,LOW);
      delay(100);
  }
}
