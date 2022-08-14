#include "gpio.h"
#include "protected_io.h"

#include <avr/io.h>


void gpio_init(void)
{
	DDRB = (1 << 5);
	// protected_write_io(DDRB, 0, 1 << 5); ???
}

void gpio_toggle_pin(void)
{
	PORTB ^= (1 << 5);
}
