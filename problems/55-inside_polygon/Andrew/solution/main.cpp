// Copyright 2024 Andrew
// H-inside_polygon

#include <iterator>
#include <type_traits>

#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <sstream>
#include <vector>
#include <functional>

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

template <class T, class IStream = std::istream>
T InputResult(IStream& stream = std::cin) {
  T value;
  stream >> value;
  return value;
}

namespace geometry {

using namespace std::literals;

// declarations
template <class T>
struct Point;
template <class T>
struct Vector;
template <class T>
struct Segment;
template <class T>
struct Line;
template <class T>
struct Ray;
template <class T>
struct Polygon;

// ishape.h
// point.h
template <class T>
struct Point {
 public:
  using VectorType = Vector<T>;
  using SegmentType = Segment<T>;

 public:
  Point() = default;

  Point(const T& x, const T& y);

  bool ContainsPoint(const Point&) const;

  bool CrossesSegment(const SegmentType&) const;

  VectorType operator-(const Point&) const;

  bool operator==(const Point&) const;

  bool operator!=(const Point&) const;

 public:
  T x;
  T y;
};

template <class T>
T SquaredDistance(const Point<T>&, const Point<T>&);

template <class T>
struct Vector {
  T x = 0;
  T y = 0;

  using PointType = Point<T>;

  Vector() = default;

  Vector(const T& x, const T& y);

  Vector(const PointType&);  // NOLINT

  Vector(const PointType& begin, const PointType& end);

  operator PointType() const;  // NOLINT

  bool IsZero() const;

  T SquaredLength() const;

  static T Dot(const Vector&, const Vector&);

  static T Cross(const Vector&, const Vector&);

  static bool Parallel(const Vector&, const Vector&);

  bool PointsTo(const PointType&) const;

  T VectorProduct(const Vector&) const;

  Vector& operator+=(const Vector&);

  Vector operator+(const Vector&) const;

  Vector& operator-=(const Vector&);

  Vector operator-(const Vector&) const;

  Vector operator-() const;

  bool operator==(const Vector&) const;
};

// segment.h
template <class T>
struct Segment {
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;

  PointType first_point = PointType();
  PointType second_point = PointType();

  Segment() = default;

  Segment(const PointType&, const PointType&);

  auto GetDirectingVector() const;

  auto SquaredLength() const;

  auto Length() const;

  bool IsPoint() const;

 protected:
  bool ContainsPointOnSameLine(const PointType&) const;

  static bool OverlapOnSameLine(const Segment&, const Segment&);

 public:
  bool ContainsPoint(const PointType&) const;

  bool CrossesSegment(const Segment&) const;
};

// ray.h
template <class T>
struct Ray {
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;
  using SegmentType = Segment<T>;

  PointType start_point = PointType();
  VectorType directing_vector = VectorType();

  Ray() = default;

  Ray(const PointType& start_point, const VectorType& directing_vector);

  Ray(const PointType& start_point, const PointType& end_point);

  explicit Ray(const SegmentType&);

  explicit operator LineType();

  bool IsUndefined() const;

  bool IsDefined() const;

  bool ContainsPoint(const PointType&) const;

  bool CrossesSegment(const SegmentType&) const;

  bool PointsTo(const PointType&) const;
};

// line.h
template <class T>
struct Line {
 public:
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;
  using SegmentType = Segment<T>;
  using RayType = Ray<T>;

 protected:
  /*
    Suppose line is determined by equation ax + by + c = 0 (a^2 + b^2 > 0).
    Finds any point of this line.
  */
  template <class R>
  static PointType FindAnyPoint(const R& a, const R& b, const R& c);

 public:
  Line() = default;

  Line(const PointType&, const PointType&);

  Line(const PointType& point, const VectorType& directing_vector);

  template <class R>
  Line(const R& a, const R& b, const R& c);

  Line(const Line&) = default;

  explicit Line(const RayType&);

  explicit Line(const SegmentType&);

  Line& operator=(const Line&) = default;

  bool IsUndefined() const;

  bool IsDefined() const;

  bool ContainsPoint(const PointType&) const;

  bool CrossesSegment(const SegmentType&) const;

  const VectorType& GetDirectingVector() const;

  VectorType& GetDirectingVector();

  void SetDirectingVector(const VectorType&);

  const PointType& GetPoint() const;

  PointType& GetPoint();

  void SetPoint(const PointType&);

  static bool Parallel(const Line& first, const Line& second);

 public:
  PointType point = PointType();
  VectorType directing_vector = VectorType();
};

// polygon.h
template <class T>
struct Polygon {
 public:
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;
  using SegmentType = Segment<T>;
  using RayType = Ray<T>;
  using RadiusType = T;

 public:
  Polygon() = default;

  Polygon(const std::initializer_list<PointType>&);  // NOLINT

  explicit Polygon(const std::vector<PointType>&);

  auto Segments() const;

  bool ContainsPoint(const PointType&) const;

  bool CrossesSegment(const SegmentType&) const;

 public:
  std::vector<PointType> points;
};

// point.cpp
template <class T>
Point<T>::Point(const T& x, const T& y) : x(x), y(y) {
}

template <class T>
bool Point<T>::ContainsPoint(const Point<T>& other) const {
  return (*this) == other;
}

template <class T>
typename Point<T>::VectorType Point<T>::operator-(const Point& other) const {
  return {other, *this};
}

template <class T>
bool Point<T>::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

template <class T>
bool Point<T>::operator!=(const Point& other) const {
  return !(*this == other);
}

template <class T>
std::istream& operator>>(std::istream& stream, Point<T>& point) {
  stream >> point.x >> point.y;
  return stream;
}

template <class T>
T SquaredDistance(const Point<T>& first, const Point<T>& second) {
  return Vector(first, second).SquaredLength();
}

// vector.cpp
template <class T>
Vector<T>::Vector(const T& x, const T& y) : x(x), y(y) {
}

template <class T>
Vector<T>::Vector(const PointType& point) : Vector(point.x, point.y) {  // NOLINT
}

template <class T>
Vector<T>::Vector(const PointType& begin, const PointType& end) : Vector(end.x - begin.x, end.y - begin.y) {
}

template <class T>
Vector<T>::operator PointType() const {
  return {x, y};
}

template <class T>
bool Vector<T>::IsZero() const {
  return x == 0 && y == 0;
}

template <class T>
T Vector<T>::SquaredLength() const {
  return Dot(*this, *this);
}

template <class T>
T Vector<T>::Dot(const Vector& first, const Vector& second) {
  return first.x * second.x + first.y * second.y;
}

template <class T>
T Vector<T>::Cross(const Vector& first, const Vector& second) {
  return first.x * second.y - first.y * second.x;
}

template <class T>
bool Vector<T>::Parallel(const Vector& first, const Vector& second) {
  if (first.IsZero() || second.IsZero()) {
    throw std::logic_error("Method 'Vector::Parallel' for zero-vector is undefined.");
  }
  return Cross(first, second) == 0;
}

template <class T>
bool Vector<T>::PointsTo(const PointType& point) const {
  if (this->IsZero()) {
    throw std::logic_error("Method 'Vector::PointsTo' for zero-vector is undefined.");
  }
  return Dot(Vector(point), *this) >= 0;
}

template <class T>
T Vector<T>::VectorProduct(const Vector& other) const {
  return Cross(*this, other);
}

template <class T>
Vector<T>& Vector<T>::operator+=(const Vector& other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <class T>
Vector<T> Vector<T>::operator+(const Vector& other) const {
  auto result = *this;
  result += other;
  return result;
}

template <class T>
Vector<T>& Vector<T>::operator-=(const Vector& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <class T>
Vector<T> Vector<T>::operator-(const Vector& other) const {
  auto result = *this;
  result -= other;
  return result;
}

template <class T>
Vector<T> Vector<T>::operator-() const {
  return {-x, -y};
}

template <class T>
bool Vector<T>::operator==(const Vector& other) const {
  return x == other.x && y == other.y;
}

// segment.cpp
template <class T>
bool Point<T>::CrossesSegment(const Segment<T>& segment) const {
  return segment.ContainsPoint(*this);
}

template <class T>
Segment<T>::Segment(const PointType& first, const PointType& second) : first_point(first), second_point(second) {
}

template <class T>
auto Segment<T>::GetDirectingVector() const {
  return VectorType(first_point, second_point);
}

template <class T>
auto Segment<T>::SquaredLength() const {
  return GetDirectingVector().SquaredLength();
}

template <class T>
auto Segment<T>::Length() const {
  return GetDirectingVector().Length();
}

template <class T>
bool Segment<T>::IsPoint() const {
  return first_point == second_point;
}

// Assume point is on the line (first_point, second_point).
// Return true if segment contains point.
template <class T>
bool Segment<T>::ContainsPointOnSameLine(const PointType& point) const {
  auto vec = VectorType(first_point, point);
  auto prod = VectorType::Dot(vec, VectorType(first_point, second_point));
  return 0 <= prod && prod <= SquaredLength();
}

// Assume first_segment and second_segment are on the same line.
// Return true if first_segment and second_segment overlap.
template <class T>
bool Segment<T>::OverlapOnSameLine(const Segment& first_segment, const Segment& second_segment) {
  return first_segment.ContainsPointOnSameLine(second_segment.first_point) ||
         first_segment.ContainsPointOnSameLine(second_segment.second_point);
}

template <class T>
bool Segment<T>::ContainsPoint(const Point<T>& point) const {
  if (this->IsPoint()) {
    return point == first_point;
  }
  bool on_the_line = Line(*this).ContainsPoint(point);
  return on_the_line && ContainsPointOnSameLine(point);
}

template <class T>
bool Segment<T>::CrossesSegment(const Segment& segment) const {
  if (this->IsPoint()) {
    return segment.ContainsPoint(first_point);
  }
  if (segment.IsPoint()) {
    return this->ContainsPoint(segment.first_point);
  }
  Line first_line(*this);
  Line second_line(segment);
  if (!(first_line.CrossesSegment(segment) && second_line.CrossesSegment(*this))) {
    return false;
  }
  if (LineType::Parallel(first_line, second_line)) {  // first_line == second_line
    return OverlapOnSameLine(*this, segment);
  }
  return true;
}

template <class T>
std::istream& operator>>(std::istream& stream, Segment<T>& section) {
  stream >> section.first_point >> section.second_point;
  return stream;
}

// ray.cpp
template <class T>
Ray<T>::Ray(const PointType& start_point, const VectorType& directing_vector)
    : start_point(start_point), directing_vector(directing_vector) {
}

template <class T>
Ray<T>::Ray(const PointType& start_point, const PointType& end_point)
    : start_point(start_point), directing_vector(VectorType(start_point, end_point)) {
}

template <class T>
Ray<T>::Ray(const SegmentType& segment)
    : Ray(segment.first_point, VectorType(segment.first_point, segment.second_point)) {
}

template <class T>
Ray<T>::operator LineType() {
  return {start_point, directing_vector};
}

template <class T>
bool Ray<T>::IsUndefined() const {
  return directing_vector.IsZero();
}

template <class T>
bool Ray<T>::IsDefined() const {
  return !IsUndefined();
}

template <class T>
bool Ray<T>::ContainsPoint(const PointType& point) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::ContainsPoint(): ray is undefined.");
  }
  bool on_the_line = Line(*this).ContainsPoint(point);
  return on_the_line && PointsTo(point);
}

template <class T>
bool Ray<T>::CrossesSegment(const SegmentType& segment) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::CrossesSegment(): ray is undefined.");
  }
  if (!LineType(*this).CrossesSegment(segment)) {
    return false;
  }
  VectorType a(start_point, segment.first_point);
  VectorType b(start_point, segment.second_point);
  VectorType c = directing_vector;
  auto vp_ac = VectorType::Cross(a, c);
  auto vp_bc = VectorType::Cross(b, c);
  auto sp_bc = VectorType::Dot(b, c);
  auto sp_ac = VectorType::Dot(a, c);
  return std::abs(vp_ac) * sp_bc + std::abs(vp_bc) * sp_ac >= 0;
}

template <class T>
bool Ray<T>::PointsTo(const PointType& point) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::PointsTo(): ray is undefined.");
  }
  return directing_vector.PointsTo(VectorType(start_point, point));
}

template <class T>
std::istream& operator>>(std::istream& stream, Ray<T>& ray) {
  stream >> ray.start_point >> ray.directing_vector;
  return stream;
}

// line.cpp
template <class T>
template <class R>
typename Line<T>::PointType Line<T>::FindAnyPoint(const R& a, const R& b, const R& c) {
  if (a == 0) {
    if (b == 0) {
      throw std::invalid_argument("a and b cannot be zero");
    }
    return {0, -static_cast<T>(c) / static_cast<T>(b)};
  }
  return {-static_cast<T>(c) / static_cast<T>(a), 0};
}

template <class T>
Line<T>::Line(const PointType& point, const VectorType& directing_vector)
    : point(point), directing_vector(directing_vector) {
}

template <class T>
Line<T>::Line(const PointType& first, const PointType& second) : Line(first, VectorType(first, second)) {
}

template <class T>
template <class R>
Line<T>::Line(const R& a, const R& b, const R& c) : Line(FindAnyPoint(a, b, c), VectorType(b, -a)) {
}

template <class T>
Line<T>::Line(const Ray<T>& ray) : Line(ray.start_point, ray.directing_vector) {
}
template <class T>
Line<T>::Line(const SegmentType& segment) : Line(segment.first_point, segment.second_point) {
}

template <class T>
bool Line<T>::IsUndefined() const {
  return GetDirectingVector().IsZero();
}

template <class T>
bool Line<T>::IsDefined() const {
  return !IsUndefined();
}

template <class T>
bool Line<T>::ContainsPoint(const PointType& p) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Line::ContainsPoint: Line is undefined.");
  }
  VectorType to_p(GetPoint(), p);
  if (to_p.IsZero()) {
    return true;
  }
  return VectorType::Parallel(VectorType(GetPoint(), p), GetDirectingVector());
}

template <class T>
bool Line<T>::CrossesSegment(const SegmentType& segment) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Line::CrossesSegment: Line is undefined.");
  }
  // v := VectorType::SignedArea(VectorType(point, p), directing_vector)
  // if (v > 0): p is to the left of line, if (v < 0): - to the right.
  // if (segment.first_point and segment.second_point are on the same side of the line): line does not cross segment.
  // else: line crosses segment.
  VectorType to_first(GetPoint(), segment.first_point);
  VectorType to_second(GetPoint(), segment.second_point);
  auto first_point_info = VectorType::Cross(to_first, GetDirectingVector());
  auto second_point_info = VectorType::Cross(to_second, GetDirectingVector());
  return first_point_info * second_point_info <= 0;
}

template <class T>
const typename Line<T>::VectorType& Line<T>::GetDirectingVector() const {
  return directing_vector;
}

template <class T>
typename Line<T>::VectorType& Line<T>::GetDirectingVector() {
  return directing_vector;
}

template <class T>
void Line<T>::SetDirectingVector(const VectorType& vector) {
  this->directing_vector = vector;
}

template <class T>
const typename Line<T>::PointType& Line<T>::GetPoint() const {
  return point;
}

template <class T>
typename Line<T>::PointType& Line<T>::GetPoint() {
  return point;
}

template <class T>
void Line<T>::SetPoint(const PointType& point) {
  this->point = point;
}

template <class T>
bool Line<T>::Parallel(const Line& first, const Line& second) {
  if (first.IsUndefined() || second.IsUndefined()) {
    throw std::logic_error("Method 'Line::Parallel' for undefined lines is undefined.");
  }
  return VectorType::Parallel(first.GetDirectingVector(), second.GetDirectingVector());
}

template <class T>
auto Polygon<T>::Segments() const {
  std::vector<SegmentType> segments;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    segments.emplace_back(points[i], points[i + 1]);
  }
  segments.emplace_back(points.back(), points.front());
  return segments;
}

template <class T>
bool Polygon<T>::ContainsPoint(const PointType& point) const {
  // T max = std::numeric_limits<T>::max();
  T max = 2000000;
  auto ray = Ray(point, VectorType(max, 1));
  size_t count = 0;
  for (const auto& segment : Segments()) {
    if (segment.ContainsPoint(point)) {
      return true;
    }
    if (ray.CrossesSegment(segment)) {
      ++count;
    }
  }
  return count % 2 == 1;
}
}  // namespace geometry

template <class T, class IStream = std::istream>
void InputPolygonN(geometry::Polygon<T>& polygon, size_t n, IStream& istream = std::cin) {
  polygon.points.reserve(polygon.points.size() + n);
  for (size_t i = 0; i < n; ++i) {
    polygon.points.emplace_back(InputResult<typename geometry::Polygon<T>::PointType>(istream));
  }
}

template <class T>
void Solution(const geometry::Polygon<T>& polygon, const geometry::Point<T>& point) {
  std::cout << (polygon.ContainsPoint(point) ? "YES" : "NO") << '\n';
}

int main() {
  using T = int64_t;

  size_t n{};
  geometry::Point<T> point;
  geometry::Polygon<T> polygon;

  std::cin >> n >> point;

  InputPolygonN(polygon, n);

  Solution(polygon, point);
}
