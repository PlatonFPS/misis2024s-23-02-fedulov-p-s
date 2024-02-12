#include "stacklst.hpp"

#include <algorithm>
#include <stdexcept>

StackLst::StackLst(const StackLst& copy) {
  Node* copyNode = copy.head_;
  while (copyNode != nullptr) {
    Push(copyNode->value);
    copyNode = copyNode->next;
  }
}

StackLst::~StackLst() {
  Clear();
}

StackLst& StackLst::operator=(const StackLst& value) {
  Clear();
  Node* valueNode = value.head_;
  while (valueNode != nullptr) {
    Push(valueNode->value);
    valueNode = valueNode->next;
  }
}

bool StackLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}

void StackLst::Push(const Complex& value) {
  Node* temp = new Node;
  temp->value = value;
  if (!IsEmpty()) {
    temp->next = head_;
  }
  head_ = temp;
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
  } else {
    return head_->value;
  }
}

const Complex& StackLst::Top() const {
  if (IsEmpty()) {
    throw std::out_of_range("Can't get top element of empty stack");
  }
  else {
    return head_->value;
  }
}

void StackLst::Clear() {
  while (!IsEmpty()) {
    Pop();
  }
}