#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<queuelstprt/queuelstprt.hpp>
#include<complex/complex.hpp>

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
    values[i] = 'a' + i % 26;
    if (i % 26 == 0 && i != 0) {
      values[i] += values[i - 1];
    }
  }
}

template <class T>
void FillWithValues(QueueLstPrT<T>& queue, const std::vector<T>& values) {
  for (int i = 0; i < values.size(); i += 1) {
    queue.Push(values[i]);
  }
}

template <class T>
void InitTest() {
  std::vector<T> values;
  CreateValues<T>(values, 10);

  QueueLstPrT<T> queue;
  CHECK_THROWS(queue.Top());
  CHECK(queue.IsEmpty());
  CHECK_NOTHROW(queue.Pop());

  FillWithValues<T>(queue, values);

  std::sort(values.begin(), values.end());

  CHECK(queue.Compare(values));

  std::reverse(values.begin(), values.end());

  CHECK_FALSE(queue.Compare(values));
}

TEST_CASE("ctor") {
  InitTest<int>();
}

