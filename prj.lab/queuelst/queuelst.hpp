#pragma once

#include <complex/complex.hpp>

class QueueLst {
public:
  QueueLst() = default;
	QueueLst(const QueueLst& copy);
  ~QueueLst();

  QueueLst& operator=(const QueueLst& value);

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Push(const Complex& value);
  void Pop() noexcept;

	[[nodiscard]] Complex& Top();
  [[nodiscard]] const Complex& Top() const;

	void Clear();
private:
	struct Node {
		Complex value;
		Node* next = nullptr;
	};
	Node* head_ = nullptr;
	Node* tail_ = nullptr;
};