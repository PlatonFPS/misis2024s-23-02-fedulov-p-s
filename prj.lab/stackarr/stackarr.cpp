#include "stackarr.hpp"

#include <algorithm>
#include <stdexcept>

StackArr::StackArr(const StackArr& copy)
  : top_(copy.top_)
  , capacity_(top_){
  bottom_ptr_ = std::make_unique<Complex[]>(capacity_);
  std::copy(copy.bottom_ptr_.get(), (copy.bottom_ptr_.get() + top_), bottom_ptr_.get());
}

StackArr::StackArr(StackArr&& copy) noexcept {
  std::swap(top_, copy.top_);
}

StackArr::~StackArr() {
  bottom_ptr_.reset();
  top_ = 0;
  capacity_ = 0;
}

StackArr& StackArr::operator=(const StackArr& value) {
  if (this != &value) {
    bottom_ptr_.reset();
    top_ = value.top_;
    capacity_ = top_;
    bottom_ptr_ = std::make_unique<Complex[]>(capacity_);
    std::copy(value.bottom_ptr_.get(), (value.bottom_ptr_.get() + top_), bottom_ptr_.get());
  }
  return *this;
}

StackArr& StackArr::operator=(StackArr&& copy) noexcept {

}

bool StackArr::IsEmpty() const noexcept {
  return top_ == 0;
}

Complex& StackArr::Top() {
  if (top_ == 0) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return *(bottom_ptr_.get() + top_ - 1);
}

const Complex& StackArr::Top() const {
  if (top_ == 0) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return *(bottom_ptr_.get() + top_ - 1);
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
    std::unique_ptr<Complex[]> temp_ptr = std::make_unique<Complex[]>(capacity_);
    std::copy(bottom_ptr_.get(), (bottom_ptr_.get() + top_), temp_ptr.get());
    bottom_ptr_.reset();
    bottom_ptr_ = std::move(temp_ptr);
  }
  top_ += 1;
  *(bottom_ptr_.get() + top_ - 1) = value;
}

void StackArr::Clear() noexcept {
  top_ = 0;
}