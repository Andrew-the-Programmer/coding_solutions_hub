#include <vector>
#include <list>
#include "../iterops.h"
#include <iostream>

void Output(auto value) {
  std::cout << value << std::endl;
}

int main() {
  using T = int;
  std::vector<T> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<T> l = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto vit = v.begin();
  auto lit = l.begin();

  Output(*Next(vit, 9));
  Output(*Next(lit, 11));
  Output(*Prev(Next(vit, 5)));

  auto i = Next(l.begin(), 5);
  Output(*i);
  Output(*Next(i, -2));
  Output(Prev(i) == Next(l.begin(), 4));

  Output(*Prev(lit, 20));
  Output(Distance(v.end(), v.begin()));
  Output(Distance(l.begin(), l.end()));
}
