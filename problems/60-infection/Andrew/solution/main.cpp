// Copyright 2024 Andrew

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct Point {
  int x, y;
};

using Polygon = std::vector<Point>;

bool IsInsidePolygon(const Polygon& polygon, const Point& point) {
  size_t size = polygon.size();
  bool inside = false;
  for (size_t i = 0, j = size - 1; i < size; j = i++) {
    auto pi = polygon[i];
    auto pj = polygon[j];
    if (((pi.y > point.y) != (pj.y > point.y)) && (point.x < (pj.x - pi.x) * (point.y - pi.y) / (pj.y - pi.y) + pi.x)) {
      inside = !inside;
    }
  }
  return inside;
}

void InputPolygon(Polygon& polygon, size_t size) {
  polygon.resize(size);
  for (size_t i = 0; i < size; i++) {
    std::cin >> polygon[i].x >> polygon[i].y;
  }
}

Polygon MakePolygon() {
  size_t n;
  std::cin >> n;
  Polygon polygon;
  InputPolygon(polygon, n);
  return polygon;
}

void OutputLocations(const std::vector<Polygon>& zones, const Polygon& points) {
  for (auto&& point : points) {
    size_t zone_index = 0;
    for (int i = 0; i < zones.size(); i++) {
      if (IsInsidePolygon(zones[i], point)) {
        zone_index = i;
        break;
      }
    }
    std::cout << zone_index << std::endl;
  }
}

void Solution(const Polygon& points, const Polygon& target_points) {
  std::vector<Polygon> zones;
  std::set<Point> used_points;
  std::set<Point> unique_points(points.begin(), points.end());
  Polygon hull;
  Polygon next_hull;
  while (points.size() > 2) {
    // Get rid of duplicate points
    std::set<Point> unique_points(points.begin(), points.end());
    Polygon hull(unique_points.begin(), unique_points.end());

    // Remove points inside the hull
    for (auto&& point : points) {
      if (IsInsidePolygon(hull, point)) {
        unique_points.erase(point);
      }
    }

    // Add hull to zones
    zones.push_back(hull);
  }

  OutputLocations(zones, target_points);
}

int main() {
  auto points = MakePolygon();
  auto target_points = MakePolygon();

  return 0;
}
