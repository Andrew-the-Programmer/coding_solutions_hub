#include <iostream>
#include <cmath>

template <class T>
struct Point {
  T x;
  T y;

  Point() = default;

  Point(const T& x, const T& y) : x(x), y(y) {
  }

  friend std::ostream& operator<<(std::ostream& stream, const Point& point) {
    stream << point.x << ' ' << point.y;
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, Point& point) {
    stream >> point.x >> point.y;
    return stream;
  }
};

template <class T>
struct Vector : public Point<T> {
  using P = Point<T>;

  using P::P;

  Vector(const P& point) : P(point.x, point.y) {  // NOLINT
  }

  Vector(const P& begin, const P& end) : P(end.x - begin.x, end.y - begin.y) {
  }

  Vector() : Vector(P()) {
  }

  const T& x() const {
    return this->x;
  }

  const T& y() const {
    return this->y;
  }

  auto SquaredLength() {
    return x() * x() + y() * y();
  }

  double Length() {
    return std::sqrt(SquaredLength());
  }

  static auto ScalarProduct(const Vector& first, const Vector& second) {
    return first.x * second.x + first.y * second.y;
  }

  static auto SignedArea(const Vector& first, const Vector& second) {
    return first.x * second.y - first.y * second.x;
  }

  auto VectorProduct(const Vector& other) const {
    return SignedArea(*this, other);
  }

  Vector operator+(const Vector& other) const {
    return Vector(x() + other.x(), y() + other.y());
  }

  Vector operator-(const Vector& other) const {
    return Vector(x() - other.x(), y() - other.y());
  }

  Vector operator-() const {
    return Vector(-x(), -y());
  }
};

template <class T>
struct Line {
  using P = Point<T>;
  using V = Vector<T>;

  Line(const P& first, const P& second) : start_point(first), directing_vector(V(second) - V(first)) {
  }
  Line(const P& start_point, const V& directing_vector) : start_point(start_point), directing_vector(directing_vector) {
  }
  template <class R>
  Line(const R& a, const R& b, const R& c) : start_point(-T(c) / T(a), 0), directing_vector(b, -a) {
  }

  virtual bool Contain(const P& point) const {
    return V::SignedArea(V(start_point, point), directing_vector) == 0;
  }

  P start_point = P();
  V directing_vector = V();
};

template <class T>
struct Ray : public Line<T> {
  using Base = Line<T>;
  using typename Base::P;
  using typename Base::V;

  using Base::Base;

  bool Contain(const P& point) const override {
    auto start_to_point_vec = V(this->start_point, point);
    bool on_the_line = V::SignedArea(start_to_point_vec, this->directing_vector) == 0;
    bool in_front_of_start = V::ScalarProduct(start_to_point_vec, this->directing_vector) >= 0;
    return on_the_line && in_front_of_start;
  }
};

template <class T>
struct Section {
  using P = Point<T>;
  using V = Vector<T>;

  Section(const P& first, const P& second) : first_point(first), second_point(second) {
  }

  virtual bool Contain(const P& point) const {
    auto first_to_second_vec = V(first_point, second_point);
    auto first_to_point_vec = V(first_point, point);
    auto second_to_point_vec = V(second_point, point);
    bool on_the_line = V::SignedArea(first_to_point_vec, first_to_second_vec) == 0;
    bool in_front_of_first = V::ScalarProduct(first_to_point_vec, first_to_second_vec) >= 0;
    bool in_front_of_second = V::ScalarProduct(second_to_point_vec, -first_to_second_vec) >= 0;
    return on_the_line && in_front_of_first && in_front_of_second;
  }

  P first_point = P();
  P second_point = P();
};

using T = double;
using P = Point<T>;
using V = Vector<T>;

void Solution(P c, P a, P b) {
  auto line = Line<T>(a, b);
  auto ray = Ray<T>(a, b);
  auto section = Section<T>(a, b);

  auto output_result = [](bool flag) { std::cout << (flag ? "YES" : "NO") << '\n'; };

  output_result(line.Contain(c));
  output_result(ray.Contain(c));
  output_result(section.Contain(c));
}

int main() {
  P c;
  P a;
  P b;

  std::cin >> c >> a >> b;

  Solution(c, a, b);
}
