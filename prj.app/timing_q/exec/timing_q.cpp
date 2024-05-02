#pragma once

#include<timer/timer.cpp>

#include<queuelstt/queuelstt.hpp>
#include<queuearrt/queuearrt.hpp>

#include<iostream>
#include<chrono>
#include<string>
#include <functional>

long long MeasureTime(int repetitionCount, std::function<void(int)> func) {
  Timer timer;

  timer.Start();
  func(repetitionCount);
  timer.Stop();

  return timer.GetDuration().count();
}

template <class T>
void CtorTest(int repetitionCount) {
  for (int i = 0; i < repetitionCount; i += 1) {
    T type();
  }
}

int main() {
  //std::function<void(const int&)> func(QueueLstT<int>::Push);

  std::cout << MeasureTime(10000000, &CtorTest<QueueLstT<int>>) << '\n';
  std::cout << MeasureTime(10000000, &CtorTest<QueueArrT<int>>) << '\n';

  Timer timer;

  std::cout << "QueueLstT Push function average time test\n";

  int leftRangeBound = 90000;
  int RightRangeBound = 100000;
  int partitionCount = 100;
  int step = (RightRangeBound - leftRangeBound) / partitionCount;

  long double sum = 0;
  long long count = 0;

  for (int n = leftRangeBound; n <= RightRangeBound; n += step) {
    QueueLstT<int> queue;
    timer.Start();
    for (int i = 0; i < n; i++) {
      queue.Push(i);
    }
    timer.Stop();
    sum += timer.GetDuration().count() / n;
    count++;
  }

  long double elementTime = sum / count;
  std::cout << "Average time per element: " << elementTime << '\n';
  std::cout << "Average elemets per second: " << 10e9 / elementTime << '\n';

  std::cout << "QueueArrT Push function average time test\n";

  leftRangeBound = 90000;
  RightRangeBound = 100000;
  partitionCount = 100;
  step = (RightRangeBound - leftRangeBound) / partitionCount;

  sum = 0;
  count = 0;

  for (int n = leftRangeBound; n <= RightRangeBound; n += step) {
    QueueArrT<int> queue;
    timer.Start();
    for (int i = 0; i < n; i++) {
      queue.Push(i);
    }
    timer.Stop();
    sum += timer.GetDuration().count() / static_cast<double>(n);
    count++;
  }

  elementTime = sum / count;
  std::cout << "Average time per element: " << elementTime << '\n';
  std::cout << "Average elemets per second: " << 10e9 / elementTime << '\n';

  return 0;
}