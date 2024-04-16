#pragma once

#include "ishape.h"
#include "point.h"
#include "vector.h"
#include "ray.h"
#include "segment.h"

namespace geometry {

struct Circle : public IShape {
 public:
  using RadiusType = T;
  using PointType = Point;
  using VectorType = Vector;

  RadiusType radius = 0;
  PointType center = PointType();

  Circle() = default;

  Circle(const RadiusType&, const PointType&);

  Circle(const PointType&, const RadiusType&);

  Circle(const Circle&) = default;

 protected:
  template <typename Cmp>
  bool CompareDistanceToPointAndRadius(const PointType&, const Cmp& cmp = Cmp()) const;

 public:
  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

	bool StrictlyContainsPoint(const Point&) const;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Circle&);
};

}  // namespace geometry
