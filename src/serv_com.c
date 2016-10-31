#include "serv_com.h"

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

void ICACHE_FLASH_ATTR espconn_conncb(void *arg);
void ICACHE_FLASH_ATTR espconn_recvcb(void *arg, char *pdata, uint16_t len);
void ICACHE_FLASH_ATTR espconn_disconcb(void *arg);

#define CMD_SEPARATOR 0x03

void ICACHE_FLASH_ATTR set_tcp_station(void * conn, const char * ssid, const char * password, int port) {

	struct station_config st_conf;
    wifi_set_opmode(STATION_MODE);
    struct espconn * tcp_espconn = (struct espconn *) conn;

    // esp_tcp declariation
    esp_tcp _esp_tcp;

    // tcp setup
    _esp_tcp.local_port = port;
    // wifi settings
    os_strncpy(&st_conf.ssid, ssid, 32);
    os_strncpy(&st_conf.password, password, 64);
    wifi_station_set_config(&st_conf);

    // connections setup
    tcp_espconn->proto.tcp = &_esp_tcp;
    tcp_espconn->type = ESPCONN_TCP;
    tcp_espconn->state = ESPCONN_NONE;
}

void ICACHE_FLASH_ATTR tcp_accept(void * conn, int timeout) {

    struct espconn * tcp_espconn = (struct espconn *) conn;

	espconn_regist_connectcb(tcp_espconn, espconn_conncb);
	// set timeout
    espconn_regist_time(tcp_espconn, timeout, 0); 
    // start listening for connections
    espconn_accept(tcp_espconn);
}

void ICACHE_FLASH_ATTR espconn_conncb(void *arg) {

    struct espconn *conn = (struct espconn *) arg;
    // register callback functions for this espconn
    espconn_regist_recvcb(conn, espconn_recvcb);        // data
    espconn_regist_disconcb(conn, espconn_disconcb);    // disconnect

    // call TCP_Connect_Callback extern implementation
    TCP_Connect_Callback(conn->proto.tcp->ipaddr, conn->proto.tcp->client_port);
}

void ICACHE_FLASH_ATTR espconn_recvcb(void *arg, char *pdata, uint16_t len) {

	struct espconn *conn = (struct espconn *) arg; 

	// parse to extract command

	// call onCommand
}

void ICACHE_FLASH_ATTR espconn_disconcb(void *arg) {  

	struct espconn *conn = (struct espconn *) arg; 
}