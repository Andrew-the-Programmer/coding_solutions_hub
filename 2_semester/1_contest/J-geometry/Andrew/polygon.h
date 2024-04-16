#pragma once

#include <vector>

#include "ishape.h"
#include "point.h"
#include "vector.h"
#include "ray.h"
#include "segment.h"

namespace geometry {

struct Polygon : public IShape {
 public:
  using PointType = Point;
  using VectorType = Vector;

  std::vector<PointType> points;

  Polygon() = default;

  Polygon(const std::initializer_list<PointType>&);

  explicit Polygon(const std::vector<PointType>&);

  auto Segments() const;

  IShape& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Polygon&);
};

}  // namespace geometry
