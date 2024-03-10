#pragma once

#include <cstddef>

#include<complex/complex.hpp>

class StackLst {
public:
  [[nodiscard]] StackLst() = default;
  [[nodiscard]] explicit StackLst(const StackLst& copy);
  StackLst(StackLst&& copy) noexcept;
  ~StackLst();

  StackLst& operator=(const StackLst& value);

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] Complex& Top();
  [[nodiscard]] const Complex& Top() const;

  void Push(const Complex& value);
  void Pop() noexcept;

  void Clear() noexcept;
private:
  struct Node {
    Complex value;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  std::ptrdiff_t size_ = 0;
};
