#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

#include "driver/uart.h"

void ICACHE_FLASH_ATTR system_init_done();

/* main function */
void ICACHE_FLASH_ATTR user_init()
{
    uart_init(BIT_RATE_115200, BIT_RATE_115200);

    system_init_done_cb(system_init_done);

    wifi_set_opmode(STATION_MODE);
}

void ICACHE_FLASH_ATTR system_init_done()
{

}
