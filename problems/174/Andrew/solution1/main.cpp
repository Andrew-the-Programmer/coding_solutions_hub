// Copyright 2024 Andrew

#include <iostream>
#include <string>
#include <vector>

auto ZFunc(const std::string& s) {
  std::vector<size_t> z(s.size(), 0);
  size_t l = 0;
  size_t r = 0;
  for (size_t i = 1; i < s.size(); ++i) {
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

size_t Solution(const std::string& str) {
  auto size = str.size();
  size_t k = 1;
  for (size_t i = 0; i < size; ++i) {
    auto z = ZFunc(str.substr(i, size));
    for (size_t j = 1; j < size - i; ++j) {
      k = std::max(k, z[j] / j + 1);
    }
  }
  return k;
}

int main() {
  std::string str;
  std::cin >> str;
  std::cout << Solution(str);
}
