#include <avr/interrupt.h>

#include "ring_buffer.h"
#include "uart_ll.h"

static ring_buffer *s_rx_buf{nullptr};
static ring_buffer *s_tx_buf{nullptr};

void uart0_ll_init(const uint32_t ubrr, ring_buffer *rx_buf, ring_buffer *tx_buf) {
	/* Set baud rate */
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << TXCIE0) | (1 << RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);

	s_rx_buf = rx_buf;
	s_tx_buf = tx_buf;
}

void uart_ll_start() { sei(); }

void uart0_ll_transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

ISR(USART0_TX_vect) {
	if (s_tx_buf->count() > 0) {
		uint8_t b;
		s_tx_buf->read(b);
		UDR0 = b;
	}
}

ISR(USART0_RX_vect) {
	uint8_t b = UDR0;
	s_rx_buf->write(b);
}
