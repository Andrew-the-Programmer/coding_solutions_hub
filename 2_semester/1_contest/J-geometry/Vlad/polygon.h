//
// Created by metaphys on 25.03.24.
//

#ifndef ALGORITMS1_POLYGON_H
#define ALGORITMS1_POLYGON_H

#include "point.h"
#include "ishape.h"
#include <vector>

namespace geometry {
  class Polygon : public IShape {
  public:
    size_t n_{};
    std::vector<int> arrx_{};
    std::vector<int> arry_{};
  public:
    Polygon() {
      n_ = 0;
    }

    explicit Polygon(std::vector<Point> &arr) : n_(arr.size()), arrx_(arr.size()), arry_(arr.size()) {
      for (size_t i = 0; i < n_; ++i) {
        arrx_[i] = arr[i].x_;
        arry_[i] = arr[i].y_;
      }
    }

    explicit Polygon(std::vector<Point> &&arr) : n_(arr.size()), arrx_(std::move(arr.size())),
                                                 arry_(std::move(arr.size())) {
      for (size_t i = 0; i < n_; ++i) {
        arrx_[i] = std::move(arr[i].x_);
        arry_[i] = std::move(arr[i].y_);
      }
    }

    void Move(const Vector &) override;

    bool ContainsPoint(const Point &) const override;

    bool CrossesSegment(const Segment &) const override;

    std::unique_ptr<IShape> Clone() const override;

    std::string ToString() override;
  };
}
#endif //ALGORITMS1_POLYGON_H
