//------------------------------------------------------------------------------
// FFT_code_Short.c
// Implementation of a complex fft originally written by Rulph Chassaing.
// Reworked for the Cortex-M4 by Mark Wickert, April 2015.
//
// Reworked by B. BARRY  May 2020
//------------------------------------------------------------------------------

#include	<math.h>


#define		MAX_FFT_LEN		512


struct cmpx {			//complex data structure used by FFT
	float real, imag;
};
typedef struct cmpx COMPLEX;


void	make_twiddle_array(int fftlen);

COMPLEX		Yvec[MAX_FFT_LEN], Twiddle[MAX_FFT_LEN];


int	fft_abs_short(short *Sig_Vect, float *Fft_Vect, int fftlen)
//----------------------------------------------------------------------
// Parametres en entree :
//	Sig_Vect = vecteur echantillons du signal
//	fftlen      = nombre de points de la FFT
// Parametres en sortie :
//	 Fft_Vect = vecteur echantillons du module de la FFT (abs(fft))
//----------------------------------------------------------------------
{
	COMPLEX  temp1, temp2;		//temporary storage variables
	float vreal, vimag;
	int i, j, k;				//loop counter variables
	int upper_leg, lower_leg;	//index of upper/lower
	//butterfly leg
	int leg_diff;				//difference between upper/lower leg
	int index, step;			//index and step between twiddle factor
	int num_stages = 0;			//number of FFT stages, or iterations
	int nerr = 0;

	if (fftlen > MAX_FFT_LEN || fftlen < 64) {
		nerr = 1;	goto sortie;
	}
	// Convert real Sig_Vect into complex Yvec
	for (i = 0; i < fftlen; i++) {
		Yvec[i].real = (float)Sig_Vect[i];		Yvec[i].imag = 0.0;
	}

	make_twiddle_array(fftlen);
	i = 1;						//log(base 2) of # of points = # of stages
	do 	{
		num_stages += 1;
		i = i * 2;
	} while (i < fftlen);

	leg_diff = fftlen / 2;		//starting difference between pper & lower legs
	step = 2;					//step between values in twiddle.h
	for (i = 0; i < num_stages; i++) { //for M-point FFT
		index = 0;
		for (j = 0; j < leg_diff; j++) {
			for (upper_leg = j; upper_leg < fftlen; upper_leg += (2*leg_diff)) {
				lower_leg = upper_leg + leg_diff;
				temp1.real = (Yvec[upper_leg]).real + (Yvec[lower_leg]).real;
				temp1.imag = (Yvec[upper_leg]).imag + (Yvec[lower_leg]).imag;
				temp2.real = (Yvec[upper_leg]).real - (Yvec[lower_leg]).real;
				temp2.imag = (Yvec[upper_leg]).imag - (Yvec[lower_leg]).imag;
				(Yvec[lower_leg]).real = temp2.real*(Twiddle[index]).real - temp2.imag*(Twiddle[index]).imag;
				(Yvec[lower_leg]).imag = temp2.real*(Twiddle[index]).imag + temp2.imag*(Twiddle[index]).real;
				(Yvec[upper_leg]).real = temp1.real;
				(Yvec[upper_leg]).imag = temp1.imag;
			}
			index += step;
		}
		leg_diff = leg_diff / 2;
		step *= 2;
	}
	j = 0;
	for (i = 1; i < (fftlen - 1); i++) { //bit reversal for	//re-sequencing data
		k = fftlen / 2;
		while (k <= j) {
			j = j - k;
			k = k / 2;
		}
		j = j + k;
		if (i < j) {
			temp1.real = (Yvec[j]).real;
			temp1.imag = (Yvec[j]).imag;
			(Yvec[j]).real = (Yvec[i]).real;
			(Yvec[j]).imag = (Yvec[i]).imag;
			(Yvec[i]).real = temp1.real;
			(Yvec[i]).imag = temp1.imag;
		}
	}
	for (i = 0; i < fftlen; i++) {
		vreal = Yvec[i].real;		vimag = Yvec[i].imag;
		Fft_Vect[i] = (float)sqrt(vreal*vreal + vimag*vimag);
	}
sortie:
	return nerr;
}

void	make_twiddle_array(int fftlen)
//-------------------------------------------------------------
//-------------------------------------------------------------
{	int n;	float vn;

	for (n = 0; n < fftlen; n++) { //set up DFT twiddle factors
		vn = (float) (PI*n/fftlen);
		Twiddle[n].real = (float)cos(vn);
		Twiddle[n].imag = (float)(-sin(vn));
	}
}
