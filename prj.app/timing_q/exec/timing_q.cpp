#pragma once

#include <timer/timer.cpp>
#include <queuelstt/queuelstt.hpp>
#include <queuearrt/queuearrt.hpp>

#include <iostream>
#include <string>
#include <map>
#include <array>

const int kDivisionCount = 25;

void PrintResults(const std::map<long long, int>& map,
                  const long long min, const long long max) {
  long long interval = (max - min) / kDivisionCount;
  long long left = min;
  long long right = min + interval;

  long long count = 0;
  long long sum = 0;

  for (auto& it : map) {
    while (it.first > right) {
      std::cout << "[" << left << "; " << right << "]: " << sum << '\n';
      left += interval;
      right += interval;
      sum = 0;
      count = 0;
    }
    sum += it.second;
    count++;
  }
  std::cout << "[" << left << "; " << right << "]: " << sum << '\n';
  sum = 0;
  count = 0;
  left += interval;
  right += interval;
}

int main() {
  const int kMinPow = 0;
  const int kMaxPow = 4;
  const int kKoef = 10;
  const int kRepetitionCount = 1e3;
  Timer timer;
  
  int count = 1;
  for (int i = kMinPow; i <= kMaxPow; i += 1) {

    std::cout << "10^" << i << '\n';
    std::map<long long, int> map;
    long long min = -1;
    long long max = -1;

    for (int j = 0; j < kRepetitionCount; j++) {

      timer.Start();
      
      for (int k = 0; k < count; k++) {
        QueueArrT<int> q;
        q.Push(0);
        q.Pop();
      }
      timer.Stop();

      auto duration = timer.GetDuration();

      QueueArrT<int> q;
      timer.Start();
      for (int k = 0; k < count; k++) {
        q.Push(0);
        q.Pop();
      }
      timer.Stop();

      long long delta = (duration - timer.GetDuration()).count();
      //long long delta = duration.count();
      if (delta <= 0) continue;
      map[delta]++;

      if(min == -1 || min > delta) min = delta;

      if(max == -1 || max < delta) max = delta;
    }

    PrintResults(map, min, max);

    count *= kKoef;
  }
  return 0;
}