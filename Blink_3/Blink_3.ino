/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// most launchpads have a red LED
#define LED RED_LED

//see pins_energia.h for more LED definitions
//#define LED GREEN_LED
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);
  pinMode(31, OUTPUT);  //Vert
  pinMode(32, OUTPUT);  //Bleu
  pinMode(33, OUTPUT);  //Rouge
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(32, HIGH);
  delay(1000);
  digitalWrite(32, LOW);
  digitalWrite(33, HIGH);
  delay(1000);
  digitalWrite(33, LOW);
  digitalWrite(31, HIGH);
  delay(1000);
  digitalWrite(33, HIGH);
  delay(1000);
  digitalWrite(33, LOW);
  digitalWrite(31, LOW);

}
