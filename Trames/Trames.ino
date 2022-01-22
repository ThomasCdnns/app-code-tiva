char buffer[8];
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.setTimeout(10000);

}

void loop() {

  //Trame courante
  byte TRA = 0x01;
  byte OBJ1 = 0x00;
  byte OBJ2 = 0x00;
  byte OBJ3 = 0x00;
  byte OBJ4 = 0x01;
  byte REQ = 0x01;
  byte TYP = 0x03;
  byte NUM1 = 0x00;
  byte NUM2 = 0x01;
  byte VAL1 = 0x00;
  byte VAL2 = 0x00;
  byte VAL3 = 0x02;
  byte VAL4 = 0x12;
  byte TIM1 = 0x00;
  byte TIM2 = 0x01;
  byte TIM3 = 0x02;
  byte TIM4 = 0x05;
  //Serial1.println("100011301002B01251B");
  int byteReceived;
  int byteSend;
  int byteSentSuccessfully;
  uint8_t byteToSend[17] = {
    TRA,
    OBJ1,
    OBJ2,
    OBJ3,
    OBJ4,
    REQ,
    TYP,
    NUM1,
    NUM2,
    VAL1,
    VAL2,
    VAL3,
    VAL4,
    TIM1,
    TIM2,
    TIM3,
    TIM4
  };

  byteSentSuccessfully = Serial1.write(byteToSend, sizeof(byteToSend));
    if (byteSentSuccessfully)
    {
      Serial.println("Wrote to device");

    }

    if (Serial1.available()) {

      byteReceived = Serial1.readBytes( buffer, sizeof(buffer));
      if (byteReceived) {
        Serial.println("She is talking to me");//check on com port

      }
    }


}
