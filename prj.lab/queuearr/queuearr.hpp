#pragma once

#include <cstddef>

#include <complex/complex.hpp>

class QueueArr {
public:
  QueueArr() = default;
	QueueArr(const QueueArr& copy);
  ~QueueArr();

  QueueArr& operator=(const QueueArr& value);

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Push(const Complex& value);
  void Pop() noexcept;

	[[nodiscard]] Complex& Top();
  [[nodiscard]] const Complex& Top() const;

	void Clear();
private:
  Complex* data_ = nullptr;
  std::ptrdiff_t head_ = 0;
  std::ptrdiff_t tail_ = 0;
  std::ptrdiff_t capacity_ = 0;
};