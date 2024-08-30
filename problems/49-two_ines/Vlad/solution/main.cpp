#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  float lin1[3]{};
  float lin2[3]{};
  for (int i = 0; i < 3; ++i) {
    std::cin >> lin1[i];
  }
  for (int i = 0; i < 3; ++i) {
    std::cin >> lin2[i];
  }
  std::cout << std::fixed << std::setprecision(6) << lin1[1] << " " << -lin1[0] << "\n";
  std::cout << std::fixed << std::setprecision(6) << lin2[1] << " " << -lin2[0] << "\n";
  if (lin1[1] * lin2[0] == lin1[0] * lin2[1]) {
    if (lin1[1] != 0 && lin2[1] != 0) {
      auto s = (lin1[1] * (lin1[2] / lin1[1] - lin2[2] / lin2[1])) /
               static_cast<float>(sqrt(static_cast<double>(lin1[1] * lin1[1] + lin1[0] * lin1[0])));
      std::cout << std::fixed << std::setprecision(6) << (s > 0 ? s : -s);
    } else if (lin1[1] == 0 && lin2[1] == 0) {
      std::cout << (lin1[2] / lin1[0] - lin2[2] / lin2[0] >= 0 ? lin1[2] / lin1[0] - lin2[2] / lin2[0]
                                                               : -(lin1[2] / lin1[0] - lin2[2] / lin2[0]));
    }
  } else {
    std::cout << std::fixed << std::setprecision(6)
              << (lin2[2] * lin1[1] - lin1[2] * lin2[1]) / (lin1[0] * lin2[1] - lin1[1] * lin2[0]) << " "
              << (lin2[0] * lin1[2] - lin1[0] * lin2[2]) / (lin1[0] * lin2[1] - lin1[1] * lin2[0]);
  }
  return 0;
}