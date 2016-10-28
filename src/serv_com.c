#include "serv_com.h"

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

/*
 * 	Global variables to use
*/

struct espconn TCP_espconn, UDP_espconn;
esp_tcp _esp_tcp;
esp_udp _esp_udp;

void ICACHE_FLASH_ATTR UDP_Create(int port, const char * ip_addr) {
	
}

void ICACHE_FLASH_ATTR send_UDP_Data(void * data, uint16_t len) {

}

void ICACHE_FLASH_ATTR UDP_Delete() {

}

void ICACHE_FLASH_ATTR set_TCP_Station(const char * ssid, const char * password, int port) {

	struct station_config st_conf;
    wifi_set_opmode(STATION_MODE);

    // tcp setup
    _esp_tcp.local_port = port;

    char * st_conf_iter = (char*) &st_conf;
    // wifi settings
    os_strncpy(st_conf_iter, ssid, 32);
    st_conf_iter += 32;
    os_strncpy(st_conf_iter, password, 64);
    wifi_station_set_config(&st_conf);
}

void ICACHE_FLASH_ATTR TCP_Accept(int timeout) {

    // connections setup
    TCP_espconn.proto.tcp = &_esp_tcp;
    TCP_espconn.type = ESPCONN_TCP;
    TCP_espconn.state = ESPCONN_NONE;

	espconn_regist_connectcb(&TCP_espconn, espconn_conncb);
	// set timeout
    espconn_regist_time(&TCP_espconn, timeout, 0); 
    // start listening for connections
    espconn_accept(&TCP_espconn);
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