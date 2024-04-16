//
// Created by metaphys on 25.03.24.
//

#ifndef ALGORITMS1_SEGMENT_H
#define ALGORITMS1_SEGMENT_H

#include "ishape.h"
#include "point.h"

namespace geometry {
  class Segment : public IShape {
  public:
    Point a_{};
    Point b_{};

    int i;

    Segment() = default;

    Segment(const Point &a, const Point &b) : a_{a}, b_{b} {
      a_.x_ = a.x_;
      a_.y_ = a.y_;
      b_.x_ = b.x_;
      b_.y_ = b.y_;
    }


    bool ContainsPoint(const Point &) const override;

    void Move(const Vector &) override;

    bool CrossesSegment(const Segment &) const override;

    std::unique_ptr<IShape> Clone() const override;

    std::string ToString() override;

  };
}
#endif //ALGORITMS1_SEGMENT_H
