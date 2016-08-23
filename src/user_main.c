#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

#include "driver/uart.h"

// SETTINGS
#define WIFI_SSID       "wifi"
#define WIFI_PASSWORD   "password"
#define PROTO_PORT      2321

void ICACHE_FLASH_ATTR espconn_conncb(void *arg);
void ICACHE_FLASH_ATTR espconn_recvcb(void *arg, char *pdata, uint16_t len);
void ICACHE_FLASH_ATTR espconn_disconcb(void *arg);

/* main function */
void ICACHE_FLASH_ATTR user_init()
{
    // wifi driver settings
    struct station_config st_conf;
    // general connection template (setup TCP/UDP/..)
    struct espconn _espconn;
    // tcp connection template (port/...)
    esp_tcp _esp_tcp;

    // serial comunication setup
    uart_init(BIT_RATE_115200, BIT_RATE_115200);

    // wireless setup
    wifi_set_opmode(STATION_MODE);

    // wifi settings
    os_strncpy(&st_conf, WIFI_SSID, 32);
    os_strncpy(&st_conf, WIFI_PASSWORD, 64);
    wifi_station_set_config(&st_config);
    
    // tcp setup
    _esp_tcp.local_port = PROTO_PORT;
    
    // connections setup
    _espconn.proto.tcp = &_esp_tcp;
    _espconn.type = ESPCONN_TCP;
    _espconn.state = ESPCONN_NONE;

    // callback functions
    espconn_regist_connectcb(&_espconn, espconn_conncb);
    // connection timeout settings
    espconn_regist_time(&_espconn, 15, 0); 
    // start listening for connections
    espconn_accept(&_espconn);
}

void ICACHE_FLASH_ATTR espconn_conncb(void *arg) 
{
    struct espconn *conn = (struct espconn *) arg;
    // register callback functions for this espconn
    espconn_regist_recvcb(conn, espconn_recvcb);        // data
    espconn_regist_disconcb(conn, espconn_disconcb);    // disconnect
}

void ICACHE_FLASH_ATTR espconn_recvcb(void *arg, char *pdata, uint16_t len)
{   struct espconn *conn = (struct espconn *) arg; }

void ICACHE_FLASH_ATTR espconn_disconcb(void *arg)
{   struct espconn *conn = (struct espconn *) arg; }
