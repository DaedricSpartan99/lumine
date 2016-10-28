#ifndef SERV_COM_H
#define SERV_COM_H

void recv_UDP_Callback(void * data, uint16_t len);
void send_UDP_Data(void * data, uint16_t len);

void * TCP_Connect(const char * ssid, const char * password);
uint16_t TCP_Write(const void * buffer, uint16_t len);
uint16_t TCP_Read(void * buffer, uint16_t len);
void TCP_Disconnect();

#endif