#include <iostream>

int main() {
  size_t max_height = 0;
  size_t n = 0;
  std::cin >> n;
  size_t width = 0;
  size_t height = 0;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> width >> height;
    max_height += std::max(width, height);
  }
  std::cout << max_height;
  return 0;
}