#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<stackarr/stackarr.hpp>
#include<complex/complex.hpp>

static const Complex a(1, 2);
static const Complex b(1, 3);
static const Complex c(2, 3);

TEST_CASE("Initialization") {
  StackArr stack;
  CHECK_THROWS(stack.Top());
  CHECK(stack.IsEmpty());
  CHECK_NOTHROW(stack.Pop());
  stack.Push(a);
  CHECK_NOTHROW(stack.Top());
}

TEST_CASE("Copy") {
  StackArr stack;
  stack.Push(a);
  stack.Push(b);

  CHECK_EQ(stack.Top(), b);
  stack.Pop();
  CHECK_EQ(stack.Top(), a);
  stack.Push(b);

  StackArr stack2(stack);
  CHECK_EQ(stack2.Top(), stack.Top());
  CHECK_EQ(stack2.Top(), b);
  stack2.Pop();
  CHECK_FALSE(stack2.Top() == stack.Top());
  CHECK_EQ(stack2.Top(), a);
  stack.Pop();
  CHECK_EQ(stack2.Top(), stack.Top());
  
  stack.Push(b);
  stack2 = stack;
  CHECK_EQ(stack2.Top(), stack.Top());
  CHECK_EQ(stack2.Top(), b);
  stack2.Pop();
  CHECK_FALSE(stack2.Top() == stack.Top());
  CHECK_EQ(stack2.Top(), a);
  stack.Pop();
  CHECK_EQ(stack2.Top(), stack.Top());
}

TEST_CASE("time test") {
  long long diff = 0;

  StackArr stack1;
  for (int i = 0; i < 10000; i++) {
    stack1.Push(a);
  }
  auto start = std::chrono::steady_clock::now();
  StackArr stack2(stack1);
  auto end = std::chrono::steady_clock::now();
  CHECK_EQ(stack2.Top(), a);
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  start = std::chrono::steady_clock::now();
  diff = duration.count();

  StackArr stack3(std::move(stack1));
  end = std::chrono::steady_clock::now();
  CHECK_EQ(stack3.Top(), a);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  diff -= duration.count();

  CHECK(diff > duration.count() * 10);

  StackArr stack4;
  for (int i = 0; i < 10000; i++) {
    stack4.Push(a);
  }
  StackArr stack5;
  start = std::chrono::steady_clock::now();
  stack5 = stack4;
  end = std::chrono::steady_clock::now();
  CHECK_EQ(stack5.Top(), a);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  diff = duration.count();

  start = std::chrono::steady_clock::now();
  StackArr stack6 = std::move(stack4);
  end = std::chrono::steady_clock::now();
  CHECK_EQ(stack6.Top(), a);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  diff -= duration.count();

  CHECK(diff > duration.count() * 10);
}