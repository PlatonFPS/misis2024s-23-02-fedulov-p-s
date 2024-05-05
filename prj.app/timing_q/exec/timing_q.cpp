#pragma once

//#include<decorator/decorator.hpp>
#include<timer/timer.cpp>

#include<queuelstt/queuelstt.hpp>
#include<queuearrt/queuearrt.hpp>

#include<iostream>
#include<chrono>
#include<string>
#include <functional>

template <class T>
void CtorTest(int repetitionCount) {
  for (int i = 0; i < repetitionCount; i += 1) {
    T type();
  }
}

#include <functional>

template<class T, class ...Args>
class Decorator {
public:
  Decorator(T(*func)(Args...)) {
    func_ = std::function<T(Args...)>(func);
  }

  std::chrono::nanoseconds MeasureTime(Args... args) {
    Timer timer;

    timer.Start();
    func_(args...);
    timer.Stop();

    return timer.GetDuration();
  }

  std::chrono::nanoseconds MeasureTime(int repetitionCount, Args... args) {
    Timer timer;

    timer.Start();
    for (int i = 0; i < repetitionCount; i += 1) {
      func_(args...);
    }
    timer.Stop();

    return timer.GetDuration();
  }

private:
  std::function<T(Args...)> func_;
};

int main() {
  Decorator ctor(&CtorTest<QueueLstT<int>>);
  std::cout << ctor.MeasureTime(10).count() << '\n';
  std::cout << ctor.MeasureTime(100).count() << '\n';
  std::cout << ctor.MeasureTime(10000).count() << '\n';

  /*Timer timer;

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
  std::cout << "Average elemets per second: " << 10e9 / elementTime << '\n';*/

  return 0;
}