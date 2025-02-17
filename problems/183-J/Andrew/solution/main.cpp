// Copyright 2024 Andrew

#include <iostream>
#include <vector>
#include <string>

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

void OutputSlice(const std::string& s, size_t start, size_t end) {
  for (size_t i = start; i < end; ++i) {
    std::cout << s[i];
  }
}

int main() {
  std::string s;
  std::string t;
  std::cin >> s >> t;
  bool good_word = false;
  auto sum = s + "#" + t;
  std::vector<size_t> p;
  p.reserve(t.size());
  auto z = ZFunc(sum);

  auto right = s.size() + 1;
  for (auto i = right; i < z.size(); ++i) {
    if (i >= right && z[i] == 0) {
      good_word = true;
      break;
    }
    if (right <= z[i] + i) {
      right = z[i] + i;
      p.emplace_back(i - (s.size() + 1));
    }
  }

  if (good_word) {
    std::cout << "Yes\n";
    return 0;
  }

  std::cout << "No\n";
  size_t left = 0;
  right = 0;
  for (size_t i = 0; i < p.size(); ++i) {
    left = right;
    if (i + 1 < p.size()) {
      right = p[i + 1];
    } else {
      right = t.size();
    }
    OutputSlice(t, left, right);
    std::cout << ' ';
  }
  std::cout << '\n';
  return 0;
}
