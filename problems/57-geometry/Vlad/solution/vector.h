#ifndef ALGORITMS1_VECTOR_H
#define ALGORITMS1_VECTOR_H
#include "point.h"
namespace geometry {
class Vector {
 public:
  int x_{};
  int y_{};

  Vector(int x, int y) : x_{x}, y_{y} {};

  Vector() = default;

  Vector(Point a, Point b) : x_{b.x_ - a.x_}, y_{b.y_ - a.y_} {
  }

  friend Vector operator-(Vector a);

  friend Vector operator+(Vector a, Vector b);

  friend Vector operator-(Vector a, Vector b);

  friend Vector operator*(Vector a, int p);

  friend Vector operator/(Vector a, int p);

  friend bool operator==(Vector a, Vector b);

  friend Vector& operator+=(Vector &a, Vector b);

  friend Vector &operator-=(Vector &a, Vector b);

  friend Vector &operator*=(Vector &a, int p);

  friend Vector &operator/=(Vector &a, int p);
};
}  // namespace geometry
#endif  // ALGORITMS1_VECTOR_H
