#ifndef UART_H_
#define UART_H_

#include <stddef.h>
#include <stdint.h>

#include "ring_buffer.h"


class uart final {
      public:
	enum class peripheral { uart0, uart1, uart2, uart3 };
	uart(const peripheral unit, const size_t tx_size, const size_t rx_size);
	~uart();
	bool init(const uint32_t baud);
	size_t available();
	bool print(const char *str);
	bool write(const uint8_t *data, size_t size);
	size_t read(uint8_t *data, size_t size);
	static void start();

      private:
	const peripheral unit_;
	const size_t tx_size_;
	const size_t rx_size_;
	bool initialized_ {false};
	ring_buffer *tx_buf_ {nullptr};
	ring_buffer *rx_buf_ {nullptr};
};

#endif /* UART_H_ */
