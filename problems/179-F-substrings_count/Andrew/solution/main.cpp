// Copyright 2024 Andrew

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

auto PiFunc(const std::string& str) {
  size_t size = str.size();
  std::vector<size_t> p(size, 0);
  for (size_t i = 1; i < size; ++i) {
    size_t count = p[i - 1];
    while ((count > 0) && (str[i] != str[count])) {
      count = p[count - 1];
    }
    if (str[i] == str[count]) {
      ++count;
    }
    p[i] = count;
  }
  return p;
}

size_t SubstringCount(const std::string& str) {
  size_t n = str.size();
  size_t count = 1;
  for (size_t i = 1; i < n; ++i) {
    std::string rev_substr(str.rend() - (static_cast<int>(i) + 1), str.rend());
    auto p = PiFunc(rev_substr);
    size_t max_p = *std::max_element(p.begin(), p.end());
    count += i + 1 - max_p;
  }
  return count;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << SubstringCount(s);
}
