#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <memory>
#include "../point.h"
#include "../ishape.h"
#include "../vector.h"
#include "../segment.h"
#include "../circle.h"
#include "../line.h"
#include "../ray.h"
#include "../polygon.h"

int A(int y1, int y2) {
  return (y2 - y1);
}

int B(int x1, int x2) {
  return (x1 - x2);
}

int C(int x1, int y1, int x2, int y2) {
  return (x2 * y1 - x1 * y2);
}

bool Check(int x1, int y1, int x2, int y2, int a, int b, int c) {
  return (((a * x1 + b * y1 + c) >= 0 && (a * x2 + b * y2 + c) <= 0) ||
          ((a * x1 + b * y1 + c) <= 0 && (a * x2 + b * y2 + c) >= 0));
}

int Vp(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4) {
  return ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));
}

int Per(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4) {
  if ((x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3) || (x1 == x4 && y1 == y4) || (x2 == x4 && y2 == y4)) {
    return 1;
  }
  int a1 = A(y1, y2);
  int a2 = A(y3, y4);
  int b1 = B(x1, x2);
  int b2 = B(x3, x4);
  int c1 = C(x1, y1, x2, y2);
  int c2 = C(x3, y3, x4, y4);
  if (a2 == 0 && b2 == 0 && c2 == 0 && a1 == 0 && b1 == 0 && c1 == 0) {
    if (x1 != x3) {
      return 0;
    }
  }
  if ((Vp(x1, x2, x1, x3, y1, y2, y1, y3) == 0 && Vp(x1, x2, x1, x4, y1, y2, y1, y4) == 0 &&
       Vp(x3, x4, x3, x1, y3, y4, y3, y1) == 0 && Vp(x3, x4, x3, x2, y3, y4, y3, y2) == 0) &&
      ((x1 - x2) != 0 || (y1 - y2) != 0) && ((x3 - x4) != 0 || (y3 - y4) != 0)) {
    int arrx[4]{x1, x2, x3, x4};
    int arry[4]{y1, y2, y3, y4};
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

namespace geometry {
  void Point::Move(const Vector &v) {
    x_ += v.x_;
    y_ += v.y_;
  }

  bool Point::ContainsPoint(const Point &p) const {
    return (x_ == p.x_ && y_ == p.y_);
  }

  bool Point::CrossesSegment(const Segment &s) const {
    return (Vp(x_, s.a_.x_, s.a_.x_, s.b_.x_, y_, s.a_.y_, s.a_.y_, s.b_.y_) == 0 && x_ <= std::max(s.a_.x_, s.b_.x_) &&
            x_ >= std::min(s.a_.x_, s.b_.x_) && y_ <= std::max(s.a_.y_, s.b_.y_) && y_ >= std::min(s.a_.y_, s.b_.y_));
  }

  std::unique_ptr<IShape> Point::Clone() const {
    return std::make_unique<Point>(*this);
  }

  std::string Point::ToString() {
    std::stringstream ss{};
    ss << "Point(" << x_ << ", " << y_ << ")";
    return ss.str();
  }

  void Segment::Move(const Vector &v) {
    a_.x_ += v.
      x_;
    a_.y_ += v.
      y_;
    b_.x_ += v.
      x_;
    b_.y_ += v.
      y_;
  }

  bool Segment::ContainsPoint(const Point &p) const {
    return ((a_.x_ - p.x_) * (b_.y_ - p.y_) - (b_.x_ - p.x_) * (a_.y_ - p.y_) == 0 &&
            (a_.x_ - p.x_) * (b_.x_ - p.x_) + (a_.y_ - p.y_) * (b_.y_ - p.y_) < 0);
  }

  bool Segment::CrossesSegment(const Segment &s) const {
    return (Per(this->a_.x_, this->b_.x_, s.a_.x_, b_.x_, this->a_.y_, this->b_.y_, s.a_.y_, b_.y_) != 0);
  }

  std::unique_ptr<IShape> Segment::Clone() const {
    return std::make_unique<Segment>(*this);
  }

  std::string Segment::ToString() {
    std::stringstream ss{};
    ss << "Ray(" << a_.ToString() << ", " << b_.ToString() << ")" << std::endl;
    return ss.str();
  }

  void Circle::Move(const Vector &v) {
    c_.x_ += v.x_;
    c_.y_ += v.y_;
  }

  bool Circle::ContainsPoint(const Point &p) const {
    return ((p.x_ - c_.x_) * (p.x_ - c_.x_) + (p.y_ - c_.y_) * (p.y_ - c_.y_) <= r_);
  }

  bool Circle::CrossesSegment(const Segment &s) const {
    int d = Vp(s.a_.x_, s.b_.x_, s.a_.x_, c_.x_, s.a_.y_, s.b_.y_, s.a_.y_, c_.y_) /
            static_cast<int>(std::sqrt(
              (s.a_.x_ - s.b_.x_) * (s.a_.x_ - s.b_.x_) + (s.a_.y_ - s.b_.y_) * (s.a_.y_ - s.b_.y_)));
    int da = static_cast<int>(std::sqrt((c_.x_ - s.a_.x_) * (c_.x_ - s.a_.x_) + (c_.y_ - s.a_.y_) * (c_.y_ - s.a_.y_)));
    int db = static_cast<int>(std::sqrt((c_.x_ - s.b_.x_) * (c_.x_ - s.b_.x_) + (c_.y_ - s.b_.y_) * (c_.y_ - s.b_.y_)));
    return (d <= r_ && ((da <= r_ && db <= r_) || (da >= r_ && db <= r_) || (db >= r_ && da <= r_)));
  }

  std::unique_ptr<IShape> Circle::Clone() const {
    return std::make_unique<Circle>(*this);
  }

  std::string Circle::ToString() {
    std::stringstream ss{};
    ss << "Circle(" << "Point(" << c_.x_ << ", " << c_.y_ << "), " << r_ << ")" << std::endl;
    return ss.str();
  }

  void Ray::Move(const Vector &v) {
    a_.x_ += v.x_;
    a_.y_ += v.y_;
  }

  bool Ray::ContainsPoint(const Point &p) const {
    return ((a_.x_ - p.x_) * b_.y_ - b_.x_ * (a_.y_ - p.y_) == 0 &&
            (a_.x_ - p.x_) * b_.x_ + b_.y_ * (a_.y_ - p.y_) < 0);
  }

  bool Ray::CrossesSegment(const Segment &s) const {
    Vector t{};
    t.x_ = b_.x_ * (20000 / std::min(b_.x_, b_.y_));
    t.y_ = b_.y_ * (20000 / std::min(b_.x_, b_.y_));
    return (Per(this->a_.x_, t.x_ + this->a_.x_, s.a_.x_, s.b_.x_, this->a_.y_, t.y_ + this->a_.y_, s.a_.y_, s.b_.y_) !=
            0);
  }

  std::unique_ptr<IShape> Ray::Clone() const {
    return std::make_unique<Ray>(*this);
  }

  std::string Ray::ToString() {
    std::stringstream ss{};
    ss << "Ray(" << a_.ToString() << ", " << "Vector(" << b_.x_ << ", " << b_.y_ << "))" << std::endl;
    return ss.str();
  }

  void Line::Move(const Vector &v) {
    c_ = c_ - a_ * v.x_ - b_ * v.y_;
  }

  bool Line::ContainsPoint(const Point &p) const {
    return (a_ * p.x_ + b_ * p.y_ + c_ == 0);
  }

  bool Line::CrossesSegment(const Segment &s) const {
    return ((a_ * s.a_.x_ + b_ * s.a_.y_ + c_) * (a_ * s.b_.x_ + b_ * s.b_.y_ + c_) <= 0);
  }

  std::unique_ptr<IShape> Line::Clone() const {
    return std::make_unique<Line>(*this);
  }

  std::string Line::ToString() {
    std::stringstream ss{};
    ss << "Line(" << a_ << ", " << b_ << ", " << c_ << ")" << std::endl;
    return ss.str();
  }

  void Polygon::Move(const Vector &v) {
    for (size_t i = 0; i < n_; ++i) {
      arrx_[i] += v.x_;
      arry_[i] += v.y_;
    }
  }

  bool Polygon::ContainsPoint(const Point &p) const {
    int xi1{};
    int yi1{};
    int xi{};
    int yi{};
    size_t c = 0;
    int x0 = 1000000;
    int y0 = 1;
    xi = arrx_[0];
    yi = arry_[0];
    for (size_t i = 1; i < n_; ++i) {
      xi1 = arrx_[i];
      yi1 = arry_[i];
      if (Per(p.x_, x0, xi, xi1, p.y_, y0, yi, yi1) == 2) {
        return true;
      }
      c += Per(p.x_, x0, xi, xi1, p.y_, y0, yi, yi1);
      xi = xi1;
      yi = yi1;
    }
    if (Per(p.x_, x0, xi, arrx_[0], p.y_, y0, yi, arry_[0]) == 2) {
      return true;
    }
    c += Per(p.x_, x0, xi, arrx_[0], p.y_, y0, yi, arry_[0]);
    return (c % 2 == 0);
  }

  bool Polygon::CrossesSegment(const Segment &s) const {
    for (size_t i = 0; i < n_ - 2; ++i) {
      if (Per(s.a_.x_, s.b_.x_, arrx_[i], arrx_[i + 1], s.a_.y_, s.b_.y_, arry_[i], arry_[i + 1])) {
        return true;
      }
    }
    return (Per(s.a_.x_, s.b_.x_, arrx_[n_ - 1], arrx_[0], s.a_.y_, s.b_.y_, arry_[n_ - 1], arry_[0]));
  }

  std::unique_ptr<IShape> Polygon::Clone() const {
    return std::make_unique<Polygon>(*this);
  }

  std::string Polygon::ToString() {
    std::stringstream ss{};
    ss << "Polygon(";
    for (size_t i = 0; i < n_; ++i) {
      if (i == n_) {
        ss << "Point(" << arrx_[i] << ", " << arry_[i] << "))";
      }
      ss << "Point(" << arrx_[i] << ", " << arry_[i] << ")" << ", ";
    }
    return ss.str();
  }

  Vector operator+(Vector a) {
    return a;
  }

  Vector operator-(Vector a) {
    return {-a.x_, -a.y_};
  }

  Vector operator+(Vector a, Vector b) {
    return {a.x_ + b.x_, a.y_ + b.y_};
  }

  Vector operator-(Vector a, Vector b) {
    return {a.x_ - b.x_, a.y_ - b.y_};
  }

  Vector operator*(Vector a, int p) {
    return {a.x_ * p, a.y_ * p};
  }

  Vector operator/(Vector a, int p) {
    return {a.x_ / p, a.y_ / p};
  }

  bool operator==(Vector a, Vector b) {
    return (a.x_ == b.x_ && a.y_ == b.y_);
  }

  Vector &operator+=(Vector &a, Vector b) {
    a.x_ += b.x_;
    a.y_ += b.y_;
    return a;
  }

  Vector &operator-=(Vector &a, Vector b) {
    a.x_ -= b.x_;
    a.y_ -= b.y_;
    return a;
  }

  Vector &operator*=(Vector &a, int p) {
    a.x_ *= p;
    a.y_ *= p;
    return a;
  }

  Vector &operator/=(Vector &a, int p) {
    a.x_ /= p;
    a.y_ /= p;
    return a;
  }

  Point operator-(Point a, Point b) {
    return Point{a.x_ - b.x_, a.y_ - b.y_};
  }
}