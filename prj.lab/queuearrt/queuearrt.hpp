#pragma once

#include <cstddef>
#include <stdexcept>
#include <memory>
#include <vector>

template <class T>
class QueueArrT final {
public:
  QueueArrT<T>() = default;
  QueueArrT<T>(const QueueArrT<T>& copy);
  QueueArrT<T>(QueueArrT<T>&& copy) noexcept;
  ~QueueArrT() = default;

  QueueArrT<T>& operator=(const QueueArrT<T>& value);
  QueueArrT<T>& operator=(QueueArrT<T>&& value) noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Push(const T& value);
  void Pop() noexcept;

  [[nodiscard]] T& Top();
  [[nodiscard]] const T& Top() const;

  void Clear();

  bool CompareWithVector(const std::vector<T>& vec) const;
  bool Compare(const QueueArrT<T>& other) const;
private:
  std::unique_ptr<T[]> data_;
  std::ptrdiff_t head_ = 0;
  std::ptrdiff_t tail_ = 0;
  std::ptrdiff_t capacity_ = 0;
};

template <class T>
bool QueueArrT<T>::CompareWithVector(const std::vector<T>& vec) const {
  if (vec.size() != head_ - tail_) {
    return false;
  }
  for (int i = tail_; i < head_; i += 1) {
    if(vec[i - tail_] != *(data_.get() + i % capacity_)) {
      return false;
    }
  }
  return true;
}

template <class T>
bool QueueArrT<T>::Compare(const QueueArrT<T>& other) const {
  if(head_ - tail_ != other.head_ - other.tail_) {
    return false;
  }
  for (int i = tail_, j = other.tail_; i < head_ && j < other.head_; i += 1, j += 1) {
    if (*(other.data_.get() + j % other.capacity_) != *(data_.get() + i % capacity_)) {
      return false;
    }
  }
  return true;
}

template <class T>
QueueArrT<T>::QueueArrT<T>(const QueueArrT<T>& copy)
  : head_(0)
  , tail_(0) {
  data_ = std::make_unique<T[]>(copy.head_ - copy.tail_);
  capacity_ = copy.head_ - copy.tail_;
  for (int i = 0; i < copy.head_ - copy.tail_; i++) {
    Push(copy.data_[(copy.tail_ + i) % copy.capacity_]);
  }
}

template <class T>
QueueArrT<T>::QueueArrT<T>(QueueArrT<T>&& copy) noexcept {
  std::swap(data_, copy.data_);
  std::swap(head_, copy.head_);
  std::swap(tail_, copy.tail_);
  std::swap(capacity_, copy.capacity_);
}

template <class T>
QueueArrT<T>& QueueArrT<T>::operator=(const QueueArrT<T>& value) {
  if (this != &value) {
    if (capacity_ < value.head_ - value.tail_) {
      Clear();
      data_ = std::make_unique<T[]>((value.head_ - value.tail_) * 2);
    }
    head_ = 0;
    tail_ = 0;
    for (int i = 0; i < value.head_ - value.tail_; i++) {
      Push(value.data_[(value.tail_ + i) % value.capacity_]);
    }
  }
  return *this;
}

template <class T>
QueueArrT<T>& QueueArrT<T>::operator=(QueueArrT<T>&& value) noexcept {
  if (this != &value) {
    data_ = std::move(value.data_);
    head_ = value.head_;
    tail_ = value.tail_;
    capacity_ = value.capacity_;
    value.data_.release();
    value.head_ = 0;
    value.tail_ = 0;
    value.capacity_ = 0;
  }
  return *this;
}

template <class T>
bool QueueArrT<T>::IsEmpty() const noexcept {
  return head_ == tail_;
}

template <class T>
void QueueArrT<T>::Push(const T& value) {
  if (!IsEmpty() && (head_ % capacity_) == (tail_ % capacity_)) {
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity_ * 2);
    for (int i = 0; i < capacity_; i++) {
      new_data[i] = data_[(tail_ + i) % capacity_];
    }
    data_.reset();
    data_ = std::move(new_data);
    capacity_ *= 2;
    head_ = head_ - tail_;
    tail_ = 0;
  }
  else if (IsEmpty()) {
    data_ = std::make_unique<T[]>(8);
    capacity_ = 8;
  }
  *(data_.get() + (head_ % capacity_)) = value;
  head_ += 1;
}

template <class T>
void QueueArrT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    tail_ = tail_ + 1;
  }
}

template <class T>
T& QueueArrT<T>::Top() {
  if (IsEmpty()) {
    throw std::out_of_range("Cannot get an element of empty queue");
  }
  return *(data_.get() + (tail_ % capacity_));
}

template <class T>
const T& QueueArrT<T>::Top() const {
  if (IsEmpty()) {
    throw std::out_of_range("Cannot get an element of empty queue");
  }
  return *(data_.get() + (tail_ % capacity_));
}

template <class T>
void QueueArrT<T>::Clear() {
  while (!IsEmpty()) {
    Pop();
  }
}