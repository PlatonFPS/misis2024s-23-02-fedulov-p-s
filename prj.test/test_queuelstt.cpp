#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<queuelstt/queuelstt.hpp>
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
void FillWithValues(QueueLstT<T>& queue, const std::vector<T>& values) {
  for (int i = 0; i < values.size(); i += 1) {
    queue.Push(values[i]);
  }
}

template <class T>
void InitTest() {
  std::vector<T> values;
  CreateValues<T>(values, 10);
  QueueLstT<T> queue1;
  CHECK_THROWS(queue1.Top());
  CHECK(queue1.IsEmpty());
  CHECK_NOTHROW(queue1.Pop());

  FillWithValues<T>(queue1, values);

  CHECK(queue1.CompareWithVector(values));

  std::vector<T> revValues = values;
  std::reverse(revValues.begin(), revValues.end());

  QueueLstT<T> queue2;

  FillWithValues<T>(queue2, revValues);

  CHECK(queue2.CompareWithVector(revValues));

  CHECK(queue1.CompareWithVector(values));
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

  QueueLstT<T> queue1;
  FillWithValues<T>(queue1, values);
  QueueLstT<T> queue2(queue1);
  CHECK(queue1.Compare(queue2));

  QueueLstT<T> queue3(queue1);
  queue1.Clear();
  FillWithValues<T>(queue1, revValues);
  CHECK(queue3.CompareWithVector(values));
  CHECK(queue1.CompareWithVector(revValues));


  queue1.Clear();
  FillWithValues(queue1, values);
  queue2 = queue1;
  CHECK(queue1.Compare(queue2));

  queue3 = queue1;
  queue1.Clear();
  FillWithValues(queue1, revValues);
  CHECK(queue3.CompareWithVector(values));
  CHECK(queue1.CompareWithVector(revValues));
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
  CreateValues<T>(values, 10000);
  long long diff = 0;

  QueueLstT<T> queue1;
  FillWithValues(queue1, values);
  auto start = std::chrono::steady_clock::now();
  QueueLstT<T> queue2(queue1);
  auto end = std::chrono::steady_clock::now();
  CHECK(queue2.CompareWithVector(values));
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  QueueLstT<T> queue3(std::move(queue1));
  end = std::chrono::steady_clock::now();
  CHECK(queue3.CompareWithVector(values));
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff -= duration.count();

  CHECK(diff > duration.count() * 10);

  QueueLstT<T> queue4;
  FillWithValues(queue4, values);
  QueueLstT<T> queue5;
  start = std::chrono::steady_clock::now();
  queue5 = queue4;
  end = std::chrono::steady_clock::now();
  CHECK(queue5.CompareWithVector(values));
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  QueueLstT<T> queue6 = std::move(queue4);
  end = std::chrono::steady_clock::now();
  CHECK(queue6.CompareWithVector(values));
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