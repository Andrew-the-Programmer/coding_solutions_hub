//
// Created by metaphys on 25.03.24.
//

#ifndef ALGORITMS1_LINE_H
#define ALGORITMS1_LINE_H

#include "vector.h"
#include "ishape.h"

int A(int y1, int y2);

int B(int x1, int x2);

int C(int x1, int y1, int x2, int y2);

namespace geometry {
  class Line : public IShape {
    int a_;
    int b_;
    int c_;

  public:
    Line() : a_{0}, b_{0}, c_{0} {};

    Line(Point a, Point b) : a_{A(a.y_, b.y_)}, b_{B(a.x_, b.x_)}, c_{C(a.x_, a.y_, b.x_, b.y_)} {};

    void Move(const Vector &) override;

    bool ContainsPoint(const Point &) const override;

    bool CrossesSegment(const Segment &) const override;

    std::unique_ptr<IShape> Clone() const override;

    std::string ToString() override;
  };
}
#endif //ALGORITMS1_LINE_H
