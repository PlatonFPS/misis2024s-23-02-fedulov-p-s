#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

template <class T>
class QueueLstPrT final {
public:
  QueueLstPrT<T>() = default;
  QueueLstPrT<T>(const QueueLstPrT<T>& copy);
  QueueLstPrT<T>(QueueLstPrT<T>&& copy) noexcept;

  ~QueueLstPrT();

  QueueLstPrT<T>& operator=(const QueueLstPrT<T>& values);
  QueueLstPrT<T>& operator=(QueueLstPrT<T>&& value) noexcept;

  bool Compare(const std::vector<T>& values) const;
  bool Compare(const QueueLstPrT<T>& queue) const;

  bool IsEmpty() const noexcept;

  void Push(T value);

  T& Top();
  const T& Top() const;

  void Pop() noexcept;
  void Clear() noexcept;

private:
  struct Node {
    T value;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  ptrdiff_t size_ = 0;
};

template<class T>
bool QueueLstPrT<T>::Compare(const std::vector<T>& values) const {
  Node* temp = head_;
  for (int i = 0; i < values.size(); ++i) {
    if (temp == nullptr) return false;
    if (temp->value != values[i]) return false;
    temp = temp->next;
  }
  return true;
}

template<class T>
bool QueueLstPrT<T>::Compare(const QueueLstPrT<T>& queue) const {
  Node* thisTemp = head_;
  Node* otherTemp = queue.head_;
  while (!(thisTemp == nullptr && otherTemp == nullptr)) {
    if (thisTemp == nullptr) return false;
    if (otherTemp == nullptr) return false;
    if (thisTemp->value != otherTemp->value) return false;
    thisTemp = thisTemp->next;
    otherTemp = otherTemp->next;
  }
  return true;
}

template <class T>
QueueLstPrT<T>::QueueLstPrT(const QueueLstPrT<T>& copy) {
  if (!copy.IsEmpty()) {
    size_ = copy.size_;
    head_ = new Node{ copy.head_->value, nullptr };
    Node* temp = head_;
    Node* copy_temp = copy.head_->next;
    while (copy_temp != nullptr) {
      temp->next = new Node{ copy_temp->value, nullptr };
      temp = temp->next;
      copy_temp = copy_temp->next;
    }
  }
}

template <class T>
QueueLstPrT<T>::QueueLstPrT(QueueLstPrT<T>&& copy) noexcept {
  std::swap(head_, copy.head_);
  std::swap(size_, copy.size_);
}

template <class T>
QueueLstPrT<T>::~QueueLstPrT() {
  Clear();
}

template <class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(const QueueLstPrT<T>& value) {
  if (this != &value) {
    while (size_ > value.size_) Pop();
    Node* head = head_;
    Node* vHead = value.head_;
    while (head != nullptr && vHead != nullptr) {
      head->value = vHead->value;
      vHead = vHead->next;
      head = head->next;
    }
    while (vHead != nullptr) {
      Push(vHead->value);
      vHead = vHead->next;
    }
  }
  return *this;
}

template <class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(QueueLstPrT<T>&& value) noexcept {
  if (this != &value) {
    head_ = value.head_;
    size_ = value.size_;
    value.head_ = nullptr;
    value.size_ = 0;
  }
  return *this;
}

template <class T>
bool QueueLstPrT<T>::IsEmpty() const noexcept {
  return (head_ == nullptr);
}

template <class T>
void QueueLstPrT<T>::Push(T value) {
  if (IsEmpty()) {
    head_ = new Node{ value, head_ };
  }
  else {
    if (head_->value > value) {
      head_ = new Node{ value, head_ };
    }
    else {
      Node* temp = head_;
      while (temp->next != nullptr && temp->next->value < value) {
        temp = temp->next;
      }
      temp->next = new Node{ value, temp->next };
    }
  }
  size_ += 1;
}

template <class T>
T& QueueLstPrT<T>::Top() {
  if (IsEmpty()) {
    throw std::logic_error("Queue is empty");
  }
  return head_->value;
}

template <class T>
const T& QueueLstPrT<T>::Top() const {
  if (IsEmpty()) {
    throw std::logic_error("Queue is empty");
  }
  return head_->value;
}

template <class T>
void QueueLstPrT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
    temp = nullptr;
    size_ -= 1;
  }
}

template <class T>
void QueueLstPrT<T>::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}