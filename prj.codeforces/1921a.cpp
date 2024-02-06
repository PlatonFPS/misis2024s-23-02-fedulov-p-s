#include <iostream>
#include <vector>
#include <algorithm>

static const int KCoords = 4;

int main() {
  int n_cases = 0;
  std::cin >> n_cases;
  for (int i_case = 0; i_case < n_cases; i_case += 1) {
    std::vector<std::pair<int, int>> coordinates(KCoords);
    for (int i_coords = 0; i_coords < KCoords; i_coords += 1) {
      int x = 0, y = 0;
      std::cin >> x >> y;
      coordinates[i_coords] = { x,y };
    }
    std::sort(coordinates.begin(), coordinates.end());
    int lenght = coordinates[2].first - coordinates[0].first;
    int height = coordinates[1].second - coordinates[0].second;
    std::cout << lenght * height << '\n';
  }
}