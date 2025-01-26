#include <cstddef>
#include <vector>

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
