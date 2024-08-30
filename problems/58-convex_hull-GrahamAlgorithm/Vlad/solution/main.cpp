#include <iostream>
#include <vector>
#include <iomanip>

class Point {
 public:
  int64_t x_{};
  int64_t y_{};

  Point(int64_t x, int64_t y) : x_{x}, y_{y} {};

  Point() = default;

  friend bool operator==(Point a, Point b);

  Point operator-(Point p) {
    return {x_ - p.x_, y_ - p.y_};
  }

  int64_t operator^(Point p) {
    return x_ * p.y_ - y_ * p.x_;
  }

  int64_t operator*(Point p) {
    return x_ * p.x_ + y_ * p.y_;
  }

  int64_t Len() {
    return x_ * x_ + y_ * y_;
  }
};

bool operator<(Point a, Point b) {
  if ((a ^ b) != 0) {
    return ((a ^ b) < 0);
  }
  return (a.Len()) > (b.Len());
}

bool operator==(Point a, Point b) {
  return (a.x_ == b.x_ && a.y_ == b.y_);
}

bool operator!=(Point a, Point b) {
  return !(a == b);
}

std::istream &operator>>(std::istream &in, Point &p) {
  in >> p.x_ >> p.y_;
  return in;
}

std::ostream &operator<<(std::ostream &out, Point &p) {
  out << p.x_ << ' ' << p.y_;
  return out;
}

int Square(std::vector<Point> &hull) {
  int64_t sqr = 0;
  auto n = hull.size();
  for (size_t i = 0; i < n - 1; ++i) {
    sqr += hull[i] ^ hull[i + 1];
  }
  sqr += hull[n - 1] ^ hull[0];
  sqr = (sqr > 0 ? sqr : -sqr);
  if (sqr % 2 == 0) {
    std::cout << sqr / 2 << ".0";
  } else {
    std::cout << sqr / 2 << ".5";
  }
  return 0;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int64_t n = 0;
  std::cin >> n;
  auto arr = std::vector<Point>{};
  for (int64_t i = 0; i < n; ++i) {
    Point p{};
    std::cin >> p;
    arr.emplace_back(p);
  }
  Point s = arr[0];
  auto hull = std::vector<Point>{};
  for (int64_t i = 1; i < n; ++i) {
    if (arr[i].x_ < s.x_ || (arr[i].x_ == s.x_ && arr[i].y_ < s.y_)) {
      s = arr[i];
    }
  }
  auto cmp = [&s](const Point &a, const Point &b) -> bool {
    Point pa{a.x_ - s.x_, a.y_ - s.y_};
    Point pb{b.x_ - s.x_, b.y_ - s.y_};
    auto area = pa ^ pb;
    if (area != 0) {
      return area < 0;
    }
    return pb * pb > pa * pa;
  };
  std::sort(arr.begin(), arr.end(), cmp);
  for (auto j : arr) {
    while (true) {
      if (hull.size() <= 1) {
        if (hull.size() == 1 && hull.front() == j) {
          break;
        }
        hull.push_back(j);
        break;
      }
      auto a = hull[hull.size() - 1];
      auto b = hull[hull.size() - 2];
      Point v = Point{b.x_ - a.x_, b.y_ - a.y_};
      Point u = Point{a.x_ - j.x_, a.y_ - j.y_};
      if ((v ^ u) >= 0) {
        hull.pop_back();
        continue;
      }
      hull.push_back(j);
      break;
    }
  }
  std::cout << hull.size() << "\n";
  for (auto &i : hull) {
    std::cout << i << "\n";
  }
  Square(hull);
  return 0;
}
