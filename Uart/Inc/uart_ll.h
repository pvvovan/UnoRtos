#ifndef UART_LL_H_
#define UART_LL_H_

#include <stddef.h>
#include <stdint.h>

#include "ring_buffer.h"

void uart0_ll_init(const uint32_t ubrr, ring_buffer *rx_buf, ring_buffer *tx_buf);
void uart_ll_start();
void uart0_ll_transmit(uint8_t data);

#endif /* UART_LL_H_ */
