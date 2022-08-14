#include "app.h"
#include "gpio.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>


static void uart_init(void)
{
	const uint32_t baud = 9600;
	const uint32_t ubrr = F_CPU / 16 / baud - 1;
	/* Set baud rate */
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);// no interrupts: | (1 << TXCIE0) | (1 << RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void app_init(void)
{
	gpio_init();
	uart_init();
}

void app_blink(void)
{
	gpio_toggle_pin();
	_delay_ms(100);
}

static void uart_ll_transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

static void print(const char *txt)
{
	while (*txt) {
		uart_ll_transmit(*txt);
		txt++;
	}
}

void app_sendmsg(void)
{
	static char msg[] = "0a\0";
	print(msg);
	msg[0]++;
	msg[1]++;
	if (msg[0] > '9') {
		msg[0] = '0';
		msg[1] = 'a';
	}
}
