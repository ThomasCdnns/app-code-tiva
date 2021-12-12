#define  RCV_TIM_LIMIT  10000000
#define MY_LEDV   33
#define MY_LEDJ   33 
#define MY_INPUT  28 
#define GIL_SW2  11
#define GIL_SW1  12
#define GIL_BUTTON 10


#define BUF_SIZE  500     // size of the buffer containing the input samples. Must be greater than the order of the filters + K

#define KP 50            // number of samples for the estimation of the signal power

#define S O.OOO568//to define          // Threshold applied to the signal power  for the signal detection

float buf[BUF_SIZE];      // Buffer containing the input samples
float pIn;                // input power

unsigned long current_time = 0;
unsigned long current_time0 = 0;
unsigned long next_sample_time = 0;
unsigned long delta[20];
unsigned int  Ts = 500;

int compteur;

void setup() {

  int i;

  // initialize  serial ports:

  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(MY_LEDJ, OUTPUT);
  pinMode(MY_LEDV, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GIL_SW1, INPUT_PULLUP);
  pinMode(GIL_SW2, INPUT_PULLUP);
  pinMode(GIL_BUTTON, INPUT_PULLUP);

  
  for (i = 0; i < BUF_SIZE; i++)
  {
    buf[i]  = 0;
  }
  pIn = 0;
  compteur = 0;
  delay(1);

  compteur = 0;
  digitalWrite(MY_LEDJ, LOW);
  digitalWrite(MY_LEDV, LOW);


  // This part is not necessary. It is a way to check the sampling
  // The values displayed in the monitor must be equal to the  sampling time Ts
  for (i = 0; i<20; i++)
  {
    Serial.println("DEBUT PROGRAMMME");
    delay(1);
  }

  current_time0  = micros();
  next_sample_time = current_time0 + (unsigned long)Ts;
  i = 0;
  while (i<10)
  { 
    current_time  = micros();
    
    while ( current_time < next_sample_time)
    {
      current_time  = micros();
    }
    
    next_sample_time += (unsigned long)Ts;
    buf[i] = (float) analogRead(MY_INPUT) - 2048.0;
    delta[i] = (unsigned int)(current_time - current_time0);
    current_time0  = current_time;
    
    i++;
  }
  
  for (i = 0; i<10; i++)
  {
    Serial.println(delta[i]);
  }
  for (i = 0; i<10; i++)
  {
    Serial.println(buf[i]);
  }

  Serial.println("FIN");
  Serial.println("FIN");
  Serial.println("FIN");

 // End of the "unnecessary" code
  
  digitalWrite(MY_LEDJ, LOW);
  digitalWrite(MY_LEDV, LOW);
}

void loop() {

  int i,n;
 
  // Read data : shift the previous samples in the buffer ...
  for (i = BUF_SIZE - 2; i >= 0; i--)
  {
    buf[i] = buf[i-1]; // To be completed
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
    pIn += buf[i]^2;                   //-- to be completed
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

}
