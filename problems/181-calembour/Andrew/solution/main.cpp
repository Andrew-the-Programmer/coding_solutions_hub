// Copyright 2024 Andrew

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

auto Suff(const std::string& str, size_t size) {
  size_t pos = std::max(str.size(), size) - size;
  return str.substr(pos, size);
}

auto GetCalembour(const std::string& str1, const std::string& str2) {
  char sep = static_cast<char>(0);
  std::string tmp_str = str2 + sep + Suff(str1, str2.size());
  auto max_prefix_len = PiFunc(tmp_str)[tmp_str.size() - 1];
  return str2.substr(max_prefix_len);
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::string next_str;
  std::cin >> next_str;
  std::string calembour = next_str;
  for (size_t i = 1; i < n; ++i) {
    std::cin >> next_str;
    calembour += GetCalembour(calembour, next_str);
  }
  std::cout << calembour << '\n';
}
