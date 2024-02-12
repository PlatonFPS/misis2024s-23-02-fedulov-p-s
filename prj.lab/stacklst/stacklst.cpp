#include "stacklst.hpp"
#include<complex/complex.hpp>

#include <algorithm>
#include <stdexcept>

StackArr::StackArr(const StackArr& copy)
  : top_(copy.top_)
  , capacity_(top_){
  bottom_ptr_ = new Complex[top_];
  std::copy(copy.bottom_ptr_, (copy.bottom_ptr_ + top_), bottom_ptr_);
}

StackArr::~StackArr() {
  delete[] bottom_ptr_;
  bottom_ptr_ = nullptr;
  top_ = 0;
  capacity_ = 0;
}

StackArr& StackArr::operator=(const StackArr& value) {
  if (this != &value) {
    delete[] bottom_ptr_;
    top_ = value.top_;
    capacity_ = top_;
    bottom_ptr_ = new Complex[top_];
    std::copy(value.bottom_ptr_, (value.bottom_ptr_ + top_), bottom_ptr_);
  }
  return *this;
}

bool StackArr::IsEmpty() const noexcept {
  return top_ == 0;
}

Complex& StackArr::Top() {
  if (top_ == 0) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  else {
    return *(bottom_ptr_ + top_ - 1);
  }
}

const Complex& StackArr::Top() const {
  if (top_ == 0) {
    throw std::out_of_range("Can't get top element of empty stack");
  } else {
    return *(bottom_ptr_ + top_ - 1);
  }
}

void StackArr::Pop() noexcept {
  if (top_ != 0) {
    top_ -= 1;
  }
}

void StackArr::Push(const Complex& value) {
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
  *(bottom_ptr_ + top_ - 1) = value;
}

void StackArr::Clear() noexcept {
  top_ = 0;
}