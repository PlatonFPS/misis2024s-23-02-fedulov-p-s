#pragma once

#include <cstddef>
#include <stdexcept>

template <class T>
class QueueLstPrT final {
public:
  QueueLstPrT() = default;
  QueueLstPrT(const QueueLstPrT<T>& copy);
  QueueLstPrT(QueueLstPrT<T>&& copy) noexcept;

  ~QueueLstPrT();

  QueueLstPrT<T>& operator=(const QueueLstPrT<T>& value);
  QueueLstPrT<T>& operator=(QueueLstPrT<T>&& value) noexcept;

  bool IsEmpty() const noexcept;

  void Push(float value);

  float& Top();
  const float& Top() const;

  void Pop() noexcept;
  void Clear() noexcept;

private:
  struct Node {
    T value;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  ptrdiff_t size_ = 0;
};

/*QueueLstPr::QueueLstPr(const QueueLstPr& copy) {
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

QueueLstPr::QueueLstPr(QueueLstPr&& copy) noexcept {
  std::swap(head_, copy.head_);
  std::swap(tail_, copy.tail_);
  std::swap(size_, copy.size_);
}

QueueLstPr::~QueueLstPr() {
  Clear();
}

QueueLstPr& QueueLstPr::operator=(const QueueLstPr& value) {
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

QueueLstPr& QueueLstPr::operator=(QueueLstPr&& value) noexcept {
  if (this != &value) {
    head_ = value.head_;
    tail_ = value.tail_;
    size_ = value.size_;
    value.head_ = nullptr;
    value.tail_ = nullptr;
    value.size_ = 0;
  }
  return *this;
}

bool QueueLstPr::IsEmpty() const noexcept {
  return (head_ == nullptr);
}

void QueueLstPr::Push(float value) {
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

float& QueueLstPr::Top() {
  if (IsEmpty()) {
    throw std::logic_error("Queue is empty");
  }
  return head_->value;
}

const float& QueueLstPr::Top() const {
  if (IsEmpty()) {
    throw std::logic_error("Queue is empty");
  }
  return head_->value;
}

void QueueLstPr::Pop() noexcept {
  if (!IsEmpty()) {
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
    temp = nullptr;
    size_ -= 1;
  }
}

void QueueLstPr::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}*/