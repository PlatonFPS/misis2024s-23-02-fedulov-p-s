#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<stackarrt/stackarrt.hpp>
#include<rational/rational.hpp>

#include <vector>
#include <algorithm>
#include <string>

template <class T>
void CreateValues(std::vector<T>& values, int32_t size) {
  values.resize(size);
  for (int i = 0; i < values.size(); i += 1) {
    values[i] = T(i);
  }
}

template <>
void CreateValues<std::string>(std::vector<std::string>& values, int32_t size) {
  values.resize(size);
  for (int i = 0; i < values.size(); i += 1) {
    values[i] = 'a' + i;
    if (i % 26 == 0 && i != 0) {
      values[i] += values[i - 1];
    }
  }
}

template <class T>
void FillWithValues(StackArrT<T>& stack, const std::vector<T>& values) {
  for (int i = 0; i < values.size(); i += 1) {
    stack.Push(values[i]);
  }
}

template <class T>
bool CheckValues(StackArrT<T>& stack, const std::vector<T>& values) {
  for (int i = 0; i < values.size(); i += 1) {
    if (stack.Top() != values[values.size() - i - 1]) {
      return false;
    }
    stack.Pop();
  }
  return true;
}

template <class T>
bool CheckStacks(StackArrT<T>& stack1, StackArrT<T>& stack2) {
  while (stack1.IsEmpty() == false) {
    if (stack1.Top() != stack2.Top()) {
      return false;
    }
    stack1.Pop();
    stack2.Pop();
  }
  if (!stack1.IsEmpty() || !stack2.IsEmpty()) {
    return false;
  }
  return true;
}

template <class T>
void InitTest() {
  std::vector<T> values;
  CreateValues<T>(values, 10);
  StackArrT<T> stack1;
  CHECK_THROWS(stack1.Top());
  CHECK(stack1.IsEmpty());
  CHECK_NOTHROW(stack1.Pop());

  FillWithValues<T>(stack1, values);

  CHECK(CheckValues<T>(stack1, values));

  std::vector<T> revValues = values;
  std::reverse(revValues.begin(), revValues.end());

  StackArrT<T> stack2;

  FillWithValues<T>(stack2, revValues);

  FillWithValues<T>(stack1, values);

  CHECK(CheckValues<T>(stack2, revValues));

  CHECK(CheckValues<T>(stack1, values));
}

TEST_CASE("Initialization") {

  InitTest<Rational>();
  InitTest<long double>();
  InitTest<char>();
  InitTest<std::string>();
}

template <class T>
void CopyTest() {
  std::vector<T> values;
  CreateValues<T>(values, 10);
  std::vector<T> revValues = values;
  std::reverse(revValues.begin(), revValues.end());
  StackArrT<T> stack1;

  FillWithValues<T>(stack1, values);
  StackArrT<T> stack2(stack1);
  CHECK(CheckStacks<T>(stack1, stack2));

  FillWithValues<T>(stack1, values);
  StackArrT<T> stack3(stack1);
  stack1.Clear();
  FillWithValues<T>(stack1, revValues);
  CHECK(CheckValues<T>(stack3, values));
  CHECK(CheckValues<T>(stack1, revValues));

  FillWithValues(stack1, values);
  stack2 = stack1;
  CHECK(CheckStacks<T>(stack1, stack2));

  FillWithValues(stack1, values);
  stack3 = stack1;
  stack1.Clear();
  FillWithValues(stack1, revValues);
  CHECK(CheckValues<T>(stack3, values));
  CHECK(CheckValues<T>(stack1, revValues));
}

TEST_CASE("Copy") {
  CopyTest<Rational>();
  CopyTest<long double>();
  CopyTest<char>();
  CopyTest<std::string>();
}

template <class T>
void TimeTest() {
  std::vector<T> values;
  CreateValues<T>(values, 1000000);
  long long diff = 0;

  StackArrT<T> stack1;
  FillWithValues(stack1, values);
  auto start = std::chrono::steady_clock::now();
  StackArrT<T> stack2(stack1);
  auto end = std::chrono::steady_clock::now();
  CHECK(CheckValues(stack2, values));
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  StackArrT<T> stack3(std::move(stack1));
  end = std::chrono::steady_clock::now();
  CHECK(CheckValues(stack3, values));
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff -= duration.count();

  CHECK(diff > duration.count() * 10);

  StackArrT<T> stack4;
  FillWithValues(stack4, values);
  StackArrT<T> stack5;
  start = std::chrono::steady_clock::now();
  stack5 = stack4;
  end = std::chrono::steady_clock::now();
  CHECK(CheckValues(stack5, values));
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  StackArrT<T> stack6 = std::move(stack4);
  end = std::chrono::steady_clock::now();
  CHECK(CheckValues(stack6, values));
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff -= duration.count();

  CHECK(diff > duration.count() * 10);
}

TEST_CASE("time test") {
  TimeTest<Rational>();
  TimeTest<long double>();
  TimeTest<char>();
  TimeTest<std::string>();
}