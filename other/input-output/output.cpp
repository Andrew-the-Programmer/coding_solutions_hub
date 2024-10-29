#include <iostream>
#include <iterator>

template <std::forward_iterator Iter>
void Output(Iter begin, Iter end) {
  for (auto i = begin; i != end; ++i) {
    std::cout << *i << " ";
  }
  std::cout << '\n';
}
