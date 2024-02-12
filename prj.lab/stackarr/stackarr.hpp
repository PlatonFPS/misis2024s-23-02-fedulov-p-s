#pragma once

#include <cstddef>

#include<complex/complex.hpp>

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
  std::ptrdiff_t top_ = 0;
  std::ptrdiff_t capacity_ = 0;
  Complex* bottom_ptr_ = nullptr;
};
