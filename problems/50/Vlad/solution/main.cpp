#include <iostream>

int main() {
  int points[6]{};
  for (int i = 0; i < 6; ++i) {
    std::cin >> points[i];
  }
  if ((points[0] - points[2]) * (points[5] - points[3]) - (points[1] - points[3]) * (points[4] - points[2]) != 0) {
    std::cout << "NO"
              << "\n"
              << "NO"
              << "\n"
              << "NO";
  } else {
    std::cout << "YES"
              << "\n";
    if ((points[0] - points[2]) * (points[4] - points[2]) + (points[1] - points[3]) * (points[5] - points[3]) >= 0) {
      std::cout << "YES"
                << "\n";
    } else {
      std::cout << "NO"
                << "\n";
    }
    if ((points[0] - points[2]) * (points[4] - points[0]) + (points[1] - points[3]) * (points[5] - points[1]) >= 0) {
      std::cout << "YES"
                << "\n";
    } else {
      std::cout << "NO"
                << "\n";
    }
  }
  return 0;
}