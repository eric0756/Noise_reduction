#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "utility.h"

#define FILE_SIZE		19559								// Number of sample in the input signal
#define FS				8000								// Sample frequency
#define FRAME_DURATION	100									// Duration of a frame (represents 10ms)
#define FRAME_SIZE		((FS) / (FRAME_DURATION))			// Number of sample in a frame
#define NB_FRAME		((FILE_SIZE) / (FRAME_SIZE))		// Number of frames
#define SIG_SIZE		((NB_FRAME) * (FRAME_SIZE))			// Number of sample in the resized signal
#define ETH				2.5f								// Threshold for computation of Inn
#define TEST_NB_FRAME	5
#define TEST_SIG_SIZE	TEST_NB_FRAME * FRAME_SIZE

#define ONE1000     	1000
#define FIVE1000    	ONE1000, ONE1000, ONE1000, ONE1000, ONE1000
#define TEN1000     	FIVE1000, FIVE1000
#define TWENTY1000 		TEN1000, TEN1000
#define EIGHTY1000		TWENTY1000, TWENTY1000, TWENTY1000, TWENTY1000

float asmCompEnergy(float sig[], short n);

#endif /* __MAIN_H */
