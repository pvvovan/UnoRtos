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

uart::~uart()
{
	if (tx_buf_) {
		delete tx_buf_;
	}
	if (rx_buf_) {
		delete rx_buf_;
	}
}

bool uart::init(const uint32_t baud) {
	if (initialized_) {
		return false;
	}
	tx_buf_ = new ring_buffer(tx_size_);
	rx_buf_ = new ring_buffer(rx_size_);
	if (tx_buf_ && rx_buf_) {
		const uint32_t ubrr = F_CPU / 16 / baud - 1;
		initialized_ = true;
		switch (unit_) {
			case peripheral::uart0:
				::uart0_ll_init(ubrr, rx_buf_, tx_buf_);
				break;
			case peripheral::uart1:
				::uart1_ll_init(ubrr, rx_buf_, tx_buf_);
				break;
			case peripheral::uart2:
				::uart2_ll_init(ubrr, rx_buf_, tx_buf_);
				break;
			case peripheral::uart3:
				::uart3_ll_init(ubrr, rx_buf_, tx_buf_);
				break;
			default:
				initialized_ = false;
				break;
		}
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
		switch (unit_) {
			case peripheral::uart0:
				::uart0_ll_transmit(b);
				break;
			case peripheral::uart1:
				::uart1_ll_transmit(b);
				break;
			case peripheral::uart2:
				::uart2_ll_transmit(b);
				break;
			case peripheral::uart3:
				::uart3_ll_transmit(b);
				break;
			default:
				break;
		}
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
	void echo_uart2(void);
}

static uart s_uart0{uart::peripheral::uart0, 256, 256};
static uart s_uart2{uart::peripheral::uart2, 256, 256};
static uart s_uart3{uart::peripheral::uart3, 256, 256};

void uart_demoinit()
{
	s_uart0.init(9600);
	s_uart2.init(38400);
	s_uart3.init(38400);
	uart::start();
}

void uart_demoprint(const char *str)
{
	s_uart0.print(str);
	s_uart3.print("str3");
}

void echo_uart2()
{
	int avail = s_uart2.available();
	if (avail > 0) {
		uint8_t buf[avail];
		s_uart2.read(buf, avail);
		s_uart2.write(buf, avail);
	}
}
