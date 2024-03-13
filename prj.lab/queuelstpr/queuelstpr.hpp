#pragma once

#include <cstddef>

class QueueLstPr {
public:
  QueueLstPr() = default;
  QueueLstPr(const QueueLstPr& copy);
  QueueLstPr(QueueLstPr&& copy) noexcept;

  ~QueueLstPr();

  QueueLstPr& operator=(const QueueLstPr& value);
  QueueLstPr& operator=(QueueLstPr&& value) noexcept;

  bool IsEmpty() const noexcept;

  void Push(float value);

  float& Top();
  const float& Top() const;

  void Pop() noexcept;
  void Clear() noexcept;

private:
  struct Node {
    float value;
    Node* next = nullptr;
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  ptrdiff_t size_ = 0;
};