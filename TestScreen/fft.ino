
  // put your setup code here, to run once:
char *p;

// test_fft.cpp : définit le point d'entrée pour l'application console.
//


#include "math.h"

struct cmpx //complex data structure used by FFT
{
float real;
float imag;
};

typedef struct cmpx COMPLEX;


void fft(COMPLEX *Y, int M);

//#define PI 3.14159
#define NFFT 512          // Nombre de point de la fft

COMPLEX in_data[NFFT];
COMPLEX Twiddle[NFFT];





void make_twiddle_array(int fftlen,struct cmpx *Twiddle)
{
int n;
float vn;
for (n=0 ; n<fftlen; n++) //set up DFT twiddle factors
{
vn = (float) (PI*n/fftlen);
Twiddle[n].real = cos(vn);
Twiddle[n].imag = -sin(vn);
}
}

void fft(struct cmpx *Y, int fftlen)
{
COMPLEX temp1,temp2; //temporary storage variables
int i,j,k; //loop counter variables
int upper_leg, lower_leg; //index of upper/lower
//butterfly leg
int leg_diff; //difference between upper/lower leg
int num_stages=0;//number of FFT stages, or iterations
int index, step; //index and step between twiddle factor
COMPLEX *w;


make_twiddle_array(fftlen,Twiddle);
w = Twiddle;
i=1; //log(base 2) of # of points = # of stages
do
{
num_stages+=1;
i=i*2;
} while (i!=fftlen);
leg_diff=fftlen/2; //starting difference between
//upper & lower legs
step=2; //step between values in twiddle.h
for (i=0;i<num_stages;i++) //for M-point FFT
{
index=0;
for (j=0;j<leg_diff;j++)
{
for (upper_leg=j;upper_leg<fftlen;upper_leg+=(2*leg_diff))
{
lower_leg=upper_leg+leg_diff;
temp1.real=(Y[upper_leg]).real + (Y[lower_leg]).real;
temp1.imag=(Y[upper_leg]).imag + (Y[lower_leg]).imag;
temp2.real=(Y[upper_leg]).real - (Y[lower_leg]).real;
temp2.imag=(Y[upper_leg]).imag - (Y[lower_leg]).imag;


(Y[lower_leg]).real=temp2.real*(w[index]).real-temp2.imag*(w[index]).imag;
(Y[lower_leg]).imag=temp2.real*(w[index]).imag+temp2.imag*(w[index]).real;


(Y[upper_leg]).real=temp1.real;
(Y[upper_leg]).imag=temp1.imag;
}
index+=step;
}
leg_diff=leg_diff/2;
step*=2;
}
j=0;
for (i=1;i<(fftlen-1);i++) //bit reversal for
//re-sequencing data
{
k=fftlen/2;
while (k<=j)
{
j=j-k;
k=k/2;
}
j=j+k;
if (i<j)
{
temp1.real=(Y[j]).real;
temp1.imag=(Y[j]).imag;
(Y[j]).real=(Y[i]).real;
(Y[j]).imag=(Y[i]).imag;
(Y[i]).real=temp1.real;
(Y[i]).imag=temp1.imag;
}
}
return;
} //end of fft()



void Test_fft()
{
  
int i;
float arg1,arg2;
float mag;
int t1,t2;

  
//Fill the input array
for (i=0; i< NFFT; i++)
{
arg1 = (float)(2*PI/32); // fréquence 1
arg2 = (float)(2*PI/8); // fréquence 2

in_data[i].real = sin((float) (i*arg1)) + sin((float) (i*arg2));
in_data[i].imag = 0;
}


for (i=0; i< NFFT; i++)
{
Serial.print("IN[] = ");Serial.println(in_data[i].real);

}
t1 = micros();
fft(in_data,NFFT);
t2 = micros();
Serial.print("Temps FFT ");Serial.println(t2-t1);

for (i=0; i< NFFT; i++)
{
mag = sqrt(in_data[i].real * in_data[i].real + in_data[i].imag * in_data[i].imag);

Serial.print(" Mag_OUT [");Serial.print(i);Serial.print("] = ");Serial.println(mag);

}


//return 0;
}
