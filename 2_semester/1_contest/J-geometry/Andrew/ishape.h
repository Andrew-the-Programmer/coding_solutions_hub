#pragma once

// Andrew was here :3

#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <sstream>

#include "other.h"

using namespace std::literals;

namespace geometry {

using T = int64_t;

struct Point;

struct Vector;

struct Segment;

struct IShape {
  virtual ~IShape() = default;

  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual std::shared_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;

  friend std::ostream& operator<<(std::ostream& stream, const IShape& shape) {
    stream << shape.ToString();
    return stream;
  }
};

}  // namespace geometry