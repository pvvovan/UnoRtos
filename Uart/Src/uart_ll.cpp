#include <avr/interrupt.h>

#include "ring_buffer.h"
#include "uart_ll.h"


static ring_buffer* s_rx0_buf {nullptr};
static ring_buffer* s_tx0_buf {nullptr};
static ring_buffer* s_rx1_buf {nullptr};
static ring_buffer* s_tx1_buf {nullptr};
static ring_buffer* s_rx2_buf {nullptr};
static ring_buffer* s_tx2_buf {nullptr};
static ring_buffer* s_rx3_buf {nullptr};
static ring_buffer* s_tx3_buf {nullptr};

void uart_ll_start()
{
	sei();
}


/* ======================= UART0 ======================= */
void uart0_ll_init(const uint32_t ubrr, ring_buffer *rx_buf, ring_buffer *tx_buf) {
	/* Set baud rate */
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << TXCIE0) | (1 << RXCIE0);
	/* Asynchronous, Disabled parity, 1 stop bit, 8-bit data */
	UCSR0C = (3 << UCSZ00);

	s_rx0_buf = rx_buf;
	s_tx0_buf = tx_buf;
}

void uart0_ll_transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

ISR(USART0_TX_vect) {
	if (s_tx0_buf->count() > 0) {
		uint8_t b;
		s_tx0_buf->read(b);
		UDR0 = b;
	}
}

ISR(USART0_RX_vect) {
	uint8_t b = UDR0;
	s_rx0_buf->write(b);
}


/* ======================= UART1 ======================= */
void uart1_ll_init(const uint32_t ubrr, ring_buffer *rx_buf, ring_buffer *tx_buf) {
	/* Set baud rate */
	UBRR1H = (uint8_t)(ubrr >> 8);
	UBRR1L = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << TXCIE1) | (1 << RXCIE1);
	/* Asynchronous, Disabled parity, 1 stop bit, 8-bit data */
	UCSR1C = (3 << UCSZ10);

	s_rx1_buf = rx_buf;
	s_tx1_buf = tx_buf;
}

void uart1_ll_transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR1A & (1 << UDRE1)))
		;
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

ISR(USART1_TX_vect) {
	if (s_tx1_buf->count() > 0) {
		uint8_t b;
		s_tx1_buf->read(b);
		UDR1 = b;
	}
}

ISR(USART1_RX_vect) {
	uint8_t b = UDR1;
	s_rx1_buf->write(b);
}


/* ======================= UART2 ======================= */
void uart2_ll_init(const uint32_t ubrr, ring_buffer *rx_buf, ring_buffer *tx_buf) {
	/* Set baud rate */
	UBRR2H = (uint8_t)(ubrr >> 8);
	UBRR2L = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSR2B = (1 << RXEN2) | (1 << TXEN2) | (1 << TXCIE2) | (1 << RXCIE2);
	/* Asynchronous, Disabled parity, 1 stop bit, 8-bit data */
	UCSR2C = (3 << UCSZ20);

	s_rx2_buf = rx_buf;
	s_tx2_buf = tx_buf;
}

void uart2_ll_transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR2A & (1 << UDRE2)))
		;
	/* Put data into buffer, sends the data */
	UDR2 = data;
}

ISR(USART2_TX_vect) {
	if (s_tx2_buf->count() > 0) {
		uint8_t b;
		s_tx2_buf->read(b);
		UDR2 = b;
	}
}

ISR(USART2_RX_vect) {
	uint8_t b = UDR2;
	s_rx2_buf->write(b);
}


/* ======================= UART3 ======================= */
void uart3_ll_init(const uint32_t ubrr, ring_buffer *rx_buf, ring_buffer *tx_buf) {
	/* Set baud rate */
	UBRR3H = (uint8_t)(ubrr >> 8);
	UBRR3L = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSR3B = (1 << RXEN3) | (1 << TXEN3) | (1 << TXCIE3) | (1 << RXCIE3);
	/* Asynchronous, Disabled parity, 1 stop bit, 8-bit data */
	UCSR3C = (3 << UCSZ30);

	s_rx3_buf = rx_buf;
	s_tx3_buf = tx_buf;
}

void uart3_ll_transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR3A & (1 << UDRE3)))
		;
	/* Put data into buffer, sends the data */
	UDR3 = data;
}

ISR(USART3_TX_vect) {
	if (s_tx3_buf->count() > 0) {
		uint8_t b;
		s_tx3_buf->read(b);
		UDR3 = b;
	}
}

ISR(USART3_RX_vect) {
	uint8_t b = UDR3;
	s_rx3_buf->write(b);
}
