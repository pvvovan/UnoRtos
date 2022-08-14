#include "app.h"
#include "gpio.h"

#include <util/delay.h>


void uart_demoinit(void);
void uart_demoprint(const char *str);


void app_init(void)
{
	gpio_init();
	uart_demoinit();
}

void app_blink(void)
{
	gpio_toggle_pin();
	_delay_ms(100);
}

void app_sendmsg(void)
{
	static char msg[] = "0a\r\n";
	uart_demoprint(msg);
	msg[0]++;
	msg[1]++;
	if (msg[0] > '9') {
		msg[0] = '0';
		msg[1] = 'a';
	}
}
