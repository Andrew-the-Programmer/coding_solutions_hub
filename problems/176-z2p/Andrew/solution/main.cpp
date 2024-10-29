// Copyright 2024 Andrew

#include <iostream>
#include <vector>
#include <iterator>

template <std::forward_iterator Iter>
void Input(Iter begin, Iter end) {
  for (auto i = begin; i != end; ++i) {
    std::cin >> *i;
  }
}

auto ZFuncToPiFunc(const std::vector<size_t>& z) {
  auto n = z.size();
  std::vector<size_t> p(n, 0);
  for (size_t i = 1; i < n; ++i) {
    for (size_t j = 0; j < z[i] && i + j < n; ++j) {
      p[i + j] = std::max(p[i + j], j + 1);
    }
  }
  return p;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<size_t> z(n);
  Input(z.begin(), z.end());
  auto p = ZFuncToPiFunc(z);
  for (auto&& v : p) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}
