#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H


/**
 * \brief   Computes the energy of signal sig.
 * \param   sig	: Array representing the signal to compute.
 * 			len	: Length of sig.
 * \return  Value representing the energy of sig.
 */
float compEnergy(float sig[], short len);


/**
 * \brief   Computes the values of Iss.
 * \param   ixx	: Noisy signal's periodogram.
 * 			inn	: Noise's periodogram.
 * 			iss : Clean signal's periodogram.
 * 			len	: Length of the arrays.
 * \return  None.
 */
void compIss(float ixx[], float inn[], float iss[], short len);


/**
 * \brief   Computes the values of Rss.
 * \param   iss_re	: Real part of the clean signal's periodogram.
 * 			iss_im 	: Imaginary part of the clean signal's periodogram.
 * 			rss		: Autocorrelation coefficients of Iss.
 * 			len		: Length of the arrays.
 * \return  None.
 */
void compRss(float iss_re[], float iss_im[], float rss[], short len);


/**
 * \brief   Applies an half-wave rectification to the input signal.
 * \param   sig			: Signal on which to apply the half wave rectification.
 * 			len			: Length of array.
 * \return  None.
 */
void halfWaveRect(float sig[], short len);


/**
 * \brief   Determines if there is speech or not. In case there is, updates the
 * 			estimated value of Inn
 * \param   frame		: 	Array representing the current frame to compute.
 * 			threshold  	: 	Value representing the threshold which determines speech or not.
 * 			ref_inn     :	Array of size 3 representing the three last values of the estimate
 * 							Inn used as reference.
 * 			ixx      	:   Array representing modulus of the periodogram of the current noisy signal sample.
 * 			inn			: 	Array representing the periodogram of the current noise sample.
 * 			len			: 	Length of arrays.
 * \return  None.
 */
void compInn(float frame[], float threshold, float ref_inn[][80], float ixx[], float inn[], short len);


/**
 * \brief   Computes the auto-correlation coefficients of signal sig.
 * \param   sig	: Array representing the signal to compute.
 * 			rxx : Array representing the auto-correlation coefficients of signal sig.
 * 			len	: Length of arrays.
 * \return  None.
 */
void compRxx(float sig[], float rxx[], short len);


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
void levinson(float r[], float coeff[], short len);


/**
 * \brief   Updates the three last value of Inn. ref_inn[0] is the most recent value
 * 			while ref_inn[2] is the least recent.
 * \param   ref_inn	: Matrix with the three last values of Inn.
 * 			inn		: Array representing the new values of Inn.
 * 			len		: Length of inn and second dimension of ref_inn.
 * \return  None.
 */
void updateRefInn(float ref_inn[][80], float inn[], short len);

#endif /* __FUNCTIONS_H */
