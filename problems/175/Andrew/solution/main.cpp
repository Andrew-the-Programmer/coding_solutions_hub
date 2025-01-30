#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

auto ZFunc(const std::string& str) {
  auto size = str.size();
  std::vector<size_t> z(size, 0);
  size_t left = 0;
  size_t right = 0;
  for (size_t i = 1; i < size; ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i + 1);
    }
    while (i + z[i] < size && str[z[i]] == str[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i] - 1) {
      left = i;
      right = i + z[i] - 1;
    }
  }
  return z;
}

void Solution(const std::string& p, const std::string& t) {
  auto p_size = p.size();
  auto t_size = t.size();

  if (p_size == 0 || p_size > t_size) {
    std::cout << 0 << std::endl;
  }

  auto s = p + '#' + t;
  auto z = ZFunc(s);

  auto pb = s.begin();
  auto pe = pb + static_cast<int64_t>(p_size);
  auto tb = pe + 1;
  auto te = tb + static_cast<int64_t>(t_size);
  std::reverse(pb, pe);
  std::reverse(tb, te);
  auto zr = ZFunc(s);

  std::vector<size_t> sol;
  for (size_t x = 0; x <= t_size - p_size; ++x) {
    auto r = p_size + 1 + x;
    auto rr = t_size - x + 1;
    if (z[r] >= p_size - 1 || z[r] + zr[rr] == p_size - 1) {
      sol.emplace_back(x);
    }
  }
  std::cout << sol.size() << std::endl;
  for (auto&& x : sol) {
    std::cout << x + 1 << " ";
  }
}

int main() {
  std::string p;
  std::string t;
  std::cin >> p >> t;
  Solution(p, t);
}
