#ifndef SERV_COM_H
#define SERV_COM_H

#define IP_LENGTH 4

void ICACHE_FLASH_ATTR UDP_Create(int port, const char * ip_addr);	// creates UDP socket
void ICACHE_FLASH_ATTR send_UDP_Data(void * data, uint16_t len);	// sends data
void ICACHE_FLASH_ATTR UDP_Delete();								// close UDP socket

void ICACHE_FLASH_ATTR set_TCP_Station(const char * ssid, const char * password, int port); 	// sets TCP options, returns 0 if no error

void ICACHE_FLASH_ATTR TCP_Accept(int timeout = 15);	// wait until a connection is established, must be non-blocking

void ICACHE_FLASH_ATTR TCP_Connect_Callback(const char * ip_addr, int client_port);	// must be implemented externally
void ICACHE_FLASH_ATTR onCommand(const char * cmd, const char * sender_ip_addr);	// must be implemented externally

#endif