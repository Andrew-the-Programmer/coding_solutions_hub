
#include "../point.h"

namespace geometry {

Point::Point(const T& x, const T& y) : x(x), y(y) {
}

Point& Point::Move(const Vector& vector) {
  x += vector.x;
  y += vector.y;
  return *this;
}

bool Point::ContainsPoint(const Point& other) const {
  return (*this) == other;
}

std::shared_ptr<IShape> Point::Clone() const {
  return std::make_shared<Point>(x, y);
}

std::string Point::ToString() const {
  // return (boost::format("Point(%1%, %2%)") % x % y).str();
  std::stringstream ss;
  ss << "Point(" << x << ", " << y << ")";
  return ss.str();
}

Vector Point::operator-(const Point& other) const {
  return {other, *this};
}

bool Point::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
  return !(*this == other);
}

std::istream& operator>>(std::istream& stream, Point& point) {
  stream >> point.x >> point.y;
  return stream;
}

T SquaredDistance(const Point& first, const Point& second) {
	return Vector(first, second).SquaredLength();
}

double Distance(const Point& first, const Point& second) {
  return Vector(first, second).Length();
}

}  // namespace geometry
