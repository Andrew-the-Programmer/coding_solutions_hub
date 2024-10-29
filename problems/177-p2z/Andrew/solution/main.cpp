// Copyright 2024 Andrew

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

template <std::forward_iterator Iter>
void Input(Iter begin, Iter end) {
  for (auto i = begin; i != end; ++i) {
    std::cin >> *i;
  }
}

template <class StrT>
auto ZFunc(const StrT& s) {
  auto n = s.size();
  std::vector<size_t> z(n, 0);
  size_t l = 0;
  size_t r = 0;
  for (size_t i = 1; i < n; ++i) {
    if (r > i) {
      z[i] = std::min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  z[0] = n;
  return z;
}

auto PiFuncToStr(const std::vector<size_t>& p) {
  auto n = p.size();
  std::vector<size_t> s(n);
  size_t count = 0;
  for (size_t i = 1; i < n; ++i) {
    if (p[i] > 0) {
      s[i] = s[p[i] - 1];
      continue;
    }
    s[i] = ++count;
  }
  return s;
}

auto PiFuncToZFunc(const std::vector<size_t>& p) {
  auto n = p.size();
  std::vector<size_t> z(n, 0);
  auto s = PiFuncToStr(p);
  z = ZFunc(s);
  return z;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<size_t> p(n);
  Input(p.begin(), p.end());
  auto z = PiFuncToZFunc(p);
  for (auto&& v : z) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}
