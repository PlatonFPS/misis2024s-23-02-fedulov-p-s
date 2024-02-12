#pragma once

#include <cstddef>

struct Complex;

class StackArr {
public:
  [[nodiscard]] StackArr() = default;
  [[nodiscard]] explicit StackArr(const StackArr& copy);
  ~StackArr();

  StackArr& operator=(const StackArr& value);

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
  std::ptrdiff_t size_ = 0;
  Complex* bottom_ptr_ = nullptr;
};
