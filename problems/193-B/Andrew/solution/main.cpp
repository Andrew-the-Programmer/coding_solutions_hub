// Copyright 2024 Andrew

#include <iostream>
#include <optional>

void Solution() {
  using T = int;

  size_t n = 0;
  std::cin >> n;

  T value{};
  size_t begin = 0;
  size_t end = 0;
  std::optional<T> max;
  T sum = 0;
  size_t start = 0;

  for (size_t i = 0; i < n; ++i) {
    std::cin >> value;
    sum += value;
    if (!max.has_value() || sum > max) {
      max = sum;
      begin = start;
      end = i;
    }
    if (sum < 0) {
      sum = 0;
      start = i + 1;
    }
  }

  std::cout << begin + 1 << ' ' << end + 1 << ' ' << max.value() << '\n';
}

int main() {
  Solution();
  return 0;
}
