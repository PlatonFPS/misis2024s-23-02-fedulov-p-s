#include "stack.hpp"

#include <algorithm>
#include <stdexcept>

Stack::Stack(const Stack& copy)
  : top_(copy.Size())
  , capacity_(top_){
  bottom_ptr_ = new Complex[top_];
  std::copy(copy.bottom_ptr_, (copy.bottom_ptr_ + top_), bottom_ptr_);
}

Stack::~Stack() {
  delete[] bottom_ptr_;
  bottom_ptr_ = nullptr;
  top_ = 0;
  capacity_ = 0;
}

Stack& Stack::operator=(const Stack& value) {
  if (this != &value) {
    delete[] bottom_ptr_;
    top_ = value.Size();
    capacity_ = top_;
    bottom_ptr_ = new Complex[top_];
    std::copy(value.bottom_ptr_, (value.bottom_ptr_ + top_), bottom_ptr_);
  }
  return *this;
}

std::ptrdiff_t Stack::Size() const noexcept {
  return top_;
}

bool Stack::IsEmpty() noexcept {
  return top_ == 0;
}

const Complex& Stack::Top() {
  if (top_ == 0) {
    throw std::out_of_range("Can't get top element of empty stack");
  } else {
    return *(bottom_ptr_ + top_);
  }
}

void Stack::Pop() noexcept {
  if (top_ != 0) {
    top_ -= 1;
  }
}

void Stack::Push(const Complex& value) {
  if (capacity_ == top_) {
    if (capacity_ == 0) {
      capacity_ = 8;
    } else {
      capacity_ = capacity_ * 2;
    }
    Complex* temp_ptr = new Complex[capacity_];
    std::copy(bottom_ptr_, (bottom_ptr_ + top_), temp_ptr);
    delete[] bottom_ptr_;
    bottom_ptr_ = temp_ptr;
  }
  top_ += 1;
  *(bottom_ptr_ + top_) = value;
}