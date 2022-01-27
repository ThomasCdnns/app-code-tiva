const int BUTTON_PIN = 35;     // the number of the pushbutton pin
bool pressed = false;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(BUTTON_PIN));
  delay(10);
}
