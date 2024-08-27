#include "../ray.h"

namespace geometry {

Ray::Ray(const PointType& start_point, const VectorType& directing_vector)
    : start_point(start_point), directing_vector(directing_vector) {
}

Ray::Ray(const PointType& start_point, const PointType& end_point)
    : start_point(start_point), directing_vector(VectorType(start_point, end_point)) {
}

Ray::Ray(const Segment& segment) : Ray(segment.first_point, VectorType(segment.first_point, segment.second_point)) {
}

Ray::operator Line() {
  return {start_point, directing_vector};
}

bool Ray::IsUndefined() const {
  return directing_vector.IsZero();
}

bool Ray::IsDefined() const {
  return !IsUndefined();
}

IShape& Ray::Move(const Vector& vector) {
  start_point.Move(vector);
  return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::ContainsPoint(): ray is undefined.");
  }
  bool on_the_line = Line(*this).ContainsPoint(point);
  return on_the_line && PointsTo(point);
}

bool Ray::CrossesSegment(const Segment& segment) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::CrossesSegment(): ray is undefined.");
  }
	if (!Line(*this).CrossesSegment(segment)) {
		return false;
	}
  VectorType a(start_point, segment.first_point);
  VectorType b(start_point, segment.second_point);
  VectorType c = directing_vector;
  auto vp_ac = VectorType::SignedArea(a, c);
  auto vp_bc = VectorType::SignedArea(b, c);
  auto sp_bc = VectorType::ScalarProduct(b, c);
  auto sp_ac = VectorType::ScalarProduct(a, c);
  return std::abs(vp_ac) * sp_bc + std::abs(vp_bc) * sp_ac >= 0;
}

std::shared_ptr<IShape> Ray::Clone() const {
  return std::make_shared<Ray>(start_point, directing_vector);
}

std::string Ray::ToString() const {
  // return (boost::format("Ray(%1%, %2%)") % start_point % directing_vector).str();
  std::stringstream ss;
  ss << "Ray(" << start_point << ", " << directing_vector << ")";
  return ss.str();
}

bool Ray::PointsTo(const PointType& point) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::PointsTo(): ray is undefined.");
  }
  return directing_vector.PointsTo(VectorType(start_point, point));
}

std::istream& operator>>(std::istream& stream, Ray& ray) {
  stream >> ray.start_point >> ray.directing_vector;
  return stream;
}

}  // namespace geometry
