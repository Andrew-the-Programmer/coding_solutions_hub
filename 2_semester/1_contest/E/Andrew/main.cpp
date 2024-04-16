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
struct Vector {
  T x;
  T y;

  using P = Point<T>;

  Vector() = default;

  Vector(const T& x, const T& y) : x(x), y(y) {
  }

  Vector(const P& point) : Vector(point.x, point.y) {  // NOLINT
  }

  Vector(const P& begin, const P& end) : Vector(end.x - begin.x, end.y - begin.y) {
  }

  auto SquaredLength() const {
    return x * x + y * y;
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
    return Vector(x + other.x, y + other.y);
  }

  Vector operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y);
  }

  Vector operator-() const {
    return Vector(-x, -y);
  }
};

template <class>
struct Section;

template <class>
struct Ray;

template <class T>
struct Line {
 public:
  using P = Point<T>;
  using V = Vector<T>;

  Line(const P& first, const P& second) : point(first), directing_vector(V(second) - V(first)) {
  }
  Line(const P& point, const V& directing_vector) : point(point), directing_vector(directing_vector) {
  }
  template <class R>
  Line(const R& a, const R& b, const R& c) : point(-T(c) / T(a), 0), directing_vector(b, -a) {
  }
  explicit Line(const Ray<T>&);
  explicit Line(const Section<T>&);

  const V& GetDirectingVector() const {
    return directing_vector;
  }

  V& GetDirectingVector() {
    return directing_vector;
  }

  const P& GetPoint() const {
    return point;
  }

  P& GetPoint() {
    return point;
  }

  static bool Parallel(const Line& first, const Line& second) {
    return V::SignedArea(first.GetDirectingVector(), second.GetDirectingVector()) == 0;
  }

 public:
  P point = P();
  V directing_vector = V();
};

template <class T>
struct Ray {
  using P = Point<T>;
  using V = Vector<T>;

  Ray(const P& start_point, const V& directing_vector) : start_point(start_point), directing_vector(directing_vector) {
  }
  explicit Ray(const Section<T>&);

  explicit operator Line<T>() {
    return Line<T>(start_point, directing_vector);
  }

  bool PointsTo(const P& point) {
    return V::SignedArea(V(start_point, point), directing_vector) >= 0;
  }

  P start_point = P();
  V directing_vector = V();
};

template <class T>
struct Section {
  using P = Point<T>;
  using V = Vector<T>;
  using L = Line<T>;

  Section() = default;

  Section(const P& first, const P& second) : first_point(first), second_point(second) {
  }

  auto GetDirectingVector() const {
    return V(first_point, second_point);
  }

  auto SquaredLength() const {
    return GetDirectingVector().SquaredLength();
  }

  auto Length() const {
    return GetDirectingVector().Length();
  }

  static bool InterceptOnLine(const Section<T>& first_section, const Section<T>& second_section) {
    auto vec = first_section.GetDirectingVector();
    auto first_squared_length = vec.SquaredLength();
    auto prod1 = V::ScalarProduct(vec, V(first_section.first_point, second_section.first_point));
    auto prod2 = V::ScalarProduct(vec, V(first_section.first_point, second_section.second_point));
    return (prod1 >= 0 && prod1 <= first_squared_length) || (prod2 >= 0 && prod2 <= first_squared_length);
  }

  bool Cross(const L& line) const {
    auto prod1 = V::SignedArea(V(line.point, first_point), line.directing_vector);
    auto prod2 = V::SignedArea(V(line.point, second_point), line.directing_vector);
    return prod1 * prod2 <= 0;
  }

  static bool Cross(const Section<T>& first, const Section<T>& second) {
    auto first_line = L(first);
    auto second_line = L(second);
    if (!(first.Cross(second_line) && second.Cross(first_line))) {
      return false;
    }
    if (L::Parallel(first_line, second_line)) {  // first_line == second_line
      return InterceptOnLine(first, second);
    }
    return true;
  }

  friend std::istream& operator>>(std::istream& stream, Section& section) {
    stream >> section.first_point >> section.second_point;
    return stream;
  }

 public:
  P first_point = P();
  P second_point = P();
};

template <class T>
Line<T>::Line(const Section<T>& section) : Line(section.first_point, section.second_point) {
}
template <class T>
Line<T>::Line(const Ray<T>& ray) : Line(ray.start_point, ray.directing_vector) {
}
template <class T>
Ray<T>::Ray(const Section<T>& section)
    : Ray(section.first_point, Vector<T>(section.first_point, section.second_point)) {
}

template <class... T>
void Output(const T&... args) {
  ((std::cout << args << ' '), ...);
  std::cout << '\n';
}

template <class T>
void Solution(const Section<T>& first, const Section<T>& second) {
  Output(Section<T>::Cross(first, second) ? "YES" : "NO");
}

using T = double;
using P = Point<T>;
using V = Vector<T>;
using S = Section<T>;

int main() {
  S first{P(0, 0), P(0, 1)};
  S second{P(0, 0), P(0, 1)};
  std::cin >> first >> second;
  Solution(first, second);
}
