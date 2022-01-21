#define  RCV_TIM_LIMIT  10000000
#define MY_LEDV   33
#define MY_LEDJ   33 
#define MY_INPUT  18
#define GIL_SW2  11
#define GIL_SW1  12
#define GIL_BUTTON 10


#define BUF_SIZE  500     // size of the buffer containing the input samples. Must be greater than the order of the filters + K

#define KP 50            // number of samples for the estimation of the signal power

#define R_SIZE 500
#define alpha 0.5

const float S = 0.000568;          // Threshold applied to the signal power  for the signal detection

float buf[BUF_SIZE];      // Buffer containing the input samples
float pIn;                // input power

// ECG detection variables

//Filtered Signal storage
double data_filtered[] = {0, 0};
const int k = 1;

//maximum detection
float temp_r = 0;
float temp_s = 0;
float margin_r = 5;
float temp_time_r = 0 ;
float initial_value = 0;
bool isSignal = 0;


//R's storage
float r[R_SIZE];
float r_time[R_SIZE];
int rn = 0;

//pulse rate (ECG calculation)
float t_sum = 0;
float heart_rate = 0;

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
    buf[i] = buf[i-1];
  }
  
  // ... and acquire the new sample
  current_time = micros() ;
  while (current_time < next_sample_time)
  {
    current_time = micros();
  }

  // Define the next sampling time
  next_sample_time += (unsigned long)Ts;

  //Low Pass filter
  data_filtered[k] = alpha * buf[0] + (1 - alpha) * data_filtered[k-1];
  data_filtered[k-1] = data_filtered[k];

  Serial.println((float) analogRead(MY_INPUT) - 2048.0);

  if ((buf[0] > 0) && (isSignal = 0)){
    initial_value = data_filtered[k];
    isSignal = 1;
  }

  else if (isSignal = 1){
    // Detect temp R and temp S
  if (temp_r < data_filtered[k] && (micros()-temp_time_r)>0.300){
    temp_r = data_filtered[k];
    temp_time_r = micros();
  }
  if (data_filtered[k] < initial_value){
    r[rn] = temp_r;
    r_time[rn] = temp_time_r;
    rn+=1;
  }
  }

  for (i = 0; i < rn; i++)
  {
    float t_sum = r_time[i];
  }
  heart_rate = t_sum / rn;

}
