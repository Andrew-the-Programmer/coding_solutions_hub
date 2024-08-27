#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  std::cout << std::fixed << std::setprecision(6);

  float line1[3]{};
  float line2[3]{};

  for (int i = 0; i < 3; ++i) {
    std::cin >> line1[i];
  }
  for (int i = 0; i < 3; ++i) {
    std::cin >> line2[i];
  }

  std::cout << line1[1] << " " << -line1[0] << "\n";
  std::cout << line2[1] << " " << -line2[0] << "\n";

  if (line1[1] * line2[0] == line1[0] * line2[1]) {  // lines are parallel
    if (line1[1] != 0 && line2[1] != 0) {
      auto s = (line1[1] * (line1[2] / line1[1] - line2[2] / line2[1])) /
               static_cast<float>(sqrt(static_cast<double>(line1[1] * line1[1] + line1[0] * line1[0])));
      std::cout << (s > 0 ? s : -s);
    } else if (line1[1] == 0 && line2[1] == 0) {
      std::cout << (line1[2] / line1[0] - line2[2] / line2[0] >= 0 ? line1[2] / line1[0] - line2[2] / line2[0]
                                                                   : -(line1[2] / line1[0] - line2[2] / line2[0]));
    }
  } else {
    std::cout << (line2[2] * line1[1] - line1[2] * line2[1]) / (line1[0] * line2[1] - line1[1] * line2[0]) << " "
              << (line2[0] * line1[2] - line1[0] * line2[2]) / (line1[0] * line2[1] - line1[1] * line2[0]);
  }
}
