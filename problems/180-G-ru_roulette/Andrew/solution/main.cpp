// Copyright 2024 Andrew

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

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

int main() {
  size_t n = 0;
  std::string start;
  std::string finish;
  std::cin >> n >> start >> finish;
  char sep = static_cast<char>(0);

  std::string optimistic = start + sep + finish + '0' + finish;
  std::string pessimistic = start + sep + finish + '1' + finish;

  auto p0 = PiFunc(optimistic);
  auto p1 = PiFunc(pessimistic);

  auto m0 = *std::max_element(p0.begin(), p0.end());
  auto m1 = *std::max_element(p1.begin(), p1.end());

  bool couldve_been_worse = (m0 == n - 1);
  bool couldve_been_better = (m1 == n - 1);

  if (couldve_been_worse == couldve_been_better) {
    std::cout << "Random";
  } else if (couldve_been_worse && !couldve_been_better) {
    std::cout << "No";
  } else if (couldve_been_better && !couldve_been_worse) {
    std::cout << "Yes";
  }
  std::cout << '\n';
}
