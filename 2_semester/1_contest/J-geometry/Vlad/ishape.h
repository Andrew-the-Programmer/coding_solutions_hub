//
// Created by metaphys on 25.03.24.
//

#ifndef ALGORITMS1_ISHAPE_H
#define ALGORITMS1_ISHAPE_H

#include <string>
#include <memory>

namespace geometry {
class Point;

class Vector;

class Segment;

class IShape {
 public:
  virtual void Move(const Vector&) = 0;

  virtual bool ContainsPoint(const Point&) const = 0;

  virtual bool CrossesSegment(const Segment &) const {
    return true;
  };

  virtual std::unique_ptr<IShape> Clone() const {
    return nullptr;
  };

  virtual std::string ToString() const = 0;

  virtual ~IShape() = default;
};

}  // namespace geometry

#endif
