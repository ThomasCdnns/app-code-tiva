int DHpin = A3;
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
void setup () {
  Serial.begin (9600);
  pinMode (DHpin, OUTPUT);
}
void loop () {
  start_test ();
  Serial.print ("Current humdity =");
  Serial.print (dat [0], DEC);
  Serial.print ('.');
  Serial.print (dat [1], DEC);
  Serial.println ('%');
  Serial.print ("Current temperature =");
  Serial.print (dat [2], DEC);
  Serial.print ('.');
  Serial.print (dat [3], DEC);
  Serial.println ('C');
  delay (700);
}
