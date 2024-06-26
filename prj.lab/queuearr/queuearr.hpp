#pragma once

#include <cstddef>
#include <memory>
#include <complex/complex.hpp>

class QueueArr final {
public:
  QueueArr() = default;
	QueueArr(const QueueArr& copy);
  QueueArr(QueueArr&& copy) noexcept;
  ~QueueArr() = default;

  QueueArr& operator=(const QueueArr& value);
  QueueArr& operator=(QueueArr&& value) noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Push(const Complex& value);
  void Pop() noexcept;

	[[nodiscard]] Complex& Top();
  [[nodiscard]] const Complex& Top() const;

	void Clear();
private:
  std::unique_ptr<Complex[]> data_;
  std::ptrdiff_t head_ = 0;
  std::ptrdiff_t tail_ = 0;
  std::ptrdiff_t capacity_ = 0;
};