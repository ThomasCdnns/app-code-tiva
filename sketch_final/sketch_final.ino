#include "Iseplogo128.h"

//Detection de son pénible
#define  RCV_TIM_LIMIT  10000000
#define MY_LEDV   33
#define MY_LEDJ   33 
#define MY_INPUT  18 
#define GIL_SW2  11
#define GIL_SW1  12
#define GIL_BUTTON 10

#define BUF_SIZE  500     // size of the buffer containing the input samples. Must be greater than the order of the filters + K
#define KP 50            // number of samples for the estimation of the signal power
#define S 200// to define          // Threshold applied to the signal power  for the signal detection

float buf[BUF_SIZE];      // Buffer containing the input samples
float pIn;                // input power

unsigned long current_time = 0;
unsigned long current_time0 = 0;
unsigned long next_sample_time = 0;
unsigned long delta[20];
unsigned int  Ts = 500;

int compteur;

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
  int i;
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(MY_LEDJ, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  for (i = 0; i < BUF_SIZE; i++)
  {
    buf[i]  = 0;
  }
  pIn = 0;
  compteur = 0;
  delay(1);
  compteur = 0;
  digitalWrite(MY_LEDJ, LOW);
  
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
  DisplayInt(displayValue, 41, int(co2Value/4));
  DisplayString(displayUnit, 41, "ppm");

  //Micro Sensor
  int microValue = analogRead(A3);
  int microValueToDbm = 10*log10(microValue*1000);
  DisplayInt(displayValue,42, microValueToDbm);
  DisplayString(displayUnit, 42, "dBm");

  //Temperature Sensor
  int tempValue = analogRead(A3);
  //int tempFinalValue = tempValue * (3.3 / 4096.0);
  int tempFinalValue = 21;
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
  DisplayInt(displayValue,45, heartRateValue);
  DisplayString(displayUnit, 45, "BPM");

  Serial.println(String(co2Value) + " " + String(microValueToDbm) + " " + String(tempFinalValue) + " " + String(humidityValue) + " " + String(heartRateValue));
  Serial1.println(String(co2Value) + " " + String(microValueToDbm) + " " + String(tempFinalValue) + " " + String(humidityValue) + " " + String(heartRateValue));
  //Détection Son pénible 
  int i,n;
  // Read data : shift the previous samples in the buffer ...
  for (i = BUF_SIZE - 2; i >= 0; i--)
  {
    //buf[i] = buf[i-1]; // To be completed
    buf[i] = buf[i-1];
  }
  // ... and acquire the new sample
  current_time = micros() ;
  while (current_time < next_sample_time)
  {
    current_time  = micros();                  //To be completed
  }
  buf[0] = (float) analogRead(MY_INPUT) - 2048.0;

  // Define the next sampling time
  next_sample_time += (unsigned long)Ts;
  // Update "instantaneous" power
  pIn = 0;
  for (i = 0; i < KP; i++)
  {
    pIn = pIn + pow(buf[i],2);                   //-- to be completed
  }
  pIn = pIn / (float)KP;
  // Display ... sommetimes - be careful, it disturbs the sampling interval
  if (compteur == 200)
  {
    Serial.println(pIn);
    compteur = 0;
  }
  compteur ++;
  // Test the amplitude of the instantaneous power
  if (pIn > S)
  {
       digitalWrite(MY_LEDJ, HIGH);   // Switch on the LED to indicate that an audio signal is detected
  }
  else      //  No useful audio signal detected
  {
      digitalWrite(MY_LEDJ, LOW);
  }

  delay(500);
  
}
