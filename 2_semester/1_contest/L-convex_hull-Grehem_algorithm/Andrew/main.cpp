

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include <boost/format.hpp>

template <class T>
T Squared(const T& value) {
  return value * value;
}

template <class... T>
void Output(const T&... args) {
  ((std::cout << args << ' '), ...);
  std::cout << '\n';
}

template <class... T>
void Input(T&... args) {
  ((std::cin >> args), ...);
}

template <class T>
T InputResult() {
  T value;
  std::cin >> value;
  return value;
}

namespace geometry {

using T = double;

class Point;

class Vector;

class Segment;

struct IShape {
  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual std::shared_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;

  friend std::ostream& operator<<(std::ostream& stream, const IShape& shape) {
    stream << shape.ToString();
    return stream;
  }
};

struct Point : public IShape {
  T x;
  T y;

  Point() = default;

  Point(const T& x, const T& y) : x(x), y(y) {
  }

  Point& Move(const Vector&) override;

  bool ContainsPoint(const Point& p) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  Vector operator-(const Point& other) const;

  bool operator==(const Point& other) const;

  bool operator!=(const Point& other) const;

  friend std::istream& operator>>(std::istream&, Point&);
};

double Distance(const Point&, const Point&);

struct Vector {
  T x = 0;
  T y = 0;

  using P = Point;

  Vector() = default;

  Vector(const T& x, const T& y);

  Vector(const P&);

  Vector(const P& begin, const P& end);

  operator Point() const;

  T SquaredLength() const;

  double Length() const;

  static T ScalarProduct(const Vector&, const Vector&);

  static T SignedArea(const Vector&, const Vector&);

  static bool Parallel(const Vector&, const Vector&);

  bool PointsTo(const P&) const;

  static double Sin(const Vector&, const Vector&);

  T VectorProduct(const Vector&) const;

  Vector& operator+=(const Vector&);

  Vector operator+(const Vector&) const;

  Vector& operator-=(const Vector&);

  Vector operator-(const Vector&) const;

  Vector operator-() const;

  bool operator==(const Vector&) const;

  std::string ToString() const;

  friend std::ostream& operator<<(std::ostream&, const Vector&);

  friend std::istream& operator>>(std::istream&, Vector&);
};

struct Line : public IShape {
  using P = Point;
  using V = Vector;

  P point = P();
  V directing_vector = V();

 protected:
  /*
    Suppose line is determined by equation ax + by + c = 0.
    Finds any point of this line.
  */
  template <class R>
  static P FindAnyPoint(const R& a, const R& b, const R& c);

 public:
  Line() = default;

  Line(const P&, const P&);

  Line(const P& point, const V& directing_vector);

  template <class R>
  Line(const R& a, const R& b, const R& c);

  Line(const Line&) = default;

  explicit Line(const Ray&);

  explicit Line(const Segment&);

  IShape& Move(const Vector& v) override;

  bool ContainsPoint(const Point& p) const override;

  bool CrossesSegment(const Segment& s) const override;

  std::shared_ptr<IShape> Clone() const override;

  const V& GetDirectingVector() const;

  V& GetDirectingVector();

  const P& GetPoint() const;

  P& GetPoint();

  // return (a,b,c): ax + by + c = 0
  auto GetPolynomialReprArgs() const;

  std::string PolynomialRepr() const;

  std::string PointAndVectorRepr() const;

  std::string ToString() const override;

  static bool Parallel(const Line& first, const Line& second);

  template <class R = T>
  void InputAsPolynom(std::istream& stream);

  void InputAsPointAndVector(std::istream& stream);

  friend std::istream& operator>>(std::istream& stream, Line& line);
};

struct Ray : public IShape {
  using P = Point;
  using V = Vector;

  P start_point = P();
  V directing_vector = V();

  Ray() = default;

  Ray(const P& start_point, const V& directing_vector);

  Ray(const P& start_point, const P& end_point);

  explicit Ray(const Segment&);

  explicit operator Line();

  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  bool PointsTo(const P&) const;

  friend std::istream& operator>>(std::istream&, Ray&);
};

struct Segment : public IShape {
  using P = Point;
  using V = Vector;
  using L = Line;

  P first_point = P();
  P second_point = P();

  Segment() = default;

  Segment(const P&, const P&);

  auto GetDirectingVector() const;

  auto SquaredLength() const;

  auto Length() const;

 protected:
  bool ContainsPointOnSameLine(const P&) const;

  static bool OverlapOnSameLine(const Segment&, const Segment&);

 public:
  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Segment&);
};

double Distance(const Point&, const Segment&);

using R = T;

struct Circle : public IShape {
 public:
  using P = Point;
  using V = Vector;

  R radius = 0;
  P center = P();

  Circle() = default;

  Circle(const R&, const P&);

  Circle(const P&, const R&);

  Circle(const Circle&) = default;

  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Circle&);
};

struct Polygon : public IShape {
 public:
  using P = Point;
  using V = Vector;

  std::vector<P> points;

  Polygon() = default;

  Polygon(const std::initializer_list<P>&);

  Polygon(const std::vector<P>&);

  auto Segments() const;

  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Polygon&);
};

Point& Point::Move(const Vector& v) {
  x += v.x;
  y += v.y;
  return *this;
}

bool Point::ContainsPoint(const Point& p) const {
  return (*this) == p;
}

bool Point::CrossesSegment([[maybe_unused]] const Segment& s) const {
  // return s.ContainsPoint(*this);
  return false;
}

std::shared_ptr<IShape> Point::Clone() const {
  return std::make_shared<Point>(x, y);
}

std::string Point::ToString() const {
  return (boost::format("Point(%1%, %2%)") % x % y).str();
}

Vector Point::operator-(const Point& other) const {
  return Vector(*this, other);
}

bool Point::operator==(const Point& p) const {
  return x == p.x && y == p.y;
}

bool Point::operator!=(const Point& p) const {
  return !(*this == p);
}

std::istream& operator>>(std::istream& stream, Point& point) {
  stream >> point.x >> point.y;
  return stream;
}

double Distance(const Point& first, const Point& second) {
  return std::abs(Vector(first, second).Length());
}

Vector::Vector(const T& x, const T& y) : x(x), y(y) {
}

Vector::Vector(const Point& point) : Vector(point.x, point.y) {  // NOLINT
}

Vector::Vector(const Point& begin, const Point& end) : Vector(end.x - begin.x, end.y - begin.y) {
}

Vector::operator Point() const {
  return Point(x, y);
}

T Vector::SquaredLength() const {
  return x * x + y * y;
}

double Vector::Length() const {
  return std::sqrt(SquaredLength());
}

T Vector::ScalarProduct(const Vector& first, const Vector& second) {
  return first.x * second.x + first.y * second.y;
}

T Vector::SignedArea(const Vector& first, const Vector& second) {
  return first.x * second.y - first.y * second.x;
}

bool Vector::Parallel(const Vector& first, const Vector& second) {
  return SignedArea(first, second) == 0;
}

bool Vector::PointsTo(const Point& point) const {
  return ScalarProduct(Vector(point), *this) >= 0;
}

double Vector::Sin(const Vector& first, const Vector& second) {
  return SignedArea(first, second) / (first.Length() * second.Length());
}

T Vector::VectorProduct(const Vector& other) const {
  return SignedArea(*this, other);
}

Vector& Vector::operator+=(const Vector& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vector Vector::operator+(const Vector& other) const {
  auto result = *this;
  result += other;
  return result;
}

Vector& Vector::operator-=(const Vector& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector Vector::operator-(const Vector& other) const {
  auto result = *this;
  result -= other;
  return result;
}

Vector Vector::operator-() const {
  return Vector(-x, -y);
}

bool Vector::operator==(const Vector& other) const {
  return x == other.x && y == other.y;
}

std::string Vector::ToString() const {
  return (boost::format("Vector(%1%, %2%)") % x % y).str();
}

std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
  stream << vector.ToString();
  return stream;
}

std::istream& operator>>(std::istream& stream, Vector& vector) {
  stream >> vector.x >> vector.y;
  return stream;
}

template <class R>
Line::P Line::FindAnyPoint(const R& a, const R& b, const R& c) {
  if (a == 0) {
    if (b == 0) {
      throw std::invalid_argument("a and b cannot be zero");
    }
    return P(0, -T(c) / T(b));
  }
  return P(-T(c) / T(a), 0);
}

Line::Line(const P& first, const P& second) : point(first), directing_vector(V(second) - V(first)) {
}

Line::Line(const P& point, const V& directing_vector) : point(point), directing_vector(directing_vector) {
}

template <class R>
Line::Line(const R& a, const R& b, const R& c) : point(FindAnyPoint(a, b, c)), directing_vector(b, -a) {
}

Line::Line(const Ray& ray) : Line(ray.start_point, ray.directing_vector) {
}
Line::Line(const Segment& segment) : Line(segment.first_point, segment.second_point) {
}

IShape& Line::Move(const Vector& v) {
  point.Move(v);
  return *this;
}

bool Line::ContainsPoint(const Point& p) const {
  return V::Parallel(V(point, p), directing_vector);
}

bool Line::CrossesSegment(const Segment& s) const {
  auto prod1 = V::SignedArea(V(point, s.first_point), directing_vector);
  auto prod2 = V::SignedArea(V(point, s.second_point), directing_vector);
  return prod1 * prod2 <= 0;
}

std::shared_ptr<IShape> Line::Clone() const {
  return std::make_shared<Line>(point, directing_vector);
}

const Line::V& Line::GetDirectingVector() const {
  return directing_vector;
}

Line::V& Line::GetDirectingVector() {
  return directing_vector;
}

const Line::P& Line::GetPoint() const {
  return point;
}

Line::P& Line::GetPoint() {
  return point;
}

// return (a,b,c): ax + by + c = 0
auto Line::GetPolynomialReprArgs() const {
  auto a = directing_vector.y;
  auto b = -directing_vector.x;
  auto c = Vector::ScalarProduct(directing_vector, point);
  return std::make_tuple(a, b, c);
}

std::string Line::PolynomialRepr() const {
  auto args = GetPolynomialReprArgs();
  return (boost::format("Line(%1%, %2%, %3%)") % std::get<0>(args) % std::get<1>(args) % std::get<2>(args)).str();
}

std::string Line::PointAndVectorRepr() const {
  return (boost::format("Line(%1%, %2%)") % GetPoint() % GetDirectingVector()).str();
}

std::string Line::ToString() const {
  return PolynomialRepr();
}

bool Line::Parallel(const Line& first, const Line& second) {
  return V::Parallel(first.GetDirectingVector(), second.GetDirectingVector());
}

template <class R = T>
void Line::InputAsPolynom(std::istream& stream) {
  R a, b, c;
  stream >> a >> b >> c;
  *this = Line(a, b, c);
}

void Line::InputAsPointAndVector(std::istream& stream) {
  stream >> point >> directing_vector;
}

std::istream& operator>>(std::istream& stream, Line& line) {
  line.InputAsPolynom(stream);
  return stream;
}

Ray::Ray(const P& start_point, const V& directing_vector)
    : start_point(start_point), directing_vector(directing_vector) {
}

Ray::Ray(const P& start_point, const P& end_point)
    : start_point(start_point), directing_vector(V(start_point, end_point)) {
}

Ray::Ray(const Segment& segment) : Ray(segment.first_point, V(segment.first_point, segment.second_point)) {
}

Ray::operator Line() {
  return Line(start_point, directing_vector);
}

IShape& Ray::Move(const Vector& v) {
  start_point.Move(v);
  return *this;
}

bool Ray::ContainsPoint(const Point& p) const {
  bool on_the_line = static_cast<Line>(*this).ContainsPoint(p);
  return on_the_line && PointsTo(p);
}

bool Ray::CrossesSegment(const Segment& s) const {
  bool f1 = V::SignedArea(V(start_point, s.first_point), directing_vector) < 0;
  bool f2 = V::SignedArea(directing_vector, V(start_point, s.second_point)) < 0;
  return f1 ^ f2;
}

std::shared_ptr<IShape> Ray::Clone() const {
  return std::make_shared<Ray>(start_point, directing_vector);
}

std::string Ray::ToString() const {
  return (boost::format("Ray(%1%, %2%)") % start_point % directing_vector).str();
}

bool Ray::PointsTo(const P& point) const {
  return directing_vector.PointsTo(V(start_point, point));
}

std::istream& operator>>(std::istream& stream, Ray& ray) {
  stream >> ray.start_point >> ray.directing_vector;
  return stream;
}

Segment::Segment(const P& first, const P& second) : first_point(first), second_point(second) {
}

auto Segment::GetDirectingVector() const {
  return V(first_point, second_point);
}

auto Segment::SquaredLength() const {
  return GetDirectingVector().SquaredLength();
}

auto Segment::Length() const {
  return GetDirectingVector().Length();
}

// Assume point is on the line (first_point, second_point).
// Return true if segment contains point.
bool Segment::ContainsPointOnSameLine(const P& point) const {
  auto vec = V(first_point, point);
  auto prod = V::ScalarProduct(vec, V(first_point, second_point));
  return 0 <= prod && prod <= SquaredLength();
}

// Assume first_segment and second_segment are on the same line.
// Return true if first_segment and second_segment overlap.
bool Segment::OverlapOnSameLine(const Segment& first_segment, const Segment& second_segment) {
  return first_segment.ContainsPointOnSameLine(second_segment.first_point) ||
         first_segment.ContainsPointOnSameLine(second_segment.second_point);
}

IShape& Segment::Move(const Vector& v) {
  first_point.Move(v);
  second_point.Move(v);
  return *this;
}

bool Segment::ContainsPoint(const Point& p) const {
  bool on_the_line = static_cast<Line>(*this).ContainsPoint(p);
  return on_the_line && ContainsPointOnSameLine(p);
}

bool Segment::CrossesSegment(const Segment& s) const {
  auto first_line = L(*this);
  auto second_line = L(s);
  if (!(first_line.CrossesSegment(s) && second_line.CrossesSegment(*this))) {
    return false;
  }
  if (L::Parallel(first_line, second_line)) {  // first_line == second_line
    return OverlapOnSameLine(*this, s);
  }
  return true;
}

std::shared_ptr<IShape> Segment::Clone() const {
  return std::make_shared<Segment>(first_point, second_point);
}

std::string Segment::ToString() const {
  return (boost::format("Segment(%1%, %2%)") % first_point % second_point).str();
}

std::istream& operator>>(std::istream& stream, Segment& section) {
  stream >> section.first_point >> section.second_point;
  return stream;
}

double Distance(const Point& point, const Segment& segment) {
  auto section_vector = segment.GetDirectingVector();
  auto ray1 = Ray(segment.second_point, section_vector);
  if (ray1.PointsTo(point)) {
    return Vector(segment.second_point, point).Length();
  }
  auto ray2 = Ray(segment.first_point, -section_vector);
  if (ray2.PointsTo(point)) {
    return Vector(segment.first_point, point).Length();
  }
  auto vec_first_point = Vector(segment.first_point, point);
  auto sin_angle = std::abs(Vector::Sin(section_vector, vec_first_point));
  return sin_angle * vec_first_point.Length();
}

Circle::Circle(const R& radius, const P& center) : radius(radius), center(center) {
}

Circle::Circle(const P& center, const R& radius) : Circle(radius, center) {
}

IShape& Circle::Move(const Vector& v) {
  center.Move(v);
  return *this;
}

bool Circle::ContainsPoint(const Point& p) const {
  return V{center, p}.SquaredLength() <= Squared(radius);
}

bool Circle::CrossesSegment(const Segment& s) const {
  return Distance(center, s) <= radius;
}

std::shared_ptr<IShape> Circle::Clone() const {
  return std::make_shared<Circle>(radius, center);
}

std::string Circle::ToString() const {
  return (boost::format("Circle(%1%, %2%)") % center % radius).str();
}

std::istream& operator>>(std::istream& stream, Circle& circle) {
  stream >> circle.center >> circle.radius;
  return stream;
}

Polygon::Polygon(const std::initializer_list<P>& list) : points(list) {
}

Polygon::Polygon(const std::vector<P>& points) : points(points) {
}

auto Polygon::Segments() const {
  std::vector<Segment> segments;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    segments.push_back(Segment(points[i], points[i + 1]));
  }
  segments.push_back(Segment(points.back(), points.front()));
  return segments;
}

IShape& Polygon::Move(const Vector& v) {
  for (P& p : points) {
    p.Move(v);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& p) const {
  auto ray = Ray(p, Vector(1, 10000));
  size_t count = 0;
  for (const auto& segment : Segments()) {
    if (ray.CrossesSegment(segment)) {
      ++count;
    }
  }
  return count % 2 == 1;
}

bool Polygon::CrossesSegment(const Segment& s) const {
  auto ray = Ray(s);
  for (const auto& segment : Segments()) {
    if (ray.CrossesSegment(segment)) {
      return true;
    }
  }
  return false;
}

std::shared_ptr<IShape> Polygon::Clone() const {
  return std::make_shared<Polygon>(points);
}

std::string Polygon::ToString() const {
  std::string repr = "Polygon(";
  for (const auto& p : points) {
    repr += (boost::format(", %1%") % p).str();
  }
  repr += ")";
  return repr;
}

std::istream& operator>>(std::istream& stream, Polygon& poly) {
  size_t count = 0;
  stream >> count;
  for (size_t i = 0; i < count; ++i) {
    poly.points.push_back(InputResult<Point>());
  }
  return stream;
}

} // namespace geometry

using namespace geometry;

template <class T>
const Point<T>& FindMinPoint(const Poligon<T>& poligon) {
  Point<T>* min = nullptr;
  for (auto point : poligon) {
    if (!min || point.y < min->y || point.y == min->y && point.x < min->x) {
      min = &point;
    }
  }
  return *min;
}

template <class T>
void SortPoligonByAngles(Poligon<T>& poligon) {
  const Point<T> min_point = FindMinPoint(poligon);
  std::cout << min_point << std::endl;
  auto cmp_less = [&min_point](const Point<T>& a, const Point<T>& b) -> bool {
    Vector<T> ma(min_point, a);
    Vector<T> mb(min_point, b);
    auto area = Vector<T>::SignedArea(ma, mb);
    if (area > 0) {
      return true;
    }
    if (area == 0) {
      return (ma.LongerThan(mb) ? false : true);
    }
    if (area < 0) {
      return false;
    }
    throw std::logic_error("");
  };
  
  std::sort(poligon.begin(), poligon.end(), cmp_less);
}

template <class T>
auto FindConvexHull(Poligon<T>& poligon) {
  Poligon<T>& result;
  SortPoligonByAngles(poligon);
  size_t size = poligon.Size();
  result.push_back(poligon.At(0));
  result.push_back(poligon.At(1));
  for (size_t cur_point_index = 2; cur_point_index < size; ++cur_point_index) {
    while () {}
  }
}

int main() {
  Poligon<int> poligon{{1, 2}, {2, 1}, {-2, 1}, {0, 0}};
  for (auto point : poligon) {
    std::cout << point << std::endl;
  }
  SortPoligonByAngles(poligon);
}
