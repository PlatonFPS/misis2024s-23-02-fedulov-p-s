#pragma once 

#include <cstddef>
#include <memory>
#include <algorithm>
#include <stdexcept>

template <class T>
class StackArr final {
public:
  StackArr() = default;
  explicit StackArr(const StackArr& copy);
  StackArr(StackArr&& copy) noexcept;
  ~StackArr();

  StackArr& operator=(const StackArr& value);
  StackArr& operator=(StackArr&& copy) noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] T& Top();
  [[nodiscard]] const T& Top() const;

  void Push(const T& value);
  void Pop() noexcept;

  void Clear() noexcept;
private:
  std::ptrdiff_t top_ = 0;
  std::ptrdiff_t capacity_ = 0;
  std::unique_ptr<T[]> bottom_ptr_;
};

template <class T>
StackArr<T>::StackArr<T>(const StackArr<T>& copy)
  : top_(copy.top_)
  , capacity_(top_) {
  bottom_ptr_ = std::make_unique<T[]>(capacity_);
  std::copy(copy.bottom_ptr_.get(), (copy.bottom_ptr_.get() + top_), bottom_ptr_.get());
}

template <class T>
StackArr<T>::StackArr<T>(StackArr<T>&& copy) noexcept {
  std::swap(bottom_ptr_, copy.bottom_ptr_);
  std::swap(top_, copy.top_);
  std::swap(capacity_, copy.capacity_);
}

template <class T>
StackArr<T>::~StackArr<T>() {
  bottom_ptr_.reset();
  top_ = 0;
  capacity_ = 0;
}

template <class T>
StackArr<T>& StackArr<T>::operator=(const StackArr<T>& value) {
  if (this != &value) {
    bottom_ptr_.reset();
    top_ = value.top_;
    capacity_ = top_;
    bottom_ptr_ = std::make_unique<T[]>(capacity_);
    std::copy(value.bottom_ptr_.get(), (value.bottom_ptr_.get() + top_), bottom_ptr_.get());
  }
  return *this;
}

template <class T>
StackArr<T>& StackArr<T>::operator=(StackArr<T>&& value) noexcept {
  if (this != &value) {
    bottom_ptr_ = std::move(value.bottom_ptr_);
    top_ = value.top_;
    capacity_ = value.capacity_;
    value.bottom_ptr_.release();
    value.top_ = 0;
    value.capacity_ = 0;
  }
  return *this;
}

template <class T>
bool StackArr<T>::IsEmpty() const noexcept {
  return top_ == 0;
}

template <class T>
T& StackArr<T>::Top() {
  if (top_ == 0) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return *(bottom_ptr_.get() + top_ - 1);
}

template <class T>
const T& StackArr<T>::Top() const {
  if (top_ == 0) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return *(bottom_ptr_.get() + top_ - 1);
}

template <class T>
void StackArr<T>::Pop() noexcept {
  if (top_ != 0) {
    top_ -= 1;
  }
}

template <class T>
void StackArr<T>::Push(const T& value) {
  if (capacity_ == top_) {
    if (capacity_ == 0) {
      capacity_ = 8;
    }
    else {
      capacity_ = capacity_ * 2;
    }
    std::unique_ptr<T[]> temp_ptr = std::make_unique<T[]>(capacity_);
    std::copy(bottom_ptr_.get(), (bottom_ptr_.get() + top_), temp_ptr.get());
    bottom_ptr_.reset();
    bottom_ptr_ = std::move(temp_ptr);
  }
  top_ += 1;
  *(bottom_ptr_.get() + top_ - 1) = value;
}

template <class T>
void StackArr<T>::Clear() noexcept {
  top_ = 0;
}