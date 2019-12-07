#include <stdio.h>
#include <math.h>

#include "main.h"
#include "utility.h"

/**
 * \brief   Computes the energy of signal sig.
 * \param   sig	: Array representing the signal to compute.
 * 			len	: Length of sig.
 * \return  Value representing the energy of sig.
 */
float compEnergy(float sig[], short len) {
	float energy = 0.0;
	short i;
	for(i = 0; i < len; i++) {
		energy += sig[i] * sig[i];		// We do  not use the pow2() function because it
										// slows down the execution.
	}
	return energy;
}


/**
 * \brief   Computes the values of Iss.
 * \param   ixx	: Noisy signal's periodogram.
 * 			inn	: Noise's periodogram.
 * 			iss : Clean signal's periodogram.
 * 			len	: Length of the arrays.
 * \return  None.
 */
void compIss(float ixx[], float inn[], float iss[], short len) {
	float ixx_mean = mean(ixx, len);
	float inn_mean = mean(inn, len);
	float max_value = MAX(0, ixx_mean - inn_mean);

	short i;
	for(i = 0; i < len; i++) {
		iss[i] = max_value;
	}
}


/**
 * \brief   Computes the values of Rss.
 * \param   iss_re	: Real part of the clean signal's periodogram.
 * 			iss_im 	: Imaginary part of the clean signal's periodogram.
 * 			rss		: Autocorrelation coefficients of Iss.
 * 			len		: Length of the arrays.
 * \return  None.
 */
void compRss(float iss_re[], float iss_im[], float rss[], short len) {

	idft(iss_re, iss_im, rss, len);

	short i;
	for(i = 0; i < len; i++) {
		rss[i] /= 2;
	}
}


/**
 * \brief   Applies an half-wave rectification to the input signal.
 * \param   sig			: Signal on which to apply the half wave rectification.
 * 			len			: Length of array.
 * \return  None.
 */
void halfWaveRect(float sig[], short len) {
	int i;
	for(i = 0; i < len; i++) {
		sig[i] = MAX(0, sig[i]);		// If sig[i] is negative, takes value 0,
										// otherwise is unmodified.
	}
}


/**
 * \brief   Determines if there is speech or not. In case there is, updates the
 * 			estimated value of Inn
 * \param   frame		: 	Array representing the current frame to compute.
 * 			threshold  	: 	Value representing the threshold which determines speech or not.
 * 			ref_inn     :	Array of size 3 representing the three last values of the estimate
 * 							Inn used as reference.
 * 			ixx      	:   Array representing the magnitude of the periodogram of the current noisy signal sample.
 * 			inn			: 	Array representing the periodogram of the current noise sample.
 * 			len			: 	Length of arrays.
 * \return  None.
 */
void compInn(float frame[], float threshold, float ref_inn[][80], float ixx[], float inn[], short len) {

	short i;

	// If the energy of the current sample is greater than the threshold,
	// we consider there is speech.
	if(compEnergy(frame, len) >= threshold) {
		// Therefore, the estimate value of inn is not updated
		for(i = 0; i < len; i++) {
			inn[i] = ref_inn[0][i];
		}
	}
	else {
		// If periodogram of corrupted speech is less than noise last's one,
		// we update it
		if(mean(ixx, len) < mean(&ref_inn[0][0], 3)) {
			for(i = 0; i < len; i++) {
				inn[i] = ixx[i];
			}
		}
		else {
			// Compute the mean values of the three last inn and take the smallest
			float meanRefInn[3];
			meanRefInn[0] = mean(&ref_inn[0][0], 3);
			meanRefInn[1] = mean(&ref_inn[1][0], 3);
			meanRefInn[2] = mean(&ref_inn[2][0], 3);

			short minInd = indOfMin(meanRefInn, 3);
			for(i = 0; i < len; i++) {
				inn[i] = ref_inn[minInd][i];
			}
		}
	}
	halfWaveRect(inn, len);
}


/**
 * \brief   Computes the auto-correlation coefficients of signal sig.
 * \param   sig	: Array representing the signal to compute.
 * 			rxx : Array representing the auto-correlation coefficients of signal sig.
 * 			len	: Length of arrays.
 * \return  None.
 */
void compRxx(float sig[], float rxx[], short len) {
	int i, m;
	for(i = 0; i < len; i++) {
		rxx[i] = 0;
		for(m = 0; m < len - i; m++) {
			rxx[i] += sig[m] * sig[m + i];
		}
	}
}


/**
 * \brief   Determines the coefficients of a len order autoregressive linear process which has r
 * 		 	as its autocorrelation sequence. Here, finds the prediction coefficients.
 * \param   r			: 	Array representing the current frame to compute.
 * 			threshold  	: 	Value representing the threshold which determines speech or not.
 * 			ref_inn     :	Array of size 3 representing the three last values of the estimate
 * 							Inn used as reference.
 * 			ixx      	:   Array representing the magnitude of the periodogram of the current noisy signal sample.
 * 			inn			: 	Array representing the periodogram of the current noise sample.
 * 			len			: 	Length of arrays.
 * \return  None.
 */
void levinson(float r[], float coeff[], short len) {

	float a[FRAME_SIZE - 1][FRAME_SIZE - 1];
	float tmp1[FRAME_SIZE], tmp2[FRAME_SIZE], tmp3[FRAME_SIZE];
	float P;

	a[0][0] = -r[1] / r[0];
	P = r[0] * (1 - a[0][0] * a[0][0]);

	short i;
	for(i = 1; i < len; i++) {
		my_select(&a[i - 1][0], tmp1, 0, i - 1);
		my_select(r, tmp2, 1, i);
		revert(tmp2, tmp3, len);

		a[i][i] = (-(r[i + 1] + dot(tmp1, tmp3, len))) / P;

		short j;
		for(j = 0; j < i; j++) {
			a[i][j] = a[i - 1][j] + a[i][i] * a[i - 1][i - 1 - j];
		}
		P *= (1 - a[i][i] * a[i][i]);
	}

	coeff[0] = 1;
	for(i = 1; i < len; i++) {
		if(isnan(a[len - 1][i - 1])) {
			coeff[i] = 0.0;
		}
		else {
			coeff[i] = a[len - 1][i - 1] / a[len - 1][1];
		}
	}
}


/**
 * \brief   Updates the three last value of Inn. ref_inn[0] is the most recent value
 * 			while ref_inn[2] is the least recent.
 * \param   ref_inn	: Matrix with the three last values of Inn.
 * 			inn		: Array representing the new values of Inn.
 * 			len		: Length of inn and second dimension of ref_inn.
 * \return  None.
 */
void updateRefInn(float ref_inn[][80], float inn[], short len) {
	short i;
	for(i = 0; i < len; i++) {
		ref_inn[2][i] = ref_inn[1][i];
		ref_inn[1][i] = ref_inn[0][i];
		ref_inn[0][i] = inn[i];
	}
}
