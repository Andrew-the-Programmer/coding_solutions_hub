#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

bool Check(double x1, double y1, double x2, double y2, double a, double b, double c) {
  return (((a * x1 + b * y1 + c) >= 0 && (a * x2 + b * y2 + c) <= 0) ||
          ((a * x1 + b * y1 + c) <= 0 && (a * x2 + b * y2 + c) >= 0));
}

double Vp(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4) {
  return ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));
}

double A(double y1, double y2) {
  return (y2 - y1);
}

double B(double x1, double x2) {
  return (x1 - x2);
}

double C(double x1, double y1, double x2, double y2) {
  return (x2 * y1 - x1 * y2);
}

bool Per(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4) {
  if ((x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3) || (x1 == x4 && y1 == y4) || (x2 == x4 && y2 == y4)) {
    return true;
  }
  double a1 = A(y1, y2);
  double a2 = A(y3, y4);
  double b1 = B(x1, x2);
  double b2 = B(x3, x4);
  double c1 = C(x1, y1, x2, y2);
  double c2 = C(x3, y3, x4, y4);
  if (a2 == 0 && b2 == 0 && c2 == 0 && a1 == 0 && b1 == 0 && c1 == 0) {
    if (x1 != x3) {
      return false;
    }
  }
  if ((Vp(x1, x2, x1, x3, y1, y2, y1, y3) == 0 && Vp(x1, x2, x1, x4, y1, y2, y1, y4) == 0 &&
       Vp(x3, x4, x3, x1, y3, y4, y3, y1) == 0 && Vp(x3, x4, x3, x2, y3, y4, y3, y2) == 0) &&
      ((x1 - x2) != 0 || (y1 - y2) != 0) && ((x3 - x4) != 0 || (y3 - y4) != 0)) {
    double arrx[4]{x1, x2, x3, x4};
    double arry[4]{y1, y2, y3, y4};
    std::sort(arrx, arrx + 4);
    std::sort(arry, arry + 4);
    if (y1 == y2 && y2 == y3 && y3 == y4) {
      if ((arrx[0] == x1 && arrx[1] == x2) || (arrx[0] == x2 && arrx[1] == x1) || (arrx[0] == x3 && arrx[1] == x4) ||
          (arrx[0] == x4 && arrx[1] == x3)) {
        return 1 < 0;
      }
      return true;
    }
    if (x1 == x2 && x2 == x3 && x3 == x4) {
      if ((arry[0] == y1 && arry[1] == y2) || (arry[0] == y2 && arry[1] == y1) || (arry[0] == y4 && arry[1] == y3) ||
          (arry[0] == y3 && arry[1] == y4)) {
        return 1 < 0;
      }
      return true;
    }
    if ((arrx[0] == x1 && arrx[1] == x2) || (arrx[0] == x2 && arrx[1] == x1) || (arrx[2] == x1 && arrx[3] == x2) ||
        (arrx[2] == x1 && arrx[3] == x2)) {
      return false;
    }
    if ((arry[0] == y1 && arry[1] == y2) || (arry[0] == y2 && arry[1] == y1) || (arry[2] == y1 && arry[3] == y2) ||
        (arry[2] == y1 && arry[3] == y2)) {
      return false;
    }
    return true;
  }
  if ((a2 * x1 + b2 * y1 + c2) == 0 &&
      (((x1 <= x4 && x1 >= x3) || (x1 <= x3 && x1 >= x4)) && ((y1 <= y4 && y1 >= y3) || (y1 <= y3 && y1 >= y4)))) {
    return true;
  }
  if ((a2 * x2 + b2 * y2 + c2) == 0 &&
      (((x2 <= x4 && x2 >= x3) || (x2 <= x3 && x2 >= x4)) && ((y2 <= y4 && y2 >= y3) || (y2 <= y3 && y2 >= y4)))) {
    return true;
  }
  if ((a1 * x3 + b1 * y3 + c1) == 0 &&
      (((x3 <= x2 && x3 >= x1) || (x3 <= x1 && x3 >= x2)) && ((y3 <= y2 && y3 >= y1) || (y3 <= y1 && y3 >= y2)))) {
    return true;
  }
  if ((a1 * x4 + b1 * y4 + c1) == 0 &&
      (((x4 <= x2 && x4 >= x1) || (x4 <= x1 && x4 >= x2)) && ((y4 <= y2 && y4 >= y1) || (y4 <= y1 && y4 >= y2)))) {
    return true;
  }
  if (Check(x1, y1, x2, y2, a2, b2, c2) && Check(x3, y3, x4, y4, a1, b1, c1)) {
    return true;
  }
  return false;
}

double Minimum(double r1, double r2, double r3, double r4, double r5, double r6, double r7, double r8) {
  double arr[8]{r1, r2, r3, r4, r5, r6, r7, r8};
  double min = *(std::min_element(arr, arr + 8));
  return min;
}

double Distp(double x1, double y1, double x2, double y2) {
  return (std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

double Distr(double x1, double y1, double x3, double y3, double x4, double y4, double a, double b, double c) {
  double x = (c * (-a) - (a * y1 - b * x1) * b) / (a * a + b * b);
  double y = (a * (a * y1 - b * x1) - b * c) / (a * a + b * b);
  if (x == x1 && y == y1) {
    return 1000000;
  }
  if ((x >= std::min(x3, x4) && x <= std::max(x3, x4)) && (y >= std::min(y3, y4) && y <= std::max(y3, y4))) {
    return static_cast<double>(std::sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
  }
  return 1000000;
}

int main() {
  double x1 = 0;
  double x2 = 0;
  double x3 = 0;
  double x4 = 0;
  double y1 = 0;
  double y2 = 0;
  double y3 = 0;
  double y4 = 0;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
  double a1 = A(y1, y2);
  double a2 = A(y3, y4);
  double b1 = B(x1, x2);
  double b2 = B(x3, x4);
  double c1 = C(x1, y1, x2, y2);
  double c2 = C(x3, y3, x4, y4);
  if (Per(x1, x2, x3, x4, y1, y2, y3, y4)) {
    std::cout << 0;
    return 0;
  }
  std::cout << std::fixed << std::setprecision(14)
            << Minimum(Distr(x1, y1, x3, y3, x4, y4, a2, b2, c2), Distr(x2, y2, x3, y3, x4, y4, a2, b2, c2),
                       Distr(x3, y3, x1, y1, x2, y2, a1, b1, c1), Distr(x4, y4, x1, y1, x2, y2, a1, b1, c1),
                       Distp(x1, y1, x3, y3), Distp(x2, y2, x3, y3), Distp(x4, y4, x2, y2), Distp(x1, y1, x4, y4));
  return 0;
}