#pragma once

#include <stdexcept>s
#include <vector>

template <class T>
class QueueLstT final {
public:
	QueueLstT<T>() = default;
	QueueLstT<T>(const QueueLstT<T>& copy);
	QueueLstT<T>(QueueLstT<T>&& copy) noexcept;
	~QueueLstT<T>();

	QueueLstT<T>& operator=(const QueueLstT<T>& value);
	QueueLstT<T>& operator=(QueueLstT<T>&& value) noexcept;

	[[nodiscard]] bool IsEmpty() const noexcept;

	void Push(const T& value);
	void Pop() noexcept;

	[[nodiscard]] T& Top();
	[[nodiscard]] const T& Top() const;

	void Clear();

  bool CompareWithVector(const std::vector<T>& other) const;
  bool Compare(const QueueLstT<T>& other) const;
private:
	struct Node {
		T value;
		Node* next = nullptr;
	};
	Node* head_ = nullptr;
	Node* tail_ = nullptr;
};

template <class T>
bool QueueLstT<T>::CompareWithVector(const std::vector<T>& other) const {
  Node* temp = head_;
  for (int i = 0; i < other.size(); i += 1) {
    if (temp->value != other[i]) {
      return false;
    }
    temp = temp->next;
  }
  return true;
}

template <class T>
bool QueueLstT<T>::Compare(const QueueLstT<T>& other) const {
  Node* temp = head_;
  Node* copy = other.head_;
  while (temp != nullptr && copy != nullptr) {
    if (temp->value != copy->value) {
      return false;
    }
    temp = temp->next;
    copy = copy->next;
  }
  return (temp == nullptr && copy == nullptr);
}

template <class T>
QueueLstT<T>::QueueLstT<T>(const QueueLstT<T>& copy) {
  Node* temp = copy.head_;
  while (temp != nullptr) {
    Push(temp->value);
    temp = temp->next;
  }
}

template <class T>
QueueLstT<T>::QueueLstT<T>(QueueLstT<T>&& copy) noexcept {
  std::swap(head_, copy.head_);
  std::swap(tail_, copy.tail_);
}

template <class T>
QueueLstT<T>::~QueueLstT<T>() {
  Clear();
}

template <class T>
QueueLstT<T>& QueueLstT<T>::operator=(const QueueLstT<T>& value) {
  if (this != &value) {
    Clear();
    Node* temp = value.head_;
    while (temp != nullptr) {
      Push(temp->value);
      temp = temp->next;
    }
  }
  return *this;
}

template <class T>
QueueLstT<T>& QueueLstT<T>::operator=(QueueLstT<T>&& value) noexcept {
  if (this != &value) {
    head_ = value.head_;
    tail_ = value.tail_;
    value.head_ = nullptr;
    value.tail_ = nullptr;
  }
  return *this;
}

template <class T>
bool QueueLstT<T>::IsEmpty() const noexcept {
  return (head_ == nullptr);
}

template <class T>
void QueueLstT<T>::Push(const T& value) {
  Node* temp = new Node{ value, nullptr };
  if (!IsEmpty()) {
    tail_->next = temp;

  }
  else {
    head_ = temp;
  }
  tail_ = temp;
  temp = nullptr;
}

template <class T>
void QueueLstT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    Node* temp = head_;
    head_ = head_->next;
    if (temp == tail_) {
      tail_ = nullptr;
    }
    delete temp;
    temp = nullptr;
  }
}

template <class T>
T& QueueLstT<T>::Top() {
  if (IsEmpty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->value;
}

template <class T>
const T& QueueLstT<T>::Top() const {
  if (IsEmpty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->value;
}

template <class T>
void QueueLstT<T>::Clear() {
  while (!IsEmpty()) {
    Pop();
  }
}