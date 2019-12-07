#include <math.h>

#define PI		3.14159f
#define PIX2	2 * PI


/**
 * \brief   Computes the angles of arrays representing complex numbers.
 * \param   Xmag	: Array representing the magnitude of the complex numbers.
 * 			Xre 	: Array representing the real part of the dft.
 * 			Xim		: Array representing the imaginary part of the dft.
 * 			Xang 	: Array representing the angles of each complex numbers.
 * 			len		: Length of arrays.
 * \return  None.
 */
void angle(float Xmag[], float Xre[], float Xim[], float Xang[], short len) {
	short i;
	for(i = 0; i < len; i++) {
		if(Xim[i] >= 0) {
			Xang[i] = acos(Xre[i] / Xmag[i]);
		}
		else {
			Xang[i] = (-1) * acos(Xre[i] / Xmag[i]);
		}
	}
}


/**
 * \brief   Convert a real positive number to a complex number.
 * \param   Xmag	: Array representing the magnitude of the complex numbers.
 * 			Xang 	: Array representing the angles of each complex numbers.
 * 			Xre 	: Array representing the real part of the dft.
 * 			Xim		: Array representing the imaginary part of the dft.
 * 			len		: Length of arrays.
 * \return  None.
 */
void complex(float Xmag[], float Xang[], float Xre[], float Xim[], short len) {
	short i;
	for(i = 0; i< len; i++) {
		Xre[i] = Xmag[i] * cos(Xang[i]);
		Xim[i] = Xmag[i] * sin(Xang[i]);
	}
}


/**
 * \brief   Computes the dot product of two arrays of length len.
 * \param   x	: First input array.
 * 			y	: Second input array.
 * 			len		: Length of arrays.
 * \return  The dot product of x and y.
 */
short dot(float x[], float y[], short len) {
	short i, res = 0;
	for(i = 0; i < len; i++) {
		res += x[i] * y[i];
	}
	return res;
}


/**
 * \brief   Computes the dft of signal x.
 * \param   x	: Array representing the signal to compute.
 * 			Xre : Array representing the real part of the dft.
 * 			Xim	: Array representing the imaginary part of the dft.
 * 			len	: Length of arrays.
 * \return  None.
 */
/* This function has been inspired by :
 * https://batchloaf.wordpress.com/2013/12/07/simple-dft-in-c/
 */
void dft(float x[], float Xre[], float Xim[], short len) {

	short n, k;
	for(k = 0 ; k < len ; ++k) {
		Xre[k] = 0;				// Real part of X[k]
		Xim[k] = 0;				// Imaginary part of X[k]

		for(n = 0 ; n < len ; ++n) {
			Xre[k] += x[n] * cos(n * k * PIX2 / len);
			Xim[k] -= x[n] * sin(n * k * PIX2 / len);
		}
	}
}


/**
 * \brief   Computes the inverse dft of signal X.
 * \param   Xre : Array representing the real part of the dft.
 * 			Xim	: Array representing the imaginary part of the dft.
 * 			x	: Array representing the signal to find.
 * 			len	: Length of arrays.
 * \return  None.
 */
void idft(float Xre[], float Xim[], float x[], short len) {

	short n, k;
	for(k = 0 ; k < len; ++k) {
		x[k] = 0;

		for(n = 0 ; n < len; ++n) {
			x[k] += Xre[n] * cos(n * k * PIX2 / len) - Xim[n] * sin(n * k * PIX2 / len);
		}
		x[k] /= len;
	}
}


/**
 * \brief   Returns the index of the minimum value in an array.
 * \param   arr	: The input array.
 * 			len	: Length of the array.
 * \return  Index of the minimum value.
 */
short indOfMin(float arr[], short len) {
	short i, ind = 0;
	for(i = 1; i < len; i++) {		// We do not start at 0 because we suppose the initial
									// minimum is at index 0.
		if(arr[i] < arr[ind]) {
			ind = i;
		}
	}
	return ind;
}


/**
 * \brief   Computes the mean value of input array.
 * \param   arr	: Input array.
 * 			len	: Length of arr.
 * \return  Mean value.
 */
float mean(float arr[], short len) {
	float mean_val = 0;
	short i;
	for(i = 0; i < len; i++) {
		mean_val += arr[i];
	}
	return mean_val / (float)len;
}


/**
 * \brief   Computes the magnitude of DFT X.
 * \param   Xre	: Array representing the real part of the DFT to compute.
 * 			Xim	: Array representing the imaginary part of the DFT to compute.
 * 			len	: Length of arrays.
 * \return  None.
 */
void mag(float Xre[], float Xim[], float Xmod[], short len) {
	short i;
	for(i = 0; i < len; i++) {
		Xmod[i] = sqrtf(Xre[i] * Xre[i] + Xim[i] * Xim[i]);
	}
}


/**
 * \brief   Reverts an array.
 * \param   arr		: Input array.
 * 			rvrt	: Reverted array.
 * 			len		: Length of arrays.
 * \return  None.
 */
void revert(float arr[], float rvrt[], short len) {
	short i;
	for(i = 0; i < len; i++) {
		rvrt[i] = arr[len - 1 - i];
	}
}


/**
 * \brief   Select a sub-array of an array.
 * \param   arr		: Input array.
 * 			slctd	: Sub-array.
 * 			start	: Starting index (included) of the sub-array in arr.
 * 			end		: Ending index (exclueded) of the sub-array in arr.
 * \return  None.
 */
void my_select(float arr[], float slctd[], short start, short end) {
	short i;
	for(i = start; i < end; i++) {
		slctd[i - start] = arr[i];
	}
}
