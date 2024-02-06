#pragma once

#include <cstddef>

struct Complex;

class StackArr {
public:
  [[nodiscard]] StackArr() = default;
  [[nodiscard]] explicit StackArr(const StackArr& copy);
  ~StackArr();

  StackArr& operator=(const StackArr& value);

  [[nodiscard]] bool IsEmpty() noexcept;

  [[nodiscard]] const Complex& Top();
  void Push(const Complex& value);
  void Pop() noexcept;
private:
  std::ptrdiff_t top_ = 0;
  std::ptrdiff_t capacity_ = 0;
  Complex* bottom_ptr_ = nullptr;
};
