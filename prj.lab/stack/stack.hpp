#ifndef STACK_HPP
#define STACK_HPP

#include<complex/complex.hpp>

#include <cstddef>

class Stack {
public:
  [[nodiscard]] Stack() = default;
  [[nodiscard]] explicit Stack(const Stack& copy);
  ~Stack();

  Stack& operator=(const Stack& value);

  [[nodiscard]] std::ptrdiff_t Size() const noexcept;

  [[nodiscard]] const Complex& Top();
  void Push(const Complex& value);
  void Pop() noexcept;
  [[nodiscard]] bool IsEmpty() noexcept;
private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
  Complex* bottom_ptr_ = nullptr;
};

#endif //STACK_HPP