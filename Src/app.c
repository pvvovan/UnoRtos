#include "app.h"
#include "gpio.h"

#include <util/delay.h>


void app_init(void)
{
	gpio_init();
}

void app_blink(void)
{
	gpio_toggle_pin();
	_delay_ms(100);
}
