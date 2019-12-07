#ifndef __UTILITY_H
#define __UTILITY_H

#define MAX(a, b) ((a) > (b)) ? (a) : (b)


/**
 * \brief   Computes the angles of arrays representing complex numbers.
 * \param   Xmag	: Array representing the magnitude of the complex numbers.
 * 			Xre 	: Array representing the real part of the dft.
 * 			Xim		: Array representing the imaginary part of the dft.
 * 			ang 	: Array representing the angles of each complex numbers.
 * 			len		: Length of arrays.
 * \return  None.
 */
void angle(float Xmag[], float Xre[], float Xim[], float ang[], short len);


/**
 * \brief   Convert a real positive number to acomplexe number.
 * \param   Xmag	: Array representing the magnitude of the complex numbers.
 * 			Xang 	: Array representing the angles of each complex numbers.
 * 			Xre 	: Array representing the real part of the dft.
 * 			Xim		: Array representing the imaginary part of the dft.
 * 			len		: Length of arrays.
 * \return  None.
 */
void complex(float Xmag[], float Xang[], float Xre[], float Xim[], short len);


/**
 * \brief   Computes the dot product of two arrays of length len.
 * \param   x	: First input array.
 * 			y	: Second input array.
 * 			len		: Length of arrays.
 * \return  The dot product of x and y.
 */
short dot(float x[], float y[], short len);


/**
 * \brief   Computes the dft of sig.
 * \param   sig	: Array representing the signal to compute.
 * 			re 	: Array representing the real part of the dft.
 * 			im	: Array representing the imaginary part of the dft.
 * 			len	: Length of arrays.
 * \return  None.
 */
void dft(float sig[], float re[], float im[], short len);


/**
 * \brief   Computes the inverse dft of signal X.
 * \param   Xre : Array representing the real part of the dft.
 * 			Xim	: Array representing the imaginary part of the dft.
 * 			x	: Array representing the signal to find.
 * 			len	: Length of arrays.
 * \return  None.
 */
void idft(float Xre[], float Xim[], float x[], short len);


/**
 * \brief   Returns the index of the minimum value in an array.
 * \param   arr	: The input array.
 * 			len	: Length of the array.
 * \return  Index of the minimum value.
 */
short indOfMin(float arr[], short len);


/**
 * \brief   Computes the mean value of input array.
 * \param   arr	: Input array.
 * 			len	: Length of arr.
 * \return  Mean value.
 */
float mean(float arr[], short len);


/**
 * \brief   Computes the modulus of DFT X.
 * \param   Xre	: Array representing the real part of the DFT to compute.
 * 			Xim	: Array representing the imaginary part of the DFT to compute.
 * 			len	: Length of arrays.
 * \return  None.
 */
void mag(float Xre[], float Xim[], float Xmod[], short len);


/**
 * \brief   Reverts an array.
 * \param   arr		: Input array.
 * 			rvrt	: Reverted array.
 * 			len		: Length of arrays.
 * \return  None.
 */
void revert(float arr[], float rvrt[], short len);


/**
 * \brief   Select a sub-array of an array.
 * \param   arr		: Input array.
 * 			slctd	: Sub-array.
 * 			start	: Starting index (included) of the sub-array in arr.
 * 			end		: Ending index (exclueded) of the sub-array in arr.
 * \return  None.
 */
void my_select(float arr[], float slctd[], short start, short end);

#endif /* __UTILITY_H */
