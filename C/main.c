#include "main.h"

float sig[NB_FRAME][FRAME_SIZE];
float rxx[FRAME_SIZE] = {0.0};
float ixx_re[FRAME_SIZE] = {0.0};
float ixx_im[FRAME_SIZE] = {0.0};
float ixx_mag[FRAME_SIZE] = {0.0};
float ixx_ang[FRAME_SIZE] = {0.0};
float inn_mag[FRAME_SIZE] = {0.0};
float iss_mag[FRAME_SIZE] = {0.0};
float iss_re[FRAME_SIZE] = {0.0};
float iss_im[FRAME_SIZE] = {0.0};
float rss[FRAME_SIZE] = {0.0};
float pred_coeff[NB_FRAME][FRAME_SIZE];

// Fill the matrix with 1000.0
float ref_inn[3][FRAME_SIZE] = {{EIGHTY1000}, 		
								{EIGHTY1000}, 
								{EIGHTY1000}};	// Three last values of Inn.
												// Voluntarily big to force the update on the first loops.

void main(void) {

	// ----------------------------------- LOADING OF DATA ----------------------------------- //
	FILE *fp = NULL;
	char r_path[] = "noisy_sig.txt";	// Path to data (file must be in the same folder than the code)
	char w_path[] = "pred_coeff.txt";	// File to write the outputs
	short i;

	// Opens the data file
	if((fp = fopen(r_path, "r")) == NULL) {
		printf("No file %s\n", r_path);
		exit(EXIT_FAILURE);
	}

	// Loads the values
	for(i = 0; i < SIG_SIZE; i++) {
		short line = i / FRAME_SIZE;
		short col = i - line * FRAME_SIZE;
		fscanf(fp, "%f", &sig[line][col]);
	}
	fclose(fp);


	// --------------------------------------- PROGRAM --------------------------------------- //
	// Loops over the frames
	for(i = 0; i < NB_FRAME; i++) {

		// Computes Rxx
		compRxx(&sig[i][0], rxx, FRAME_SIZE);			// Rxx is real

		// Computes Ixx
		dft(rxx, ixx_re, ixx_im, FRAME_SIZE);			// Ixx is complex
		
		// Computes the magnitude of Ixx
		mag(ixx_re, ixx_im, ixx_mag, FRAME_SIZE);

		// Computes Inn
		compInn(&sig[i][0], ETH, ref_inn, ixx_mag, inn_mag, FRAME_SIZE);	// Inn is real and represents its magnitude

		// Updates the last values of ref_inn
		updateRefInn(ref_inn, inn_mag, FRAME_SIZE);

		// Computes Iss
		compIss(ixx_mag, inn_mag, iss_mag, FRAME_SIZE);		// Iss is real and represents its magnitude

		// We need the complex value of Iss in order to compute Rss
		// We use the magnitude of Iss and the angle of Ixx to do it
		// Compute the angle of Iss, which is the same as Ixx'
		angle(ixx_mag, ixx_re, ixx_im, ixx_ang, FRAME_SIZE);

		// Computes the complex Iss
		complex(iss_mag, ixx_ang, iss_re, iss_im, FRAME_SIZE);

		compRss(iss_re, iss_im, rss, FRAME_SIZE);		// Rss is real

		levinson(rss, &pred_coeff[i][0], FRAME_SIZE - 1);
	}
	
	// Opens the data file
	if((fp = fopen(w_path, "w")) == NULL) {
		printf("Cannot create %s\n", r_path);
		exit(EXIT_FAILURE);
	}
	
	
	for(i = 0; i < NB_FRAME; i++) {
		short j;
		for(j = 0; j < FRAME_SIZE; j++) {
			fprintf(fp, "%f\n", pred_coeff[i][j]);
		}
	}
	
	fclose(fp);

	// ----------------------------------- END OF PROGRAM ------------------------------------ //
}
