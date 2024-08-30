#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  float vec1[4]{};
  float vec2[4]{};
  for (int i = 0; i < 4; ++i) {
    std::cin >> vec1[i];
  }
  for (int i = 0; i < 4; ++i) {
    std::cin >> vec2[i];
  }
  std::cout << std::fixed << std::setprecision(6)
            << sqrt((static_cast<double>(vec1[0] - vec1[2]) * (vec1[0] - vec1[2]) +
                     (vec1[1] - vec1[3]) * (vec1[1] - vec1[3])))
            << ' ';
  std::cout << std::fixed << std::setprecision(6)
            << sqrt(static_cast<double>((vec2[0] - vec2[2]) * (vec2[0] - vec2[2]) +
                                        (vec2[1] - vec2[3]) * (vec2[1] - vec2[3])))
            << '\n';
  std::cout << std::fixed << std::setprecision(6) << (vec1[2] - vec1[0] + vec2[2] - vec2[0]) << " "
            << std::setprecision(6) << (vec1[3] - vec1[1] + vec2[3] - vec2[1]) << '\n';
  std::cout << std::fixed << std::setprecision(6)
            << (vec1[2] - vec1[0]) * (vec2[2] - vec2[0]) + (vec1[3] - vec1[1]) * (vec2[3] - vec2[1]) << " "
            << std::setprecision(6)
            << (vec1[2] - vec1[0]) * (vec2[3] - vec2[1]) - (vec1[3] - vec1[1]) * (vec2[2] - vec2[0]);
  std::cout << "\n";
  float s = 0.5f * ((vec1[2] - vec1[0]) * (vec2[3] - vec2[1]) - (vec1[3] - vec1[1]) * (vec2[2] - vec2[0]));
  std::cout << std::fixed << std::setprecision(6) << (s >= 0 ? s : -s);
  return 0;
}