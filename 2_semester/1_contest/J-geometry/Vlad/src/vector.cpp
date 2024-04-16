
#include "../vector.h"

namespace geometry {

Vector::Vector(const T& x, const T& y) : x(x), y(y) {
}

Vector::Vector(const Point& point) : Vector(point.x, point.y) {  // NOLINT
}

Vector::Vector(const Point& begin, const Point& end) : Vector(end.x - begin.x, end.y - begin.y) {
}

Vector::operator Point() const {
  return {x, y};
}

bool Vector::IsZero() const {
  return x == 0 && y == 0;
}

T Vector::SquaredLength() const {
  return ScalarProduct(*this, *this);
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
  if (first.IsZero() || second.IsZero()) {
    throw std::logic_error("Method 'Vector::Parallel' for zero-vector is undefined.");
  }
  return SignedArea(first, second) == 0;
}

bool Vector::PointsTo(const Point& point) const {
  if (this->IsZero()) {
    throw std::logic_error("Method 'Vector::PointsTo' for zero-vector is undefined.");
  }
  return ScalarProduct(Vector(point), *this) >= 0;
}

double Vector::Sin(const Vector& first, const Vector& second) {
  return static_cast<double>(SignedArea(first, second)) / (first.Length() * second.Length());
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
  return {-x, -y};
}

bool Vector::operator==(const Vector& other) const {
  return x == other.x && y == other.y;
}

std::string Vector::ToString() const {
  // return (boost::format("Vector(%1%, %2%)") % x % y).str();
  std::stringstream ss;
  ss << "Vector(" << x << ", " << y << ")";
  return ss.str();
}

std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
  stream << vector.ToString();
  return stream;
}

std::istream& operator>>(std::istream& stream, Vector& vector) {
  stream >> vector.x >> vector.y;
  return stream;
}

}  // namespace geometry
