 #include "queuearr.hpp"
#include <complex/complex.hpp>
#include <stdexcept>
#include <memory>

QueueArr::QueueArr(const QueueArr& copy)
  : head_(0)
  , tail_(0) {
  data_ = std::make_unique<Complex[]>(copy.head_ - copy.tail_);
  capacity_ = copy.head_ - copy.tail_;
  for (int i = 0; i < copy.head_ - copy.tail_; i++) {
    Push(copy.data_[(copy.tail_ + i) % copy.capacity_]);
  }
}

QueueArr::~QueueArr() {
  data_.reset();
  head_ = 0;
  tail_ = 0;
  capacity_ = 0;
}

QueueArr& QueueArr::operator=(const QueueArr& value) {
  if (this != &value) {
    if (capacity_ < value.head_ - value.tail_) {
      Clear();
      data_ = std::make_unique<Complex[]>((value.head_ - value.tail_) * 2);
    }
    head_ = 0;
    tail_ = 0;
    for (int i = 0; i < value.head_ - value.tail_; i++) {
      Push(value.data_[(value.tail_ + i) % value.capacity_]);
    }
  }
  return *this;
}

bool QueueArr::IsEmpty() const noexcept {
  return head_ == tail_;
}

void QueueArr::Push(const Complex& value) {
  if (!IsEmpty() && (head_ % capacity_) == (tail_ % capacity_)) {
    std::unique_ptr<Complex[]> new_data = std::make_unique<Complex[]>(capacity_ * 2);
    for (int i = 0; i < capacity_; i++) {
      new_data[i] = data_[(tail_ + i) % capacity_];
    }
    data_.reset();
    data_ = std::move(new_data);
    capacity_ *= 2;
    head_ = head_ - tail_;
    tail_ = 0;
  } else if (IsEmpty()) {
    data_ = std::make_unique<Complex[]>(8);
    capacity_ = 8;
  }
  *(data_.get() + (head_ % capacity_)) = value;
  head_ += 1;
}

void QueueArr::Pop() noexcept {
  if (!IsEmpty()) {
    tail_ = tail_ + 1;
  }
}

Complex& QueueArr::Top() {
  if (IsEmpty()) {
    throw std::out_of_range("Cannot get an element of empty queue");
  }
  return *(data_.get() + (tail_ % capacity_));
}

const Complex& QueueArr::Top() const {
  if (IsEmpty()) {
    throw std::out_of_range("Cannot get an element of empty queue");
  }
  return *(data_.get() + (tail_ % capacity_));
}

void QueueArr::Clear() {
  while (!IsEmpty()) {
    Pop();
  }
}