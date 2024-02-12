#include "stacklst.hpp"

#include <algorithm>
#include <stdexcept>

StackLst::StackLst(const StackLst& copy) {
  //reserving space
  Node* copyNode = copy.head_;
  while (copyNode != nullptr) {
    Push(Complex(0, 0));
    copyNode = copyNode->next;
  }
  //setting values;
  copyNode = copy.head_;
  Node* node = head_;
  while (copyNode != nullptr) {
    node->value = copyNode->value;
    copyNode = copyNode->next;
    node = node->next;
  }
}

StackLst::~StackLst() {
  Clear();
}

StackLst& StackLst::operator=(const StackLst& value) {
  Clear();
  //reserving space
  Node* valueNode = value.head_;
  while (valueNode != nullptr) {
    Push(Complex(0, 0));
    valueNode = valueNode->next;
  }
  //setting values;
  valueNode = value.head_;
  Node* node = head_;
  while (valueNode != nullptr) {
    node->value = valueNode->value;
    valueNode = valueNode->next;
    node = node->next;
  }
  return *this;
}

bool StackLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}

void StackLst::Push(const Complex& value) {
  head_ = new Node{ value, head_ };
}

void StackLst::Pop() noexcept {
  if (!IsEmpty()) {
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
    temp = nullptr;
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