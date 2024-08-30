#include <iostream>
#include <algorithm>

bool Check(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t a, int64_t b, int64_t c) {
  return (((a * x1 + b * y1 + c) >= 0 && (a * x2 + b * y2 + c) <= 0) ||
          ((a * x1 + b * y1 + c) <= 0 && (a * x2 + b * y2 + c) >= 0));
}

int64_t Vp(int64_t x1, int64_t x2, int64_t x3, int64_t x4, int64_t y1, int64_t y2, int64_t y3, int64_t y4) {
  return ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));
}

int64_t A(int64_t y1, int64_t y2) {
  return (y2 - y1);
}

int64_t B(int64_t x1, int64_t x2) {
  return (x1 - x2);
}

int64_t C(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
  return (x2 * y1 - x1 * y2);
}

int Per(int64_t x1, int64_t x2, int64_t x3, int64_t x4, int64_t y1, int64_t y2, int64_t y3, int64_t y4) {
  if ((x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3) || (x1 == x4 && y1 == y4) || (x2 == x4 && y2 == y4)) {
    return 1;
  }
  int64_t a1 = A(y1, y2);
  int64_t a2 = A(y3, y4);
  int64_t b1 = B(x1, x2);
  int64_t b2 = B(x3, x4);
  int64_t c1 = C(x1, y1, x2, y2);
  int64_t c2 = C(x3, y3, x4, y4);
  if (a2 == 0 && b2 == 0 && c2 == 0 && a1 == 0 && b1 == 0 && c1 == 0) {
    if (x1 != x3) {
      return 0;
    }
  }
  if ((Vp(x1, x2, x1, x3, y1, y2, y1, y3) == 0 && Vp(x1, x2, x1, x4, y1, y2, y1, y4) == 0 &&
       Vp(x3, x4, x3, x1, y3, y4, y3, y1) == 0 && Vp(x3, x4, x3, x2, y3, y4, y3, y2) == 0) &&
      ((x1 - x2) != 0 || (y1 - y2) != 0) && ((x3 - x4) != 0 || (y3 - y4) != 0)) {
    int64_t arrx[4]{x1, x2, x3, x4};
    int64_t arry[4]{y1, y2, y3, y4};
    std::sort(arrx, arrx + 4);
    std::sort(arry, arry + 4);
    if (y1 == y2 && y2 == y3 && y3 == y4) {
      if ((arrx[0] == x1 && arrx[1] == x2) || (arrx[0] == x2 && arrx[1] == x1) || (arrx[2] == x1 && arrx[3] == x2) ||
          (arrx[2] == x1 && arrx[3] == x2)) {
        return 0;
      }
      return 1;
    }
    if (x1 == x2 && x2 == x3 && x3 == x4) {
      if ((arry[0] == y1 && arry[1] == y2) || (arry[0] == y2 && arry[1] == y1) || (arry[2] == y1 && arry[3] == y2) ||
          (arry[2] == y1 && arry[3] == y2)) {
        return 0;
      }
      return 1;
    }
    if ((arrx[0] == x1 && arrx[1] == x2) || (arrx[0] == x2 && arrx[1] == x1) || (arrx[2] == x1 && arrx[3] == x2) ||
        (arrx[2] == x1 && arrx[3] == x2)) {
      return 0;
    }
    if ((arry[0] == y1 && arry[1] == y2) || (arry[0] == y2 && arry[1] == y1) || (arry[2] == y1 && arry[3] == y2) ||
        (arry[2] == y1 && arry[3] == y2)) {
      return 0;
    }
    return 1;
  }
  if ((a2 * x1 + b2 * y1 + c2) == 0 &&
      (((x1 <= x4 && x1 >= x3) || (x1 <= x3 && x1 >= x4)) && ((y1 <= y4 && y1 >= y3) || (y1 <= y3 && y1 >= y4)))) {
    return 2;
  }
  if ((a2 * x2 + b2 * y2 + c2) == 0 &&
      (((x2 <= x4 && x2 >= x3) || (x2 <= x3 && x2 >= x4)) && ((y2 <= y4 && y2 >= y3) || (y2 <= y3 && y2 >= y4)))) {
    return 2;
  }
  if ((a1 * x3 + b1 * y3 + c1) == 0 &&
      (((x3 <= x2 && x3 >= x1) || (x3 <= x1 && x3 >= x2)) && ((y3 <= y2 && y3 >= y1) || (y3 <= y1 && y3 >= y2)))) {
    return 2;
  }
  if ((a1 * x4 + b1 * y4 + c1) == 0 &&
      (((x4 <= x2 && x4 >= x1) || (x4 <= x1 && x4 >= x2)) && ((y4 <= y2 && y4 >= y1) || (y4 <= y1 && y4 >= y2)))) {
    return 2;
  }
  if (Check(x1, y1, x2, y2, a2, b2, c2) && Check(x3, y3, x4, y4, a1, b1, c1)) {
    return 1;
  }
  return 0;
}

int main() {
  int64_t n = 0;
  int64_t x1 = 0;
  int64_t y1 = 0;
  int64_t xi1 = 0;
  int64_t yi1 = 0;
  int64_t yp = 0;
  int64_t xp = 0;
  size_t c = 0;
  int64_t x0 = 1000000;
  int64_t y0 = 1;
  std::cin >> n >> xp >> yp >> x1 >> y1;
  int64_t xi = x1;
  int64_t yi = y1;
  for (int64_t i = 0; i < n - 1; ++i) {
    std::cin >> xi1 >> yi1;
    if (Per(xp, x0, xi, xi1, yp, y0, yi, yi1) == 2) {
      std::cout << "YES";
      return 0;
    }
    c += Per(xp, x0, xi, xi1, yp, y0, yi, yi1);
    xi = xi1;
    yi = yi1;
  }
  if (Per(xp, x0, xi, x1, yp, y0, yi, y1) == 2) {
    std::cout << "YES";
    return 0;
  }
  c += Per(xp, x0, xi, x1, yp, y0, yi, y1);
  if (c % 2 == 0) {
    std::cout << "NO";
  } else {
    std::cout << "YES";
  }
  return 0;
}