
//Module BT G4E avec MDP 1234
void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop(){
  int sensorValue = analogRead(A3);
  float voltage = sensorValue * (3.3 / 4096.0);
  Serial1.println(voltage);
  delay(1000);
}
