#pragma once

#include <timer/timer.cpp>

#include <chrono>
#include <functional>

template<class T, class ...Args>
class Decorator {
public:
  Decorator(T (*func)(Args...)) {
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