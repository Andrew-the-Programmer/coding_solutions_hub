// Copyright 2024 Andrew

#include <iostream>
#include <vector>
#include <cmath>

struct Point {
  int x, y;
};

using Polygon = std::vector<Point>;

Point GetPolygonPoint(const Polygon& polygon, size_t i) {
  return polygon[std::fmod(i, polygon.size())];
}

bool IsInsidePolygon(const Polygon& polygon, const Point& point) {
  size_t size = polygon.size();
  bool inside = false;
  for (size_t i = 0; i < size; ++i) {
    auto cur = GetPolygonPoint(polygon, i);
    auto next = GetPolygonPoint(polygon, i + 1);
    auto prev = GetPolygonPoint(polygon, i - 1);
    if (cur.y == point.y && cur.x == point.x) {
      // Cur == point
      return true;
    }
    if (cur.y == point.y && cur.x > point.x) {
      // Ray cross cur
      if (next.y > point.y) {
        inside = !inside;
      }
      if (prev.y > point.y) {
        inside = !inside;
      }
      continue;
    }
    bool cross_segment = ((cur.y > point.y) != (next.y > point.y));
    if (cross_segment && (point.x < (next.x - cur.x) * (point.y - cur.y) / (next.y - cur.y) + cur.x)) {
      inside = !inside;
    }
  }
  return inside;
}

Point MakePoint() {
  Point point;
  std::cin >> point.x >> point.y;
  return point;
}

void InputPolygon(Polygon& polygon, size_t size) {
  polygon.resize(size);
  for (size_t i = 0; i < size; i++) {
    std::cin >> polygon[i].x >> polygon[i].y;
  }
}

Polygon MakePolygon(size_t n) {
  Polygon polygon;
  InputPolygon(polygon, n);
  return polygon;
}

void Solution(const Polygon& polygon, const Point& point) {
  std::cout << (IsInsidePolygon(polygon, point) ? "YES" : "NO") << std::endl;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  auto point = MakePoint();
  auto polygon = MakePolygon(n);
  Solution(polygon, point);
  return 0;
}
