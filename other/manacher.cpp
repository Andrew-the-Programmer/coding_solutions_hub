// Copyright 2024 Andrew

#include <cstddef>
#include <vector>

auto ManacherEven(const std::vector<size_t>& array) {
  auto n = array.size();
  std::vector<size_t> p(n, 0);
  size_t l = 0;
  size_t r = 0;
  for (size_t i = 0; i < n; ++i) {
    if (i < r) {
      p[i] = std::min(r - i + 1, p[2 * l - i]);
    } else {
      p[i] = 1;
    }
    while (i >= p[i] && i + p[i] < n && array[i - p[i]] == array[i + p[i]]) {
      ++p[i];
    }
    if (i + p[i] - 1 > r) {
      r = i + p[i] - 1;
      l = i;
    }
  }
  return p;
}

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
