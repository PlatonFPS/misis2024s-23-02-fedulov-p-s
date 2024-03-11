#pragma once

#include <cstddef>
#include <memory>
#include<complex/complex.hpp>

class StackArr {
public:
  StackArr() = default;
  explicit StackArr(const StackArr& copy);
  StackArr(StackArr&& copy) noexcept;
  ~StackArr();

  StackArr& operator=(const StackArr& value);
  StackArr& operator=(StackArr&& copy) noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] Complex& Top();
  [[nodiscard]] const Complex& Top() const;

  void Push(const Complex& value);
  void Pop() noexcept;

  void Clear() noexcept;
private:
  std::ptrdiff_t top_ = 0;
  std::ptrdiff_t capacity_ = 0;
  std::unique_ptr<Complex[]> bottom_ptr_;
};
