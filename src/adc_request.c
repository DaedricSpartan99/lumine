#include "adc_request.h"

#define LIGHT_MIN 0x3FF
#define LIGHT_MAX 0x1
#define LIGHT_NONE 0x0
#define LIGHT_LIMIT 0x1FF	// tha half of LIGHT_MIN

void requestData(void * buffer) {

	// get data from ADC register and store them in buffer
}

void * filter(void * buffer) {

	uint16_t * bufint = (uint16_t *) buffer;

	if (*bufint == LIGHT_NONE || *bufint > LIGHT_LIMIT)
		return 0;

	return buffer;
}