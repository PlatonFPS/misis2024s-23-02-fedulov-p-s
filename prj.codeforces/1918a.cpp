#include <iostream>

int main() {
  int n_wall = 0;
  std::cin >> n_wall;
  for (int i_wall = 0; i_wall < n_wall; i_wall += 1) {
    int height = 0, width = 0;
    std::cin >> height >> width;
    std::cout << (width / 2) * height << '\n';
  }
}