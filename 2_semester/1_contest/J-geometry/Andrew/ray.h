#pragma once

#include "ishape.h"
#include "point.h"
#include "vector.h"
#include "line.h"
#include "segment.h"

namespace geometry {

struct Line;

struct Ray : public IShape {
  using PointType = Point;
  using VectorType = Vector;

  PointType start_point = PointType();
  VectorType directing_vector = VectorType();

  Ray() = default;

  Ray(const PointType& start_point, const VectorType& directing_vector);

  Ray(const PointType& start_point, const PointType& end_point);

  explicit Ray(const Segment&);

  explicit operator Line();

	bool IsUndefined() const;

  bool IsDefined() const;

  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  bool PointsTo(const PointType&) const;

  friend std::istream& operator>>(std::istream&, Ray&);
};

}  // namespace geometry
