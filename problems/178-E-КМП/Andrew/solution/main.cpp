// Copyright 2024 Andrew

#include <iostream>
#include <string>
#include <vector>

auto PiFunc(const std::string& str) {
  size_t size = str.size();
  std::vector<size_t> pref(size, 0);
  for (size_t i = 1; i < size; ++i) {
    size_t count = pref[i - 1];
    while ((count > 0) && (str[i] != str[count])) {
      count = pref[count - 1];
    }
    if (str[i] == str[count]) {
      ++count;
    }
    pref[i] = count;
  }
  return pref;
}

int main() {
  std::string s;
  std::string p;
  std::cin >> s >> p;
  auto p_size = p.size();
  std::string p0s = p + static_cast<char>(0) + s;
  auto pi_func = PiFunc(p0s);
  for (size_t i = p_size + 1; i < pi_func.size(); ++i) {
    if (pi_func[i] == p_size) {
      std::cout << i - 2 * p_size << '\n';
    }
  }
}
