#include "timer.hpp"

void Timer::Start() {
  startPoint = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
  endPoint = std::chrono::high_resolution_clock::now();
}

inline std::chrono::nanoseconds Timer::GetDuration() {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint);
}