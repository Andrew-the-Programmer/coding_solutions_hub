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

