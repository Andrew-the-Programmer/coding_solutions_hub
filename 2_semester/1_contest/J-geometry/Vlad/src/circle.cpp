#include "../circle.h"

namespace geometry {

Circle::Circle(const RadiusType& radius, const PointType& center) : radius(radius), center(center) {
}

Circle::Circle(const PointType& center, const RadiusType& radius) : Circle(radius, center) {
}

IShape& Circle::Move(const Vector& vector) {
  center.Move(vector);
  return *this;
}

template <typename Cmp>
bool Circle::CompareDistanceToPointAndRadius(const PointType& point, const Cmp& cmp) const {
  return cmp(static_cast<RadiusType>(SquaredDistance(center, point)), Squared(radius));
}

bool Circle::ContainsPoint(const Point& point) const {
  return CompareDistanceToPointAndRadius<std::less_equal<RadiusType>>(point);
}

bool Circle::StrictlyContainsPoint(const Point& point) const {	
  return CompareDistanceToPointAndRadius<std::less<RadiusType>>(point);
}

bool Circle::CrossesSegment(const Segment& segment) const {
  if (StrictlyContainsPoint(segment.first_point) && StrictlyContainsPoint(segment.second_point)) {
    return false;
  }
  return Distance(center, segment) <= static_cast<double>(radius);
}

std::shared_ptr<IShape> Circle::Clone() const {
  return std::make_shared<Circle>(*this);
}

std::string Circle::ToString() const {
  // return (boost::format("Circle(%1%, %2%)") % center % radius).str();
  std::stringstream ss;
  ss << "Circle(" << center << ", " << radius << ")";
  return ss.str();
}

std::istream& operator>>(std::istream& stream, Circle& circle) {
  stream >> circle.center >> circle.radius;
  return stream;
}

}  // namespace geometry