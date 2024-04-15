#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<stacklstt/stacklstt.hpp>
#include<complex/complex.hpp>

static const Complex a(1, 2);
static const Complex b(1, 3);
static const Complex c(2, 3);

using StackLst = StackLstT<Complex>;

template <class T>
void InitTest(const T& a, const T& b, const T& c) {
  StackLst<T> stack1;
  CHECK_THROWS(stack1.Top());
  CHECK(stack1.IsEmpty());
  CHECK_NOTHROW(stack1.Pop());
  for(int i = 0; i < 10; i += 1) {
    CHECK_NOTHROW(stack1.Push(a));
  }
  for (int i = 0; i < 10; i += 1) {
    CHECK_EQ(stack1.Top(), a);
    CHECK_NOTHROW(stack1.Pop());
  }

  StackLst<T> stack2;
  for (int i = 0; i < 10; i += 1) {
    CHECK_NOTHROW(stack2.Push(c));
  }
  for (int i = 0; i < 10; i += 1) {
    CHECK_NOTHROW(stack1.Push(b));
  }

  for (int i = 0; i < 10; i += 1) {
    CHECK_EQ(stack2.Top(), c);
    CHECK_NOTHROW(stack2.Pop());
  }
  for (int i = 0; i < 10; i += 1) {
    CHECK_EQ(stack1.Top(), c);
    CHECK_NOTHROW(stack1.Pop());
  }

  StackLst<T> stack3;
  for (int i = 0; i < 90; i += 1) {
    switch (i % 3) {
      case 0:
        CHECK_NOTHROW(stack3.Push(a));
        break;
      case 1:
        CHECK_NOTHROW(stack3.Push(b));
        break;
      case 2:
        CHECK_NOTHROW(stack3.Push(c));
        break;
    }
  }

  for (int i = 0; i < 90; i += 1) {
    switch (i % 3) {
      case 0:
        CHECK_EQ(stack3.Top(), a);
        break;
      case 1:
        CHECK_EQ(stack3.Top(), b);
        break;
      case 2:
        CHECK_EQ(stack3.Top(), c);
        break;
    }
    CHECK_NOTHROW(stack3.Pop());
}

TEST_CASE("Initialization") {
  InitTest(Complex(1, 2), Complex(1.23, -2.32),Complex(4.4, 5));
}

void CopiedTest(StackLst& stack1, StackLst& stack2) {
  stack1.Clear();

  for (int i = 0; i < 100; i += 1) {
    CHECK_EQ(stack2.Top(), a);
    CHECK_NOTHROW(stack2.Pop());
  }

  CHECK_NOTHROW(stack1.Push(b));
  CHECK_THROW(stack2.Top());
  CHECK_NOTHROW(stack1.Pop());
}

template <typename T>
void CopyTest(const T& a, const T& b, const T& c) {
  StackLst<T> stack1;
  for (int i = 0; i < 100; i += 1) {
    CHECK_NOTHROW(stack1.Push(a));
  }

  StackLst<T> stack2(stack1);

  CopiedTest(stack1, stack2);

  for (int i = 0; i < 100; i += 1) {
    CHECK_NOTHROW(stack1.Push(a));
  }

  StackLast<T> stack3 = stack1;

  CopiedTest(stack1, stack3);
}

TEST_CASE("Copy") {
  CopyTest(Complex(1.023, 2), Complex(2.3, 2.32),Complex(4.45, -5));
}

void TimeTest(const T& a, const T& b) {
  long long diff = 0;

  StackLst<T> stack1;
  for (int i = 0; i < 1000; i++) {
    stack1.Push(a);
  }
  auto start = std::chrono::steady_clock::now();
  StackLst<T> stack2(stack1);
  auto end = std::chrono::steady_clock::now();
  for (int i = 0; i < 1000; i++) {
    CHECK_EQ(stack2.Top(), a);
    CHECK_NOTHROW(stack2.Pop());
  }
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  StackLst<T> stack3(std::move(stack1));
  end = std::chrono::steady_clock::now();
  for (int i = 0; i < 1000; i++) {
    CHECK_EQ(stack3.Top(), a);
    CHECK_NOTHROW(stack3.Pop());
  }
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff -= duration.count();

  CHECK(diff > duration.count() * 10);

  StackLst<T> stack4;
  for (int i = 0; i < 1000; i++) {
    stack4.Push(b);
  }
  StackLst<T> stack5;
  start = std::chrono::steady_clock::now();
  stack5 = stack4;
  end = std::chrono::steady_clock::now();
  for (int i = 0; i < 1000; i++) {
    CHECK_EQ(stack5.Top(), b);
    CHECK_NOTHROW(stack5.Pop());
  }
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  StackLst<T> stack6 = std::move(stack4);
  end = std::chrono::steady_clock::now();
  for (int i = 0; i < 1000; i++) {
    CHECK_EQ(stack6.Top(), b);
    CHECK_NOTHROW(stack6.Pop());
  }
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff -= duration.count();

  CHECK(diff > duration.count() * 10);
}

TEST_CASE("time test") {
  TimeTest(Complex(1.023, 2), Complex(2.3, 2.32));
}