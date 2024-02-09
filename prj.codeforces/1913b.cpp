#include <iostream>
#include <string>

int main() {
  int n_string = 0;
  std::cin >> n_string;
  for (int i_string = 0; i_string < n_string; i_string += 1) {
    std::string string = "";
    std::cin >> string;
    int n_zero = 0, n_one = 0;
    for (char i_char : string) {
      if (i_char == '0') {
        n_zero += 1;
      } else {
        n_one += 1;
      }
    }
    int i_char = 0;
    for (i_char = 0; i_char < string.size(); i_char += 1) {
      if (string[i_char] == '0') {
        if (n_one > 0) {
          n_one -= 1;
        } else {
          break;
        }
      } else {
        if (n_zero > 0) {
          n_zero -= 1;
        } else {
          break;
        }
      }
    }
    std::cout << string.size() - i_char << '\n';
  }
}