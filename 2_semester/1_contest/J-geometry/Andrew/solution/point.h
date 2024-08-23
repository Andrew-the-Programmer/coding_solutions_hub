#pragma once

#include "ishape.h"
#include "vector.h"
// #include "segment.h"

namespace geometry {

struct Segment;

struct Point : public IShape {
  T x;
  T y;

  Point() = default;

  Point(const T& x, const T& y);

  Point& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  Vector operator-(const Point&) const;

  bool operator==(const Point&) const;

  bool operator!=(const Point&) const;

  friend std::istream& operator>>(std::istream&, Point&);
};

T SquaredDistance(const Point&, const Point&);

double Distance(const Point&, const Point&);

}  // namespace geometry
