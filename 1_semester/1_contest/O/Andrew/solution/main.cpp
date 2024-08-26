#include <iostream>

size_t Solution(size_t w, size_t h, size_t n) {
  size_t min_size = 0;
  size_t max_size = 0;
  size_t middle_size = 0;

  size_t max = std::max(w, h);

  min_size = max;
  max_size = max * n;

  while (min_size < max_size) {
    middle_size = (max_size + min_size) / 2;
    if (n > (middle_size / w) * (middle_size / h)) {
      min_size = middle_size + 1;
    } else {
      max_size = middle_size;
    }
  }

  return min_size;
}

int main() {
  size_t w = 0;  // width
  size_t h = 0;  // height
  size_t n = 0;  // amount

  std::cin >> w >> h >> n;

  std::cout << Solution(w, h, n);
}