#include "queuelstpr.hpp"
#include <stdexcept>

QueueLstPr::QueueLstPr(const QueueLstPr& copy) {
  if (!copy.IsEmpty()) {
    head_ = new Node { copy.head_->value, nullptr };
    Node* temp = head_;
    Node* copy_temp = copy.head_->next;
    while (copy_temp != nullptr) {
      temp->next = new Node { copy_temp->value, nullptr };
      temp = temp->next;
      copy_temp = copy_temp->next;
    }
  }
}

QueueLstPr::QueueLstPr(QueueLstPr&& copy) noexcept {
  if (!copy.IsEmpty()) {
    head_ = new Node { copy.head_->value, nullptr };
    Node* temp = head_;
    copy.head_ = copy.head_->next;
    Node* copy_temp = copy.head_->next;
    while (copy_temp != nullptr) {
      temp->next = new Node{ copy_temp->value, nullptr };
      temp = temp->next;
      copy_temp = copy_temp->next;
    }
  }
}

QueueLstPr::~QueueLstPr() {
  Clear();
}

QueueLstPr& QueueLstPr::operator=(const QueueLstPr& copy) {
  return *this;
}

QueueLstPr& QueueLstPr::operator=(QueueLstPr&& copy) noexcept {
  return *this;
}

bool QueueLstPr::IsEmpty() const noexcept {
  return (head_ == nullptr);
}

void QueueLstPr::Push(float value) {
  if (IsEmpty()) {
    head_ = new Node{ value, head_ };
  } else {
    if (head_->value > value) {
      head_ = new Node{ value, head_ };
    } else {
      Node* temp = head_;
      while (temp->next != nullptr && temp->next->value < value) {
        temp = temp->next;
      }
      temp->next = new Node{ value, temp->next };
    }
  }
}

float& QueueLstPr::Top() {
  if(IsEmpty()) {
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
  }
}

void QueueLstPr::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}