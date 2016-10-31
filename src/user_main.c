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

#define CONN_TIMEOUT 15

/* main function */
void ICACHE_FLASH_ATTR user_init()
{
    // tcp connection
    struct espconn _espconn;
    set_tcp_station((void*) &_espconn, WIFI_SSID, WIFI_PASSWORD, PROTO_PORT);

    // serial comunication setup
    uart_init(BIT_RATE_115200, BIT_RATE_115200);

    tcp_accept((void*) &_espconn, CONN_TIMEOUT);
}

void ICACHE_FLASH_ATTR on_command(const char *cmd, const char *argv, uint8_t argc, const char *sender_ip_addr) {


}