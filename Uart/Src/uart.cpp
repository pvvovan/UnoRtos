#include "string.h"
#include <stdlib.h>

#include "scope_lock.h"
#include "uart.h"
#include "uart_ll.h"

uart::uart(const peripheral unit, const size_t tx_size, const size_t rx_size) :
	unit_ {unit},
	tx_size_ {tx_size},
	rx_size_ {rx_size}
{ }

bool uart::init(const uint32_t baud) {
	if (initialized_) {
		return false;
	}
	tx_buf_ = new ring_buffer(tx_size_);
	rx_buf_ = new ring_buffer(rx_size_);
	if (tx_buf_ && rx_buf_) {
		const uint32_t ubrr = F_CPU / 16 / baud - 1;
		::uart0_ll_init(ubrr, rx_buf_, tx_buf_);
		initialized_ = true;
	}
	return initialized_;
}

void uart::start() { ::uart_ll_start(); }

size_t uart::available() {
	scope_lock sl{};
	size_t avail = rx_buf_->count();
	return avail;
}

bool uart::print(const char *str) {
	size_t len = ::strlen(str);
	return uart::write(reinterpret_cast<const uint8_t *>(str), len);
}

bool uart::write(const uint8_t *data, size_t size) {
	scope_lock sl{};
	bool empty = (tx_buf_->count() == 0);
	if (size >= (tx_size_ - tx_buf_->count())) {
		return false;
	}
	for (size_t i = 0; i < size; i++) {
		tx_buf_->write(data[i]);
	}
	if (empty && (tx_buf_->count() > 0)) {
		uint8_t b;
		tx_buf_->read(b);
		::uart0_ll_transmit(b);
	}
	return true;
}

size_t uart::read(uint8_t *data, size_t size) {
	scope_lock sl{};
	size_t count = size;
	if (count > rx_buf_->count()) {
		count = rx_buf_->count();
	}
	for (size_t i = 0; i < count; i++) {
		rx_buf_->read(data[i]);
	}
	return count;
}


extern "C" {
	void uart_demoinit(void);
	void uart_demoprint(const char *str);
}

static uart s_uart0{uart::peripheral::uart0, 256, 256};

void uart_demoinit()
{
	s_uart0.init(9600);
	s_uart0.start();
}

void uart_demoprint(const char *str)
{
	s_uart0.print(str);
}
