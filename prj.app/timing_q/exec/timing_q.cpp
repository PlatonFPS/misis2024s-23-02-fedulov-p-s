#pragma once

#include<timer/timer.cpp>

#include<queuelstt/queuelstt.hpp>
#include<queuearrt/queuearrt.hpp>

#include<iostream>
#include<chrono>
#include<string>

void MeasureAverageTime(void(*func)(), std::string name, int repeatCount) {
  std::cout << name << " average time test(" << repeatCount << " repetitions)" << '\n';

  Timer timer;

  long double sum = 0;
  long long count = 0;

  timer.Start();
  for (int i = 0; i < repeatCount; i += 1) {
    func();
  }
  timer.Stop();

  std::cout << "Average time: " << timer.GetDuration().count() / repeatCount << '\n';
}

void Test() {
  QueueLstT<int> queue();
}

int main() {
  auto it = &Test;
  MeasureAverageTime(it, "QueueLstT ctor", 100000);

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
    sum += timer.GetDuration().count() / static_cast<double>(n);
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