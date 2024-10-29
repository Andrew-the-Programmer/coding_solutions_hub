#include <string>
#include <vector>

auto PrefixFunction(const std::string& str) {
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
