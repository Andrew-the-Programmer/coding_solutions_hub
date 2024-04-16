//
// Created by metaphys on 25.03.24.
//

#ifndef ALGORITMS1_CIRCLE_H
#define ALGORITMS1_CIRCLE_H

#include "ishape.h"
#include "point.h"

namespace geometry {
class Circle : public IShape {
    Point c_;
    int r_;

  public:
    Circle() {
      c_.x_ = 0;
      c_.y_ = 0;
      r_ = 0;
    }

    Circle(const Point &c, int r) {
      c_.x_ = c.x_;
      c_.y_ = c.y_;
      r_ = r;
    }

    void Move(const Vector &) override;

    bool ContainsPoint(const Point &) const override;

    bool CrossesSegment(const Segment &) const override;

    std::unique_ptr<IShape> Clone() const override;

    std::string ToString() override;
  };
}
#endif //ALGORITMS1_CIRCLE_H
