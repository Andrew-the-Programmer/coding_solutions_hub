#pragma once

#include "ishape.h"
#include "point.h"
#include "vector.h"
#include "line.h"
#include "ray.h"

namespace geometry {

struct Line;

struct Segment : public IShape {
  using PointType = Point;
  using VectorType = Vector;
  using LineType = Line;

  PointType first_point = PointType();
  PointType second_point = PointType();

  Segment() = default;

  Segment(const PointType&, const PointType&);

  auto GetDirectingVector() const;

  auto SquaredLength() const;

  auto Length() const;

	bool IsPoint() const;

 protected:
  bool ContainsPointOnSameLine(const PointType&) const;

  static bool OverlapOnSameLine(const Segment&, const Segment&);

 public:
  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Segment&);
};

double Distance(const Point&, const Segment&);

}  // namespace geometry
