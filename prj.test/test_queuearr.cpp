#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<queuearr/queuearr.hpp>
#include<complex/complex.hpp>

Complex a(1, 2);
Complex b(1, 3);

TEST_CASE("Initialization") {
  QueueArr queue;
  CHECK_THROWS(queue.Top());
  CHECK(queue.IsEmpty());
  CHECK_NOTHROW(queue.Pop());
  queue.Push(a);
  CHECK_NOTHROW(queue.Top());
  queue.Push(b);
}

TEST_CASE("Push, Pop, Top, Clear") {
  QueueArr queue;
  CHECK_THROWS(queue.Top());
  CHECK(queue.IsEmpty());
  CHECK_NOTHROW(queue.Pop());

  queue.Push(a);
  CHECK_NOTHROW(queue.Top());
  CHECK_EQ(queue.Top(), a);

  queue.Push(b);
  CHECK_EQ(queue.Top(), a);
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue.Top(), b);
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue.IsEmpty(), true);

  queue.Push(a);
  CHECK_NOTHROW(queue.Top());
  queue.Clear();
  CHECK_EQ(queue.IsEmpty(), true);
}

TEST_CASE("Copy ctor") {
  QueueArr queue;
  queue.Push(a);
  queue.Push(b);

  QueueArr queue2(queue);
  CHECK_EQ(queue2.Top(), queue.Top());
  CHECK_EQ(queue2.Top(), a);
  CHECK_NOTHROW(queue2.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue2.Top(), queue.Top());
  CHECK_EQ(queue2.Top(), b);
  CHECK_NOTHROW(queue2.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue2.IsEmpty(), queue.IsEmpty());
  CHECK_EQ(queue2.IsEmpty(), true);
}

TEST_CASE("Copy operator") {
  QueueArr queue3;
  CHECK_THROWS(queue3.Top());
  CHECK(queue3.IsEmpty());
  CHECK_NOTHROW(queue3.Pop());
  queue3.Push(a);
  CHECK_NOTHROW(queue3.Top());
  queue3.Push(b);

  QueueArr queue4 = queue3;
  CHECK_EQ(queue4.Top(), queue3.Top());
  CHECK_EQ(queue4.Top(), a);
  CHECK_NOTHROW(queue4.Pop());
  CHECK_NOTHROW(queue3.Pop());
  CHECK_EQ(queue4.Top(), queue3.Top());
  CHECK_EQ(queue4.Top(), b);
  CHECK_NOTHROW(queue4.Pop());
  CHECK_NOTHROW(queue3.Pop());
  CHECK_EQ(queue4.IsEmpty(), queue3.IsEmpty());
  CHECK_EQ(queue4.IsEmpty(), true);
}

TEST_CASE("Cycle") {
  QueueArr queue;
  for(int i_cycle = 0; i_cycle < 100; i_cycle++) {
    queue.Push(a);
    queue.Push(b);
    CHECK_EQ(queue.Top(), a);
    queue.Pop();
    CHECK_EQ(queue.Top(), b);
    queue.Pop();
    CHECK_EQ(queue.IsEmpty(), true);
  }

  queue.Push(a);
  queue.Push(b);

  QueueArr queue2(queue);
  CHECK_EQ(queue2.Top(), queue.Top());
  CHECK_EQ(queue2.Top(), a);
  CHECK_NOTHROW(queue2.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue2.Top(), queue.Top());
  CHECK_EQ(queue2.Top(), b);
  CHECK_NOTHROW(queue2.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue2.IsEmpty(), queue.IsEmpty());
  CHECK_EQ(queue2.IsEmpty(), true);

  queue.Push(a);
  queue.Push(b);

  QueueArr queue3 = queue;
  CHECK_EQ(queue3.Top(), queue.Top());
  CHECK_EQ(queue3.Top(), a);
  CHECK_NOTHROW(queue3.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue3.Top(), queue.Top());
  CHECK_EQ(queue3.Top(), b);
  CHECK_NOTHROW(queue3.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue3.IsEmpty(), queue.IsEmpty());
  CHECK_EQ(queue3.IsEmpty(), true);
}

TEST_CASE("time test") {
  QueueArr queue1;
  for (int i = 0; i < 10000; i++) {
    queue1.Push(a);
  }
  auto start = std::chrono::steady_clock::now();
  QueueArr queue2(queue1);
  auto end = std::chrono::steady_clock::now();
  CHECK_EQ(queue2.Top(), a);
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  start = std::chrono::steady_clock::now();
  QueueArr queue3(std::move(queue1));
  end = std::chrono::steady_clock::now();
  CHECK_EQ(queue3.Top(), a);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  QueueArr queue4;
  for (int i = 0; i < 10000; i++) {
    queue4.Push(a);
  }
  QueueArr queue5;
  start = std::chrono::steady_clock::now();
  queue5 = queue4;
  end = std::chrono::steady_clock::now();
  CHECK_EQ(queue5.Top(), a);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  start = std::chrono::steady_clock::now();
  QueueArr queue6 = std::move(queue4);
  end = std::chrono::steady_clock::now();
  CHECK_EQ(queue6.Top(), a);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
}