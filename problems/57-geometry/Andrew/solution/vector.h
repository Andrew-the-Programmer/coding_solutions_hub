#pragma once

#include "point.h"

namespace geometry {

struct Vector {
  T x = 0;
  T y = 0;

  using PointType = Point;

  Vector() = default;

  Vector(const T& x, const T& y);

  Vector(const PointType&);  // NOLINT

  Vector(const PointType& begin, const PointType& end);

  operator Point() const;  // NOLINT

  bool IsZero() const;

  T SquaredLength() const;

  double Length() const;

  static T ScalarProduct(const Vector&, const Vector&);

  static T SignedArea(const Vector&, const Vector&);

  static bool Parallel(const Vector&, const Vector&);

  bool PointsTo(const PointType&) const;

  static double Sin(const Vector&, const Vector&);

  T VectorProduct(const Vector&) const;

  Vector& operator+=(const Vector&);

  Vector operator+(const Vector&) const;

  Vector& operator-=(const Vector&);

  Vector operator-(const Vector&) const;

  Vector operator-() const;

  bool operator==(const Vector&) const;

  std::string ToString() const;

  friend std::ostream& operator<<(std::ostream&, const Vector&);

  friend std::istream& operator>>(std::istream&, Vector&);
};

}  // namespace geometry
