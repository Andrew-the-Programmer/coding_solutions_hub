//
// Created by metaphys on 25.03.24.
//

#ifndef ALGORITMS1_POINT_H
#define ALGORITMS1_POINT_H

#include "ishape.h"

namespace geometry {

class Vector;

class Point : public IShape {
 public:
  int x_{};
  int y_{};

  Point(int x, int y) : x_{x}, y_{y} {};

  Point(Point &&other) noexcept : x_{other.x_}, y_{other.y_} {
    other.x_ = 0;
    other.y_ = 0;
  }

  Point(const Point &other) : x_{other.x_}, y_{other.y_} {
  }

  Point() = default;

  void Move(const Vector &) override;

  bool ContainsPoint(const Point &) const override;

  bool CrossesSegment(const Segment &) const override;

  std::unique_ptr<IShape> Clone() const override;

  std::string ToString() const override;

  friend Vector operator-(Point, Point);
};
}  // namespace geometry
#endif  // ALGORITMS1_POINT_H
