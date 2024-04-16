#include <iostream>
#include <cmath>
#include <iomanip>

template <class T>
struct Point {
  T x;
  T y;

  Point() = default;

  Point(const T& x, const T& y) : x(x), y(y) {
  }

  bool operator==(const Point<T>& other) const {
    return x == other.x && y == other.y;
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
class Vector : public Point<T> {
 public:
  using P = Point<T>;

  using P::P;

  Vector(const P& point) : P(point.x, point.y) {  // NOLINT
  }

  Vector(const P& begin, const P& end) : P(end.x - begin.x, end.y - begin.y) {
  }

  Vector() : Vector(P()) {
  }

  const T& X() const {
    return this->x;
  }

  const T& Y() const {
    return this->y;
  }

  auto SquaredLength() const {
    return X() * X() + Y() * Y();
  }

  auto Length() const {
    return std::sqrt(SquaredLength());
  }

  static auto Distance(const P& first, const P& second) {
    return std::abs(Vector(first, second).Length());
  }

  static auto ScalarProduct(const Vector& first, const Vector& second) {
    return first.x * second.x + first.y * second.y;
  }

  static auto SignedArea(const Vector& first, const Vector& second) {
    return first.x * second.y - first.y * second.x;
  }

  static auto Sin(const Vector& first, const Vector& second) {
    return SignedArea(first, second) / (first.Length() * second.Length());
  }

  auto VectorProduct(const Vector& other) const {
    return SignedArea(*this, other);
  }

  Vector operator+(const Vector& other) const {
    return Vector(X() + other.X(), Y() + other.Y());
  }

  Vector operator-(const Vector& other) const {
    return Vector(X() - other.X(), Y() - other.Y());
  }

  Vector operator-() const {
    return Vector(-X(), -Y());
  }
};

using T = double;
using P = Point<T>;
using V = Vector<T>;

template <class... T>
void Output(const T&... args) {
  ((std::cout << args << ' '), ...);
  std::cout << '\n';
}

void Solution(P c, P a, P b) {
  if (a == b || a == c) {
    Output(.0);
    Output(.0);
    Output(V{c, a}.Length());
    return;
  }

  double distance_to_line = 0;
  double distance_to_ray = 0;
  double distance_to_section = 0;

  auto vec_ac = V(a, c);
  auto vec_bc = V(b, c);
  auto vec_ab = V(a, b);
  auto vec_ba = -vec_ab;

  auto sin_angle_bac = std::abs(V::Sin(vec_ab, vec_ac));

  distance_to_line = sin_angle_bac * vec_ac.Length();

  // in the projection on line (a, b) (a <= b)
  bool c_is_less_than_a = V::ScalarProduct(vec_ac, vec_ab) < 0;
  bool c_is_less_than_b = V::ScalarProduct(vec_bc, vec_ba) > 0;

  if (c_is_less_than_a) {
    distance_to_ray = distance_to_section = vec_ac.Length();
  } else {
    distance_to_ray = distance_to_line;
    if (c_is_less_than_b) {
      distance_to_section = distance_to_line;
    } else {
      distance_to_section = vec_bc.Length();
    }
  }

  Output(distance_to_line);
  Output(distance_to_ray);
  Output(distance_to_section);
}

int main() {
  P c;
  P a;
  P b;

  std::cout << std::fixed << std::setprecision(6);

  std::cin >> c >> a >> b;

  Solution(c, a, b);
}