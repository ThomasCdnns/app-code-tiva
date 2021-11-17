
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(31, OUTPUT);  //Vert
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(31, HIGH);
  int sensorValue = analogRead(A3);
  int voltage = sensorValue * (3.3 / 4096.0);
  Serial.println(sensorValue);
  delay(50);
}
