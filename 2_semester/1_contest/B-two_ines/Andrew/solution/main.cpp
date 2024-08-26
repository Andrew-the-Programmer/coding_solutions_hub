#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <sstream>

using namespace std::literals;

using distance_type = double;  // NOLINT

struct IShape {
  virtual ~IShape() = default;
  virtual std::string ToString() const = 0;

  friend std::ostream& operator<<(std::ostream& stream, const IShape& shape) {
    stream << shape.ToString();
    return stream;
  }
};

template <class T>
struct Point : public IShape {
  T x;
  T y;

  Point() = default;

  Point(const T& x, const T& y);

  std::string ToString() const override {
    std::stringstream ss;
    ss << "Point(" << x << ", " << y << ")";
    return ss.str();
  }

  bool operator==(const Point&) const = default;
  bool operator!=(const Point&) const = default;

  template <class U>
  friend auto& operator>>(std::istream& stream, Point<U>& point) {
    stream >> point.x >> point.y;
    return stream;
  }
};

template <class T>
double Distance(const Point<T>&, const Point<T>&);

template <class T>
class Vector {
 public:
  using PointType = Point<T>;

 public:
  T x;
  T y;

 public:
  Vector(const T& x, const T& y) : x(x), y(y) {
  }

  Vector() : Vector(0, 0) {
  }

  Vector(const PointType& point) : Vector(point.x, point.y) {  // NOLINT
  }

  Vector(const PointType& begin, const PointType& end) : Vector(end.x - begin.x, end.y - begin.y) {
  }

  operator PointType() const {
    return {x, y};
  }

  bool IsZero() const {
    return x == 0 && y == 0;
  }

  Vector(const Vector& begin, const Vector& end) : Vector(end - begin) {
  }

  double Length() {
    return std::sqrt(this->Dot(*this));
  }

  T Dot(const Vector& other) const {
    return x * other.x + y * other.y;
  }

  T Cross(const Vector& other) const {
    return x * other.y - y * other.x;
  }

  Vector operator+(const Vector& other) const {
    return {x + other.x, y + other.y};
  }

  Vector operator-() const {
    return {-x, -y};
  }

  Vector operator-(const Vector& other) const {
    return *this + (-other);
  }

  template <class IStream>
  void InputAsPoint(IStream& istream = std::cin) {
    istream >> x >> y;
  }

  template <class IStream>
  void InputAsBeginEnd(IStream& istream = std::cin) {
    Vector begin;
    Vector end;
    begin.InputAsPoint(istream);
    end.InputAsPoint(istream);
    *this = Vector(begin, end);
  }

  friend std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
    stream << vector.x << ' ' << vector.y;
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, Vector& vector) {
    vector.InputAsBeginEnd(stream);
    return stream;
  }
};

template <class PointT, class VectorT>
struct Line {
 public:
  using PointType = PointT;
  using VectorType = VectorT;

  PointType point = PointType();
  VectorType directing_vector = VectorType();

 public:  //^ public constructors
  Line() = default;

  Line(const PointType& first, const PointType& second) : Line(first, VectorType(first, second)) {
  }

  Line(const PointType& point, const VectorType& directing_vector) : point(point), directing_vector(directing_vector) {
  }

  template <class R>
  Line(const R& a, const R& b, const R& c) : Line(FindAnyPoint(a, b, c), VectorType(b, -a)) {
  }

  Line(const Line&) = default;

  Line& operator=(const Line&) = default;

 public:  //^ simple public methods
  bool IsUndefined() const {
    return GetDirectingVector().IsZero();
  }

  bool IsDefined() const {
    return !IsUndefined();
  }

  const VectorType& GetDirectingVector() const {
    return directing_vector;
  }

  VectorType& GetDirectingVector() {
    return directing_vector;
  }

  void SetDirectingVector(const VectorType& vector) {
    this->directing_vector = vector;
  }

  const PointType& GetPoint() const {
    return point;
  }

  PointType& GetPoint() {
    return point;
  }

  void SetPoint(const PointType& point) {
    this->point = point;
  }

 protected:  //^ complex protected methods
  /*
    Suppose line is determined by equation ax + by + c = 0 (a^2 + b^2 > 0).
    Finds any point of this line.
  */
  template <class R>
  static PointType FindAnyPoint(const R& a, const R& b, const R& c) {
    if (a == 0) {
      if (b == 0) {
        throw std::invalid_argument("a and b cannot be zero");
      }
      return {0, c / b};
    }
    return {-static_cast<T>(c) / static_cast<T>(a), 0};
  }

 public:
  // return (a,b,c): ax + by + c = 0
  auto GetPolynomialReprArgs() const {
    auto a = GetDirectingVector().y;
    auto b = -GetDirectingVector().x;
    auto c = -(a * GetPoint().x + b * GetPoint().y);
    return std::make_tuple(a, b, c);
  }

  std::string PolynomialRepr() const {
    auto args = GetPolynomialReprArgs();
    std::stringstream ss;
    ss << "Line(" << std::get<0>(args) << ", " << std::get<1>(args) << ", " << std::get<2>(args) << ")";
    return ss.str();
  }

  std::string PointAndVectorRepr() const {
    std::stringstream ss;
    ss << "Line(" << GetPoint() << ", " << GetDirectingVector() << ")";
    return ss.str();
  }

  std::string ToString() const {
    return PolynomialRepr();
  }

  bool Parallel(const Line& first, const Line& second) {
    if (first.IsUndefined() || second.IsUndefined()) {
      throw std::logic_error("Method 'Parallel' for undefined lines is undefined.");
    }
    return VectorType::Parallel(first.GetDirectingVector(), second.GetDirectingVector());
  }

  template <class R>
  void InputAsPolynom(std::istream& stream) {
    R a;
    R b;
    R c;
    stream >> a >> b >> c;
    *this = Line(a, b, c);
  }
  friend auto& operator>>(std::istream& stream, Line& line) {
    line.InputAsPolynom(stream);
    return stream;
  }
};

int main() {
  auto cmp = [](){};
  x
}
