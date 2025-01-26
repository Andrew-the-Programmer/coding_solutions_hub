#include <cstddef>
#include <vector>

auto ZFuncToPiFunc(const std::vector<size_t>& z) {
  auto n = z.size();
  std::vector<size_t> p(n, 0);
  for (size_t i = 1; i < n; ++i) {
    for (size_t j = 0; j < z[i] && i + j < n; ++j) {
      p[i + j] = std::max(p[i + j], j + 1);
    }
  }
  return p;
}
