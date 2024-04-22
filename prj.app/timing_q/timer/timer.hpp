#pragma once

#include<chrono>

class Timer {
public:
  void Start();
  void Stop();
  inline std::chrono::nanoseconds GetDuration();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> startPoint;
  std::chrono::time_point<std::chrono::high_resolution_clock> endPoint;
};
