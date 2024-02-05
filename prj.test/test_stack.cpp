#include<stack/stack.hpp>

#include <iostream>

int main() {
  Stack s;
  std::cout << s.IsEmpty() << '\n';
  try {
    s.Top();
  }
  catch (const std::out_of_range& error) {
    std::cout << error.what();
  }
}