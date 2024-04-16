#pragma once

#include <cstddef>
#include <stdexcept>

template <class T>
class StackLstT final {
public:
  [[nodiscard]] StackLstT() = default;
  [[nodiscard]] explicit StackLstT(const StackLstT& copy);
  StackLstT(StackLstT&& copy) noexcept;
  ~StackLstT();

  StackLstT& operator=(const StackLstT& value);
  StackLstT& operator=(StackLstT&& value) noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] T& Top();
  [[nodiscard]] const T& Top() const;

  void Push(const T& value);
  void Pop() noexcept;

  void Clear() noexcept;
private:
  struct Node {
    T value;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  std::ptrdiff_t size_ = 0;
};

template <class T>
StackLstT<T>::StackLstT<T>(const StackLstT& copy) {
  if (copy.IsEmpty()) return;
  //reserving space
  for (int i = 0; i < copy.size_; i++) Push(copy.head_->value);
  //setting values;
  Node* copyNode = copy.head_;
  Node* node = head_;
  while (copyNode != nullptr) {
    node->value = copyNode->value;
    copyNode = copyNode->next;
    node = node->next;
  }
}

template <class T>
StackLstT<T>::StackLstT<T>(StackLstT&& copy) noexcept {
  std::swap(head_, copy.head_);
}

template <class T>
StackLstT<T>::~StackLstT<T>() {
  Clear();
}

template <class T>
StackLstT<T>& StackLstT<T>::operator=(const StackLstT<T>& value) {
  if (this != &value) {
    if (value.IsEmpty()) return *this;
    //reserving space
    if (value.size_ > size_) {
      int diff = value.size_ - size_;
      for (int i = 0; i < diff; i += 1) Push(value.head_->value);
    }
    else {
      for (int i = 0; i < size_ - value.size_; i += 1) Pop();
    }
    //setting values;
    Node* valueNode = value.head_;
    Node* node = head_;
    while (valueNode != nullptr) {
      node->value = valueNode->value;
      valueNode = valueNode->next;
      node = node->next;
    }
  }
  return *this;
}

template <class T>
StackLstT<T>& StackLstT<T>::operator=(StackLstT<T>&& value) noexcept {
  if (this != &value) {
    head_ = value.head_;
    value.head_ = nullptr;
  }
  return *this;
}

template <class T>
bool StackLstT<T>::IsEmpty() const noexcept {
  return head_ == nullptr;
}

template <class T>
void StackLstT<T>::Push(const T& value) {
  head_ = new Node{ value, head_ };
  size_ += 1;
}

template <class T>
void StackLstT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
    temp = nullptr;
    size_ -= 1;
  }
}

template <class T>
T& StackLstT<T>::Top() {
  if (IsEmpty()) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return head_->value;
}

template <class T>
const T& StackLstT<T>::Top() const {
  if (IsEmpty()) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return head_->value;
}

template <class T>
void StackLstT<T>::Clear()  noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}