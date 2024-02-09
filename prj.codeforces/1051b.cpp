#include <iostream>

int main() {
  long long l = 0, r = 0;
  std::cin >> l >> r;
  std::cout << "YES\n";
  for (long long i_pair = 0; i_pair < (r - l + 1) / 2; i_pair += 1) {
    std::cout << (l + i_pair * 2) << ' ' << (l + i_pair * 2 + 1) << '\n';
  }
}