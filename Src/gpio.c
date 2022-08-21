#include "gpio.h"
#include "protected_io.h"

#include <avr/io.h>

static const uint8_t led_pin_mask = 1U << 7U;

void gpio_init(void)
{
	DDRB = led_pin_mask;
	// protected_write_io(DDRB, 0, 1 << 5); ???
}

void gpio_toggle_pin(void)
{
	PORTB ^= led_pin_mask;
}
