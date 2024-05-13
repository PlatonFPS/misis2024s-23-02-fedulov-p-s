#pragma once

#include <timer/timer.cpp>
#include <queuelstt/queuelstt.hpp>
#include <queuearrt/queuearrt.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <math.h>
#include <filesystem>

std::string prefix = std::filesystem::current_path().
                     parent_path().parent_path().parent_path().parent_path().parent_path()
                     .string() + "/prj.app/timing_q/outdata/";

void WriteToFile(std::string fileName, std::vector<double> data, long long min, double interval) {
  std::ofstream out(prefix + fileName);
  if (out.is_open()) {
    std::cout << "Opened file at " << prefix + fileName << '\n';
    out << "test\n";
    out.close();
  }
  else {
    std::cout << "Could't open file at " << prefix + fileName << '\n';
  }
}

void PrintResults(std::vector<double>& intervals, long long min, double interval) {
  for (int i = 0; i < intervals.size(); ++i) {
    std::cout << "[" << min + i * interval << "; " << min + (i + 1) * interval << "]: " << intervals[i] * 100 << "%\n";
  }

  //calculating dispertion
  long double dispertion = 0;
  for (int i = 0; i < intervals.size(); ++i) {
    dispertion += intervals[i] * intervals[i];
  }
  dispertion /= intervals.size();
  dispertion = sqrt(dispertion);
  std::cout << "Dispertion: " << dispertion * 100 << "%\n";

  //calculating mathematical excpectancy
  double excpectancy = 0;
  for (int i = 0; i < intervals.size(); ++i) {
    excpectancy += intervals[i] * (min + (i + 0.5) * interval);
  }
  std::cout << "Excpectancy: " << excpectancy << '\n';
}


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

  //recalculating probabilities
  double oldSum = 0;
  for (auto& it : ver) {
    oldSum += it.second;
  }
  for (auto& it : ver) {
    it.second /= oldSum;
  }

  double check = 0;
  for (auto& it : ver) {
    check += it.second;
  }
  std::cout << check << '\n';

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

  PrintResults(intervals, min, interval);

  WriteToFile("debug.txt", intervals, min, interval);
}

int main() {
  const int kMinPow = 1;
  const int kMaxPow = 4;
  const int kKoef = 10;
  const int kRepetitionCount = 1e3;
  Timer timer;
  
  int count = 1;
  for (int i = 0; i < kMinPow; ++i) {
    count *= kKoef;
  }
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