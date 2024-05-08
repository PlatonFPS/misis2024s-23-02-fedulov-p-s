#pragma once

#include <timer/timer.cpp>
#include <queuelstt/queuelstt.hpp>
#include <queuearrt/queuearrt.hpp>

#include <iostream>
#include <string>
#include <map>
#include <array>
#include <vector>

const int kDivisionCount = 20;

const double minPassingVer = 0.05;

void ProcessResults(const std::map<long long, long long>& map) {
  if (map.size() < 2) {
    std::cout << "Insufficient map size" << '\n';
    return;
  }

  //filtering extreme values
  long long maxVer = 0;
  for (auto& it : map) {
    maxVer += it.second;
  }

  long long min = -1;
  long long max = -1;

  double currVer = 0;
  std::map<long long, double> ver;
  auto it = map.begin();
  while (it != map.end()) {
    currVer += (double)it->second / maxVer;
    if (currVer >= minPassingVer && currVer <= 1 - minPassingVer) {
      ver[it->first] = (double)it->second / maxVer;

      if (min == -1) min = it->first;
      if(max == -1 || max < it->first) max = it->first;
    }
    it++;
  }
  
  //grouping values in intervals
  int divisionCount = (ver.size() < kDivisionCount ? ver.size() : kDivisionCount);
  double interval = static_cast<double>(max - min) / divisionCount;
  std::vector<double> intervals(divisionCount);

  double left = min;
  double right = min + interval;
  double sum = 0;
  int division = 0;

  for (auto& it : ver) {
    while (it.first > right) {
      intervals[division] = sum;
      division++;
      left += interval;
      right += interval;
      sum = 0;
    }
    sum += it.second;
  }

  for (int i = 0; i < intervals.size(); i += 1) {
    std::cout << "[" << min + i * interval << "; " << min + (i + 1) * interval << "]: " << intervals[i] * 100 << "%\n";
  }

  /*long long interval = (max - min) / kDivisionCount;
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
  right += interval;*/
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
    std::map<long long, long long> map;

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
    }

    ProcessResults(map);

    count *= kKoef;
  }
  return 0;
}