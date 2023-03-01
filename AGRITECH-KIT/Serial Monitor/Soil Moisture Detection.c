int sensorvalue = 0; // 0 means Soil having moisture
int buzzer = 6;

void setup() {
  pinMode(10,INPUT);
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  sensorvalue = digitalRead(10);
  Serial.print('\n');
  delay(1000);
  
  if(sensorvalue == 1){
  Serial.println("Soil needs water");
    digitalWrite(buzzer,HIGH);
  delay(100);
  }
  else{
    Serial.println("Soil is moisturized");
      delay(100);
  }
}
