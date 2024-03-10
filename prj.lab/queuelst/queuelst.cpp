#include "queuelst.hpp"
#include <complex/complex.hpp>
#include <stdexcept>

QueueLst::QueueLst(const QueueLst& copy) {
  Node* temp = copy.head_;
  while (temp != nullptr) {
    Push(temp->value);
    temp = temp->next;
  }
}

QueueLst::~QueueLst() {
  Clear();
}

QueueLst& QueueLst::operator=(const QueueLst& value) {
  Clear();
  Node* temp = value.head_;
  while (temp != nullptr) {
    Push(temp->value);
    temp = temp->next;
  }
  return *this;
}

bool QueueLst::IsEmpty() const noexcept {
  return (head_ == nullptr);
}

void QueueLst::Push(const Complex& value) {
  Node* temp = new Node{ value, nullptr };
  if (!IsEmpty()) {
    tail_->next = temp;
    
  } else {
    head_ = temp;
  }
  tail_ = temp;
  temp = nullptr;
}

void QueueLst::Pop() noexcept {
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

Complex& QueueLst::Top() {
  if (IsEmpty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->value;
}

const Complex& QueueLst::Top() const {
  if (IsEmpty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->value;
}

void QueueLst::Clear() {
  while (!IsEmpty()) {
    Pop();
  }
}