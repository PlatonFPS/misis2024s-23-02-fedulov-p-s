#include <functional>

template<class T, class ...Args>
class Decorator<T(Args...)> {
public:
  Decorator(std::function<R(Args...)> func);

  std::chrono::nanoseconds MeasureTime(Args... args);

private:
  std::function<R(Args...)> func_;
};