//
// Created by metaphys on 25.03.24.
//

#ifndef ALGORITMS1_RAY_H
#define ALGORITMS1_RAY_H

#include "ishape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
  class Ray : public IShape {
    Point a_;
    Vector b_;
  public:
    Ray() {
      a_.x_ = 0;
      a_.y_ = 0;
      b_.x_ = 0;
      b_.y_ = 0;
    }

    Ray(const Point &a, const Point &b) {
      a_.x_ = a.x_;
      a_.y_ = a.y_;
      b_.x_ = b.x_ - a.x_;
      b_.y_ = b.y_ - a.y_;
    }

    void Move(const Vector &) override;

    bool ContainsPoint(const Point &) const override;

    bool CrossesSegment(const Segment &) const override;

    std::unique_ptr<IShape> Clone() const override;

    std::string ToString() override;

  };
}
#endif //ALGORITMS1_RAY_H
