
#include "../segment.h"

namespace geometry {

bool Point::CrossesSegment(const Segment& segment) const {
  return segment.ContainsPoint(*this);
}

Segment::Segment(const PointType& first, const PointType& second) : first_point(first), second_point(second) {
}

auto Segment::GetDirectingVector() const {
  return VectorType(first_point, second_point);
}

auto Segment::SquaredLength() const {
  return GetDirectingVector().SquaredLength();
}

auto Segment::Length() const {
  return GetDirectingVector().Length();
}

bool Segment::IsPoint() const {
  return first_point == second_point;
}

// Assume point is on the line (first_point, second_point).
// Return true if segment contains point.
bool Segment::ContainsPointOnSameLine(const PointType& point) const {
  auto vec = VectorType(first_point, point);
  auto prod = VectorType::ScalarProduct(vec, VectorType(first_point, second_point));
  return 0 <= prod && prod <= SquaredLength();
}

// Assume first_segment and second_segment are on the same line.
// Return true if first_segment and second_segment overlap.
bool Segment::OverlapOnSameLine(const Segment& first_segment, const Segment& second_segment) {
  return first_segment.ContainsPointOnSameLine(second_segment.first_point) ||
         first_segment.ContainsPointOnSameLine(second_segment.second_point);
}

IShape& Segment::Move(const Vector& vector) {
  first_point.Move(vector);
  second_point.Move(vector);
  return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
  if (this->IsPoint()) {
    return point == first_point;
  }
  bool on_the_line = Line(*this).ContainsPoint(point);
  return on_the_line && ContainsPointOnSameLine(point);
}

bool Segment::CrossesSegment(const Segment& segment) const {
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

std::shared_ptr<IShape> Segment::Clone() const {
  return std::make_shared<Segment>(first_point, second_point);
}

std::string Segment::ToString() const {
  // return (boost::format("Segment(%1%, %2%)") % first_point % second_point).str();
  std::stringstream ss;
  ss << "Segment(" << first_point << ", " << second_point << ")";
  return ss.str();
}

std::istream& operator>>(std::istream& stream, Segment& section) {
  stream >> section.first_point >> section.second_point;
  return stream;
}

double Distance(const Point& point, const Segment& segment) {
	if (segment.IsPoint()) {
		return Distance(point, segment.first_point);
	}
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

}  // namespace geometry