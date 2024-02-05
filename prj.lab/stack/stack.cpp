#include "stack.hpp"

#include <algorithm>
#include <stdexcept>

Stack::Stack(const Stack& copy)
  : size_(copy.Size())
  , capacity_(size_){
  bottom_ptr_ = new Complex[size_];
  std::copy(copy.bottom_ptr_, (copy.bottom_ptr_ + size_), bottom_ptr_);
}

Stack::~Stack() {
  delete[] bottom_ptr_;
  bottom_ptr_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

Stack& Stack::operator=(const Stack& value) {
  if (this != &value) {
    delete[] bottom_ptr_;
    size_ = value.Size();
    capacity_ = size_;
    bottom_ptr_ = new Complex[size_];
    std::copy(value.bottom_ptr_, (value.bottom_ptr_ + size_), bottom_ptr_);
  }
  return *this;
}

std::ptrdiff_t Stack::Size() const noexcept {
  return size_;
}