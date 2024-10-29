// Copyright 2024 Andrew

#include <iostream>
#include <string>

size_t Solution(const std::string& str) {
  auto size = str.size();
  size_t max_k = 1;
  for (size_t len = 1; len <= size / 2; ++len) {
    for (size_t start = 0; start <= size - len; ++start) {
      size_t k = 1;
      size_t finish = start + len;
      while (finish + len <= size && str.compare(start, len, str, finish, len) == 0) {
        ++k;
        finish += len;
      }
      max_k = std::max(k, max_k);
    }
  }
  return max_k;
}

int main() {
  std::string str;
  std::cin >> str;
  std::cout << Solution(str);
}
