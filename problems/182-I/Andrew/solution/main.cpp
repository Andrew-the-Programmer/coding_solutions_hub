// Copyright 2024 Andrew

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

auto ManacherOdd(const std::vector<size_t>& array) {
  auto n = array.size();
  std::vector<size_t> p(n, 0);
  size_t l = 0;
  size_t r = 0;
  for (size_t i = 0; i < n; ++i) {
    if (i <= r) {
      p[i] = std::min(r - i, p[2 * l - i]);
    } else {
      p[i] = 0;
    }
    while (i > p[i] && i + p[i] < n && array[i - p[i] - 1] == array[i + p[i]]) {
      ++p[i];
    }
    if (i + p[i] > r) {
      r = i + p[i];
      l = i;
    }
  }
  return p;
}

template <std::forward_iterator Iter>
void Input(Iter begin, Iter end) {
  for (auto i = begin; i != end; ++i) {
    std::cin >> *i;
  }
}

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  std::vector<size_t> cubes(n);
  Input(cubes.begin(), cubes.end());
  auto p = ManacherOdd(cubes);
  for (size_t i = n - 1;; --i) {
    if (p[i] == i) {
      std::cout << n - i << ' ';
    }
    if (i == 0) {
      break;
    }
  }
  std::cout << '\n';
  return 0;
}
