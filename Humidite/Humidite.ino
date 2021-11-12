int DHpin = A3;
byte dat[5];
byte read_data()
{
  byte i = 0;
  byte data = 0;
  for (i = 0; i < 8; i++) {
    while (digitalRead(DHpin) == LOW);
    delayMicroseconds(30);
    if (digitalRead(DHpin) == HIGH)
      data |= (1 << (8 - i));
    while (digitalRead(DHpin) == HIGH);
  }
  return data;
}

void start_test()
{
  digitalWrite(DHpin, LOW);
  delay(30);
  digitalWrite(DHpin, HIGH);
  delayMicroseconds(40);
  pinMode(DHpin, INPUT);
  while (digitalRead(DHpin) == HIGH);
  delayMicroseconds(80);
  if (digitalRead(DHpin) == LOW)
    delayMicroseconds(80);
  for (int i = 0; i < 5; i++)
    dat[i] = read_data();
  pinMode(DHpin, OUTPUT);
  digitalWrite(DHpin, HIGH);
}


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DHpin, OUTPUT);
  start_test();
}

void loop()
{
  Serial.print("Humidity = ");
  Serial.print(dat[0], DEC);
  Serial.print('.');
  Serial.print(dat[1], DEC);
  Serial.println('%');
  Serial.print("Temperature = ");
  Serial.print(dat[2], DEC);
  Serial.print('.');
  Serial.print(dat[3], DEC);
  Serial.println('C');
  delay(500);

}
