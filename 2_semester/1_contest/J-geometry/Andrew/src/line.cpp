
#include "../line.h"

namespace geometry {

template <class R>
Line::PointType Line::FindAnyPoint(const R& a, const R& b, const R& c) {
  if (a == 0) {
    if (b == 0) {
      throw std::invalid_argument("a and b cannot be zero");
    }
    return {0, -static_cast<T>(c) / static_cast<T>(b)};
  }
  return {-static_cast<T>(c) / static_cast<T>(a), 0};
}

Line::Line(const PointType& point, const VectorType& directing_vector)
    : point(point), directing_vector(directing_vector) {
}

Line::Line(const PointType& first, const PointType& second) : Line(first, VectorType(first, second)) {
}

template <class R>
Line::Line(const R& a, const R& b, const R& c) : Line(FindAnyPoint(a, b, c), VectorType(b, -a)) {
}

Line::Line(const Ray& ray) : Line(ray.start_point, ray.directing_vector) {
}
Line::Line(const Segment& segment) : Line(segment.first_point, segment.second_point) {
}

bool Line::IsUndefined() const {
  return GetDirectingVector().IsZero();
}

bool Line::IsDefined() const {
  return !IsUndefined();
}

IShape& Line::Move(const Vector& vector) {
  point.Move(vector);
  return *this;
}

bool Line::ContainsPoint(const PointType& p) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Line::ContainsPoint: Line is undefined.");
  }
	VectorType to_p(GetPoint(), p);
	if (to_p.IsZero()) {
		return true;
	}
  return VectorType::Parallel(VectorType(GetPoint(), p), GetDirectingVector());
}

bool Line::CrossesSegment(const Segment& segment) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Line::CrossesSegment: Line is undefined.");
  }
  // v := VectorType::SignedArea(VectorType(point, p), directing_vector)
  // if (v > 0): p is to the left of line, if (v < 0): - to the right.
  // if (segment.first_point and segment.second_point are on the same side of the line): line does not cross segment.
  // else: line crosses segment.
	VectorType to_first(GetPoint(), segment.first_point);
	VectorType to_second(GetPoint(), segment.second_point);
  auto first_point_info = VectorType::SignedArea(to_first, GetDirectingVector());
  auto second_point_info = VectorType::SignedArea(to_second, GetDirectingVector());
  return first_point_info * second_point_info <= 0;
}

std::shared_ptr<IShape> Line::Clone() const {
  return std::make_shared<Line>(*this);
}

const Line::VectorType& Line::GetDirectingVector() const {
  return directing_vector;
}

Line::VectorType& Line::GetDirectingVector() {
  return directing_vector;
}

void Line::SetDirectingVector(const VectorType& vector) {
  this->directing_vector = vector;
}

const Line::PointType& Line::GetPoint() const {
  return point;
}

Line::PointType& Line::GetPoint() {
  return point;
}

void Line::SetPoint(const PointType& point) {
  this->point = point;
}

// return (a,b,c): ax + by + c = 0
auto Line::GetPolynomialReprArgs() const {
  auto a = GetDirectingVector().y;
  auto b = -GetDirectingVector().x;
  auto c = -(a * GetPoint().x + b * GetPoint().y);
  return std::make_tuple(a, b, c);
}

std::string Line::PolynomialRepr() const {
  auto args = GetPolynomialReprArgs();
  // return (boost::format("Line(%1%, %2%, %3%)") % std::get<0>(args) %
  // std::get<1>(args) % std::get<2>(args)).str();
  std::stringstream ss;
  ss << "Line(" << std::get<0>(args) << ", " << std::get<1>(args) << ", " << std::get<2>(args) << ")";
  return ss.str();
}

std::string Line::PointAndVectorRepr() const {
  // return (boost::format("Line(%1%, %2%)") % GetPoint() %
  // GetDirectingVector()).str();
  std::stringstream ss;
  ss << "Line(" << GetPoint() << ", " << GetDirectingVector() << ")";
  return ss.str();
}

std::string Line::ToString() const {
  return PolynomialRepr();
}

bool Line::Parallel(const Line& first, const Line& second) {
  if (first.IsUndefined() || second.IsUndefined()) {
    throw std::logic_error("Method 'Line::Parallel' for undefined lines is undefined.");
  }
  return VectorType::Parallel(first.GetDirectingVector(), second.GetDirectingVector());
}

template <class R>
void Line::InputAsPolynom(std::istream& stream) {
  R a;
  R b;
  R c;
  stream >> a >> b >> c;
  *this = Line(a, b, c);
}

void Line::InputAsPointAndVector(std::istream& stream) {
  SetPoint(InputResult<PointType>(stream));
  SetDirectingVector(InputResult<VectorType>(stream));
}

std::istream& operator>>(std::istream& stream, Line& line) {
  line.InputAsPolynom(stream);
  return stream;
}

}  // namespace geometry