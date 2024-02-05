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
  std::cout << s2.Top() << " | expected {3,4}\n";
  s2.Pop();
  std::cout << s2.Top() << " | expected {2,3}\n";
  std::cout << s.Top() << " | expected {3,4}\n";

  Stack s3;
  s3 = s;
  std::cout << s3.Top() << " | expected {3,4}\n";
  s3.Pop();
  std::cout << s3.Top() << " | expected {2,3}\n";
  std::cout << s.Top() << " | expected {3,4}\n";
}