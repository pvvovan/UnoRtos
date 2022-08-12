#include "gpio.h"

#include <avr/io.h>


void gpio_init(void)
{
	DDRB = (1 << 5);
}

void gpio_toggle_pin(void)
{
	PORTB ^= (1 << 5);
}
