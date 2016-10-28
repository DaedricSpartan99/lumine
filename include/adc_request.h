#ifndef ADC_REQUEST_H
#define ADC_REQUEST_H


void ICACHE_FLASH_ATTR requestData(void * buffer);	// size of buffer must be sizeof(short)

void * ICACHE_FLASH_ATTR filter(void * buffer);	

/* 	returns the buffer pointer, or a null pointer.
	To determine if the data are unable to be sent to the server
	check if the return value is 0
*/

#endif