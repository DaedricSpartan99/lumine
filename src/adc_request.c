#include "adc_request.h"

#define LIGHT_MIN 0x3FF
#define LIGHT_MAX 0x1
#define LIGHT_NONE 0x0	// I suppose that 0 or no signal
#define LIGHT_LIMIT 0x1FF	// tha half of LIGHT_MIN

void ICACHE_FLASH_ATTR requestData(void * buffer) {

	// get data from ADC register and store them in buffer
}

void * ICACHE_FLASH_ATTR filter(void * buffer) {

	uint16_t * bufint = (uint16_t *) buffer;

	// verify that light intensity is more than LIGHT_LIMIT

	if (*bufint == LIGHT_NONE || *bufint > LIGHT_LIMIT)
		return 0;

	return buffer;
}