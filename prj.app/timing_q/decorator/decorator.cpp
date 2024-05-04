#include "decorator.hpp"

#include <timer/timer.hpp>

#include <chrono>

template<class T, class ...Args>
Decorator::Decorator(std::function<R(Args...)> func)
: func_(func) {
}

template<class T, class ...Args>
std::chrono::nanoseconds Decorator::MeasureTime(Args... args) {
  Timer timer;

  timer.Start();
  func_(args...);
  timer.Stop();

  return timer.GetDuration();
}