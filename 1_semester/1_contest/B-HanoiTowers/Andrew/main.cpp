// hanoi.cpp

#include <stdexcept>

#include <vector>
#include <iostream>

size_t Leftover(size_t from, size_t to) {
  return 3 - from - to;
}

void HanoiSolution(size_t amount, size_t from, size_t to, std::vector<size_t>* m) {
  if (amount == 1) {
    std::cout << m[from].back() + 1 << " " << from + 1 << " " << to + 1 << std::endl;
    m[to].push_back(m[from].back());
    m[from].pop_back();
    return;
  }

  HanoiSolution(amount - 1, from, Leftover(from, to), m);
  HanoiSolution(1, from, to, m);
  HanoiSolution(amount - 1, Leftover(from, to), to, m);
}

int main() {
  size_t n = 0;

  std::cin >> n;

  std::vector<size_t> m[3]{};

  for (size_t i = 0; i < n; ++i) {
    m[0].push_back(n - 1 - i);
  }

  HanoiSolution(n, 0, 2, m);
}