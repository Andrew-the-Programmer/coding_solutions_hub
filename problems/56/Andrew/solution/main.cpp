// Copyright (c) 2024 Andrew
// I-polygon_surface

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

template <class T, class IStream = std::istream>
T InputResult(IStream& istream = std::cin) {
  T value;
  istream >> value;
  return value;
}

template <class T>
void Input(std::vector<T>& vector, size_t size) {
  vector.reserve(size + vector.size());
  for (size_t i = 0; i < size; ++i) {
    vector.emplace_back(InputResult<T>(std::cin));
  }
}

template <class T>
struct Vector;

template <class T>
struct Point {
  using VectorType = Vector<T>;

  T x;
  T y;

  Point() = default;
  Point(const T& x, const T& y) : x(x), y(y) {
  }

  static constexpr Point Zero() {
    return {0, 0};
  }

  friend auto& operator>>(std::istream& stream, Point& point) {
    stream >> point.x >> point.y;
    return stream;
  }
};

template <class T>
struct Vector {
  using PointType = Point<T>;

  T x;
  T y;

  Vector() = default;
  Vector(const T& x, const T& y) : x(x), y(y) {
  }
  Vector(const PointType& point) : Vector(point.x, point.y) {  // NOLINT
  }
  Vector(const PointType& begin, const PointType& end) : Vector(end.x - begin.x, end.y - begin.y) {
  }

  explicit operator PointType() const {
    return {x, y};
  }

  auto Dot(const Vector& other) const {
    return x * other.x + y * other.y;
  }

  auto Cross(const Vector& other) const {
    return x * other.y - y * other.x;
  }
};

template <class T>
struct Polygon : std::vector<Point<T>> {
  using Base = std::vector<Point<T>>;

  using Base::Base;
  using typename Base::value_type;
  using VectorType = Vector<T>;
  using PointType = Point<T>;

  auto Surface() {
    auto n = this->size();
    int64_t surface = 0;
    for (size_t i = 0; i < n - 1; ++i) {
      surface += Vector<T>(this->at(i)).Cross(this->at(i + 1));
    }
    surface += Vector<T>(this->back()).Cross(this->front());
    surface = std::abs(surface);
    std::cout << surface / 2 << (surface % 2 == 0 ? ".0" : ".5");
  }
};

void Solution() {
  using T = int64_t;

  Polygon<T> polygon;
  Input(polygon, InputResult<size_t>());

  polygon.Surface();
}

int main() {
  std::cout << std::fixed << std::setprecision(1);
  Solution();
}
