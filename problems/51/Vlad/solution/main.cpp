#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  float points[6]{};
  for (int i = 0; i < 6; i++) {
    std::cin >> points[i];
  }
  float s =
      ((points[0] - points[2]) * (points[5] - points[3]) - (points[1] - points[3]) * (points[4] - points[2])) /
      std::sqrt((points[4] - points[2]) * (points[4] - points[2]) + (points[5] - points[3]) * (points[5] - points[3]));
  s = (s >= 0 ? s : -s);
  std::cout << std::fixed << std::setprecision(6) << s << "\n";
  if ((points[0] - points[2]) * (points[4] - points[2]) + (points[1] - points[3]) * (points[5] - points[3]) >= 0) {
    std::cout << s << "\n";
  } else {
    std::cout << std::fixed << std::setprecision(6)
              << std::sqrt((points[0] - points[2]) * (points[0] - points[2]) +
                           (points[1] - points[3]) * (points[1] - points[3]))
              << "\n";
    std::cout << std::fixed << std::setprecision(6)
              << std::sqrt((points[0] - points[2]) * (points[0] - points[2]) +
                           (points[1] - points[3]) * (points[1] - points[3]));
    return 0;
  }
  if ((points[0] - points[4]) * (points[2] - points[4]) + (points[1] - points[5]) * (points[3] - points[5]) >= 0) {
    std::cout << std::fixed << std::setprecision(6) << s;
  } else {
    std::cout << std::fixed << std::setprecision(6)
              << std::sqrt((points[0] - points[4]) * (points[0] - points[4]) +
                           (points[1] - points[5]) * (points[1] - points[5]));
  }
  return 0;
}