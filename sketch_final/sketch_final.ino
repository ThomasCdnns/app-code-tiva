#include "Iseplogo128.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  InitI2C();
  InitScreen();

  Display(motif);
}

void loop() {
  // read the input on analog pin A3:
  int co2Value = analogRead(A2);
  // print out the value you read:
  //Serial.println(co2Value);

  // read the input on analog pin A3:
  int microValue = analogRead(A0);
  // print out the value you read:
  Serial.println(microValue);
  delay(50); // delay in between reads for stability

  // read the input on analog pin A3:
  int tempValue = analogRead(A3);
  int voltage = sensorValue * (3.3 / 4096.0); 
  
  // print out the value you read:
  Serial.println(voltage);
  
}
