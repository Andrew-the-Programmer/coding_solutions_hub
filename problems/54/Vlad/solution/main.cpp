#include <iostream>
#include <cmath>

int64_t Signum(int64_t x) {
  if (x == 0) {
    return 0;
  }
  if (x > 0) {
    return 1;
  }
  return -1;
}

int64_t Vecproduct(int64_t x1, int64_t x2, int64_t x3, int64_t x4, int64_t y1, int64_t y2, int64_t y3, int64_t y4) {
  return Signum((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  bool flag = true;
  int64_t n = 0;
  std::cin >> n;
  int64_t x2 = 0;
  int64_t x1 = 0;
  int64_t x3 = 0;
  int64_t y1 = 0;
  int64_t y2 = 0;
  int64_t y3 = 0;
  int64_t xi2 = 0;
  int64_t yi2 = 0;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  int64_t frer = Vecproduct(x1, x2, x2, x3, y1, y2, y2, y3);
  if (frer == 0) {
    flag = false;
  }
  int64_t xi = x2;
  int64_t yi = y2;
  int64_t xi1 = x3;
  int64_t yi1 = y3;
  if (n > 3) {
    for (int64_t i = 0; i < n - 3; ++i) {
      std::cin >> xi2 >> yi2;
      if (Vecproduct(xi, xi1, xi1, xi2, yi, yi1, yi1, yi2) != 0 && flag &&
          (Vecproduct(xi, xi1, xi1, xi2, yi, yi1, yi1, yi2) != frer)) {
        std::cout << "NO";
        return 0;
          }
      if (!flag && Vecproduct(xi, xi1, xi1, xi2, yi, yi1, yi1, yi2) != 0) {
        flag = true;
        frer = Vecproduct(xi, xi1, xi1, xi2, yi, yi1, yi1, yi2);
      }
      xi = xi1;
      yi = yi1;
      xi1 = xi2;
      yi1 = yi2;
    }
  }
  if ((Vecproduct(xi, xi1, xi1, x1, yi, yi1, yi1, y1) != 0 && Vecproduct(xi, xi1, xi1, x1, yi, yi1, yi1, y1) != frer) ||
      (Vecproduct(xi1, x1, x1, x2, yi1, y1, y1, y2) != 0 && Vecproduct(xi1, x1, x1, x2, yi1, y1, y1, y2) != frer)) {
    std::cout << "NO";
    return 0;
      }
  std::cout << "YES";
  return 0;
}