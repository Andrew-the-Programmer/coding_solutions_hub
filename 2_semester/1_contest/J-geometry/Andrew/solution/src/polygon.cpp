#include "../polygon.h"

namespace geometry {

Polygon::Polygon(const std::initializer_list<PointType>& list) : points(list) {}

Polygon::Polygon(const std::vector<PointType>& points) : points(points) {}

auto Polygon::Segments() const {
  std::vector<Segment> segments;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    segments.emplace_back(points[i], points[i + 1]);
  }
  segments.emplace_back(points.back(), points.front());
  return segments;
}

IShape& Polygon::Move(const Vector& vector) {
  for (PointType& point : points) {
    point.Move(vector);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
	// T max = std::numeric_limits<T>::max();
	T max = 200000;
  auto ray = Ray(point, Vector(max, 1));
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

bool Polygon::CrossesSegment(const Segment& segment) const {
  for (const auto& s : Segments()) {
    if (segment.CrossesSegment(s)) {
      return true;
    }
  }
  return false;
}

std::shared_ptr<IShape> Polygon::Clone() const {
  return std::make_shared<Polygon>(points);
}

std::string Polygon::ToString() const {
  std::stringstream ss;
  ss << "Polygon(";
  for (size_t i = 0; i < points.size(); ++i) {
    if (i != 0) {
      ss << ", ";
    }
    ss << points[i];
  }
  ss << ")";
  return ss.str();
}

std::istream& operator>>(std::istream& stream, Polygon& poly) {
  size_t count = 0;
  stream >> count;
  for (size_t i = 0; i < count; ++i) {
    poly.points.push_back(InputResult<Point>());
  }
  return stream;
}

}  // namespace geometry
