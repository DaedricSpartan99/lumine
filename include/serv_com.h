#ifndef SERV_COM_H
#define SERV_COM_H

#define IP_LENGTH 4

void ICACHE_FLASH_ATTR set_tcp_station(void *conn, const char *ssid, const char *password, int port); 	// sets TCP options, returns 0 if no error

void ICACHE_FLASH_ATTR tcp_accept(void *conn, int timeout);	// wait until a connection is established, must be non-blocking

void ICACHE_FLASH_ATTR on_command(const char *cmd, const char *argv, uint8_t argc, const char *sender_ip_addr);	// must be implemented externally

#endif