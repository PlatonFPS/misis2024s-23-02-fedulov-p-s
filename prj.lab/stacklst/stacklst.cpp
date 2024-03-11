#include "stacklst.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>

StackLst::StackLst(const StackLst& copy) {
  //reserving space
  for (int i = 0; i < copy.size_; i++) Push(Complex(0, 0));
  //setting values;
  Node* copyNode = copy.head_;
  Node* node = head_;
  while (copyNode != nullptr) {
    node->value = copyNode->value;
    copyNode = copyNode->next;
    node = node->next;
  }
}

StackLst::StackLst(StackLst&& copy) noexcept {
  std::swap(head_, copy.head_);
}

StackLst::~StackLst() {
  Clear();
}

StackLst& StackLst::operator=(const StackLst& value) {
  if (this != &value) {
    //reserving space
    if (value.size_ > size_) {
      for (int i = 0; i < value.size_ - size_; i += 1) Push(Complex(0, 0));
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

StackLst& StackLst::operator=(StackLst&& value) noexcept {
  if (this != &value) {
    head_ = value.head_;
    value.head_ = nullptr;
  }
  return *this;
}

bool StackLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}

void StackLst::Push(const Complex& value) {
  head_ = new Node{ value, head_ };
  size_ += 1;
}

void StackLst::Pop() noexcept {
  if (!IsEmpty()) {
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
    temp = nullptr;
    size_ -= 1;
  }
}

Complex& StackLst::Top() {
  if (IsEmpty()) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return head_->value;
}

const Complex& StackLst::Top() const {
  if (IsEmpty()) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  return head_->value;
}

void StackLst::Clear()  noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}