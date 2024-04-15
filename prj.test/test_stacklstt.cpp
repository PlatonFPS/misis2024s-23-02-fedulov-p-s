#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<stacklstt/stacklstt.hpp>
#include<complex/complex.hpp>

#include <vector>
#include <algorithm>

template <typename T> 
void CreateValues(std::vector<T>& values, int32_t size) {
  values.resize(size);
  for (int i = 0; i < values.size(); i += 1) {
    values[i] = T(i);
  }
}

template <typename T>
void FillWithValues(StackLstT<T>& stack, const std::vector<T>& values) {
  for (int i = 0; i < values.size(); i += 1) {
    stack.Push(values[i]);
  }
}

template <typename T>
bool CheckValues(StackLstT<T>& stack, const std::vector<T>& values) {
  for (int i = 0; i < values.size(); i += 1) {
    if(stack.Top() != values[values.size() - i - 1]) {
      return false;
    }
    stack.Pop();
  }
  return true;
}

template <typename T>
bool CheckStacks(StackLstT<T>& stack1, StackLstT<T>& stack2) {
  while(stack1.IsEmpty() == false) {
    if (stack1.Top() != stack2.Top()) {
      return false;
    }
    stack1.Pop();
    stack2.Pop();
  }
  if(!stack1.IsEmpty() || !stack2.IsEmpty()) {
    return false;
  }
  return true;
}

template <typename T> 
void InitTest() {
  std::vector<T> values;
  CreateValues<T>(values, 10);
  StackLstT<T> stack1;
  CHECK_THROWS(stack1.Top());
  CHECK(stack1.IsEmpty());
  CHECK_NOTHROW(stack1.Pop());

  FillWithValues<T>(stack1, values);

  CHECK(CheckValues<T>(stack1, values));

  std::vector<T>& revValues = values;
  std::reverse(revValues.begin(), revValues.end());

  StackLstT<T> stack2;
  
  FillWithValues<T>(stack2, revValues);

  FillWithValues<T>(stack1, values);

  CHECK(CheckValues<T>(stack2, revValues));

  CHECK(CheckValues<T>(stack1, revValues));
}

TEST_CASE("Initialization") {

  InitTest<Complex>();
}

template <typename T>
void CopiedTest() {
  
}

template <typename T>
void CopyTest() {
  std::vector<T> values;
  CreateValues<T>(values, 10);
  std::vector<T>& revValues = values;
  std::reverse(revValues.begin(), revValues.end());
  StackLstT<T> stack1;

  FillWithValues<T>(stack1, values);
  StackLstT<T> stack2(stack1);
  CHECK(CheckStacks<T>(stack1, stack2));

  FillWithValues<T>(stack1, values);
  StackLstT<T> stack3(stack1);
  stack1.Clear();
  FillWithValues<T>(stack1, revValues);
  CheckValues<T>(stack3, values);
  CheckValues<T>(stack1, revValues);

  FillWithValues(stack1, values);
  stack2 = stack1;
  CheckStacks<T>(stack1, stack2);

  FillWithValues(stack1, values);
  stack3 = stack1;
  stack1.Clear();
  FillWithValues(stack1, revValues);
  CheckValues<T>(stack3, values);
  CheckValues<T>(stack1, revValues);
}

TEST_CASE("Copy") {
  CopyTest<Complex>();
}

//template <typename T>
//void TimeTest(const T& a, const T& b) {
//  long long diff = 0;
//
//  StackLstT<T> stack1;
//  for (int i = 0; i < 1000; i++) {
//    stack1.Push(a);
//  }
//  auto start = std::chrono::steady_clock::now();
//  StackLstT<T> stack2(stack1);
//  auto end = std::chrono::steady_clock::now();
//  for (int i = 0; i < 1000; i++) {
//    CHECK_EQ(stack2.Top(), a);
//    CHECK_NOTHROW(stack2.Pop());
//  }
//  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
//
//  diff = duration.count();
//
//  start = std::chrono::steady_clock::now();
//  StackLstT<T> stack3(std::move(stack1));
//  end = std::chrono::steady_clock::now();
//  for (int i = 0; i < 1000; i++) {
//    CHECK_EQ(stack3.Top(), a);
//    CHECK_NOTHROW(stack3.Pop());
//  }
//  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
//
//  diff -= duration.count();
//
//  CHECK(diff > duration.count() * 10);
//
//  StackLstT<T> stack4;
//  for (int i = 0; i < 1000; i++) {
//    stack4.Push(b);
//  }
//  StackLstT<T> stack5;
//  start = std::chrono::steady_clock::now();
//  stack5 = stack4;
//  end = std::chrono::steady_clock::now();
//  for (int i = 0; i < 1000; i++) {
//    CHECK_EQ(stack5.Top(), b);
//    CHECK_NOTHROW(stack5.Pop());
//  }
//  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
//
//  diff = duration.count();
//
//  start = std::chrono::steady_clock::now();
//  StackLstT<T> stack6 = std::move(stack4);
//  end = std::chrono::steady_clock::now();
//  for (int i = 0; i < 1000; i++) {
//    CHECK_EQ(stack6.Top(), b);
//    CHECK_NOTHROW(stack6.Pop());
//  }
//  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
//
//  diff -= duration.count();
//
//  CHECK(diff > duration.count() * 10);
//}
//
//TEST_CASE("time test") {
//  TimeTest(Complex(1.023, 2), Complex(2.3, 2.32));
//}