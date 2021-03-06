/*
  ReadAnalogVoltage
  Reads an analog input on pin A3, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A3, and the outside pins to +3V and ground.
  
  Hardware Required:
  * MSP-EXP430G2 LaunchPad
  * Potentiometer
 
  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2231 must use 4800
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin A3:
  int sensorValue = analogRead(A3);
  int voltage = sensorValue * (3.3 / 4096.0); 
  
  // print out the value you read:
  Serial.println(voltage);
}
