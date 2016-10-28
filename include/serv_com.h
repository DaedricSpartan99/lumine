#ifndef SERV_COM_H
#define SERV_COM_H

void ICACHE_FLASH_ATTR recv_UDP_Callback(void * data, uint16_t len);
void ICACHE_FLASH_ATTR send_UDP_Data(void * data, uint16_t len);

void * ICACHE_FLASH_ATTR TCP_Connect(const char * ssid, const char * password);
uint16_t ICACHE_FLASH_ATTR TCP_Write(const void * buffer, uint16_t len);
uint16_t ICACHE_FLASH_ATTR TCP_Read(void * buffer, uint16_t len);
void ICACHE_FLASH_ATTR TCP_Disconnect();

#endif