#include "ring_buffer.h"

ring_buffer::ring_buffer(size_t buf_size) { // найбільше значення (число) для
					    // процесора для одного такту
	if (buf_size > 0) {
		buf_size++;
		data_ = new uint8_t[buf_size];
	}
	size_ = buf_size;
}

ring_buffer::~ring_buffer() { delete[] data_; }

bool ring_buffer::write(uint8_t b) {
	if (size_ == 0) {
		return false;
	} else if (this->count() < (size_ - 1)) {
		data_[head_++] = b;
		if (head_ >= size_) {
			head_ = 0;
		}
		return true;
	} else {
		return false;
	}
}

bool ring_buffer::read(uint8_t &b) {
	if (this->count() > 0) {
		b = data_[tail_++];
		if (tail_ >= size_) {
			tail_ = 0;
		}
		return true;
	} else {
		return false;
	}
}

size_t ring_buffer::count() {
	if (head_ >= tail_) {
		return head_ - tail_;
	} else {
		return size_ + head_ - tail_;
	}
}
