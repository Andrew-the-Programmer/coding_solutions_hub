// Copyright 2024 Dasha

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

std::vector<uint64_t> ZFunc(const std::string& s) {
  std::vector<uint64_t> z(s.size(), 0);
  uint64_t l = 0;
  uint64_t r = 0;
  for (uint64_t i = 1; i < s.size(); ++i) {
    if (r > i) {
      z[i] = std::min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

int main() {
  std::string p;
  std::string t;
  std::cin >> p >> t;
  uint64_t ans = 0;
  auto a = p + '#' + t;
  auto z = ZFunc(a);
  if (p.length() > t.length()) {
    std::cout << 0 << std::endl;
    return 0;
  }
  for (uint64_t i = 0; i < p.length() / 2; ++i) {
    std::swap(p[i], p[p.length() - i - 1]);
  }
  for (uint64_t i = 0; i < t.length() / 2; ++i) {
    std::swap(t[i], t[t.length() - i - 1]);
  }
  auto b = p + '#' + t;
  auto z_reverse = ZFunc(b);
  std::vector<uint64_t> list;
  for (uint64_t i = 0; i < t.size() - p.size() + 1; ++i) {
    if (z[i + p.length() + 1] >= p.length() - 1) {
      ++ans;
      list.emplace_back(i);
    } else {
      if (z[i + p.length() + 1] + z_reverse[t.length() - i + 1] == p.length() - 1) {
        ++ans;
        list.emplace_back(i);
      }
    }
  }
  std::cout << ans << std::endl;
  for (uint64_t i = 0; i < list.size(); ++i) {
    std::cout << list[i] + 1 << ' ';
  }
  return 0;
}
