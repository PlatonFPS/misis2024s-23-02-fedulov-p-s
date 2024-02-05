#include<stack/stack.hpp>

#include <iostream>

int main() {
  Stack s;
  std::cout << (s.IsEmpty() ? "stack is empty" : "stack is not empty") << '\n';
  try {
    s.Top();
  }
  catch (const std::out_of_range& error) {
    std::cout << error.what() << '\n';
  }
  s.Pop();
  Complex a(2, 3);
  s.Push(a);
  std::cout << s.Top() << " | expected {2,3}\n";
  
  Complex b(3, 4);
  s.Push(b);
  std::cout << s.Top() << " | expected {3,4}\n";

  Stack s2(s);
  std::cout << s.Top() << " | expected {3,4}\n";
  s.Pop();
  std::cout << s.Top() << " | expected {2,3}\n";
}