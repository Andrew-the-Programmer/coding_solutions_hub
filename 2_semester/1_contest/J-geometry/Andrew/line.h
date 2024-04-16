#pragma once

#include "ishape.h"
#include "point.h"
#include "vector.h"
#include "ray.h"
#include "segment.h"

namespace geometry {

struct Ray;

struct Segment;

struct Line : public IShape {
  using PointType = Point;
  using VectorType = Vector;

  PointType point = PointType();
  VectorType directing_vector = VectorType();

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

  explicit Line(const Ray&);

  explicit Line(const Segment&);

  Line& operator=(const Line&) = default;

  bool IsUndefined() const;

  bool IsDefined() const;

  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  const VectorType& GetDirectingVector() const;

  VectorType& GetDirectingVector();

	void SetDirectingVector(const VectorType&);

  const PointType& GetPoint() const;

  PointType& GetPoint();

	void SetPoint(const PointType&);

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

}  // namespace geometry
