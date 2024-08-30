#include <iostream>
#include <iomanip>

int64_t Vecproduct(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
  return (x1 * y2 - x2 * y1);
}

int main() {
  int n = 0;
  int64_t xi = 0;
  int64_t yi = 0;
  int64_t xi1 = 0;
  int64_t yi1 = 0;
  std::cin >> n;
  int64_t sqr = 0;
  std::cin >> xi >> yi;
  int64_t x1 = xi;
  int64_t y1 = yi;
  for (int i = 0; i < n - 1; ++i) {
    std::cin >> xi1 >> yi1;
    sqr += Vecproduct(xi, yi, xi1, yi1);
    xi = xi1;
    yi = yi1;
  }
  sqr += Vecproduct(xi, yi, x1, y1);
  sqr = (sqr > 0 ? sqr : -sqr);
  if (sqr % 2 == 0) {
    std::cout << sqr / 2 << ".0";
  } else {
    std::cout << sqr / 2 << ".5";
  }
  return 0;
}