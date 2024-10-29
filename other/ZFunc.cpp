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
