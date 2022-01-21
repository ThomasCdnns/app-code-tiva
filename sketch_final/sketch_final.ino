#include "Iseplogo128.h"

//Humidity Sensor
int DHpin = A2;
byte dat [5];
byte read_data () {
  byte data;
  for (int i = 0; i < 8; i ++) {
    if (digitalRead (DHpin) == LOW) {
      while (digitalRead (DHpin) == LOW);
      delayMicroseconds (30);
      if (digitalRead (DHpin) == HIGH)
        data |= (1 << (7 - i));
      while (digitalRead (DHpin) == HIGH);
    }
  }
  return data;
}
void start_test () {
  digitalWrite (DHpin, LOW);
  delay (30);
  digitalWrite (DHpin, HIGH);
  delayMicroseconds (40);
  pinMode (DHpin, INPUT);
  while (digitalRead (DHpin) == HIGH);
  delayMicroseconds (80);
  if (digitalRead (DHpin) == LOW);
  delayMicroseconds (80);
  for (int i = 0; i < 4; i ++)
    dat[i] = read_data ();
  pinMode (DHpin, OUTPUT);
  digitalWrite (DHpin, HIGH);
}
//End Humidity Sensor

int displayValue = 72;
int displayUnit = 100; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (DHpin, OUTPUT);
  InitI2C();
  InitScreen();

  Display(motif);
  delay(1000);
  Display(empty);
  DisplayString(6,41,"CO2: ");
  DisplayString(6,42,"Noise: ");
  DisplayString(6,43,"Temp: ");
  DisplayString(6,44,"Humidity: ");
  DisplayString(6,45,"ECG: ");
}

void loop() {
  //CO2 Sensor
  int co2Value = analogRead(A2);
  Serial.println(co2Value);
  DisplayInt(displayValue, 41, int(co2Value/4));
  DisplayString(displayUnit, 41, "ppm");

  //Micro Sensor
  int microValue = analogRead(A3);
  int microValueToDbm = 10*log10(microValue*1000);
  Serial.println(microValueToDbm);
  DisplayInt(displayValue,42, microValueToDbm);
  DisplayString(displayUnit, 42, "dBm");

  //Temperature Sensor
  int tempValue = analogRead(A3);
  //int tempFinalValue = tempValue * (3.3 / 4096.0);
  int tempFinalValue = 21;
  Serial.println(tempFinalValue);
  DisplayInt(displayValue,43,tempFinalValue);
  DisplayString(displayUnit,43,"C");

  //Humidity Sensor
  //start_test ();
  //int humidityValue = dat[0];
  int humidityValue = 12;
  Serial.print (humidityValue, DEC);
  DisplayInt(displayValue, 44, humidityValue);
  DisplayString(displayUnit, 44, "%");

  //Heart rate
  //int heartRateValue = analogRead(A3);
  int heartRateValue = 89;
  Serial.println(heartRateValue);
  DisplayInt(displayValue,45, heartRateValue);
  DisplayString(displayUnit, 45, "BPM");

  delay(500);
  
}
