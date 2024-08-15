// Copyright 2024 Andrew

#include <iostream>
#include <optional>
#include <vector>
#include <queue>

template <class T>
struct Point {
  T x{};
  T y{};
  Point(T x, T y) : x(x), y(y) {
  }
  auto operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
  }
};

template <class T>
struct GridT : std::vector<std::vector<T>> {
  using Base = std::vector<std::vector<T>>;
  using Base::Base;

  GridT(size_t n, size_t m) : Base(n, std::vector<T>(m)) {
  }

  template <class U>
  auto&& At(const Point<U>& point) {
    return this->at(point.y)[point.x];
  }

  template <class U>
  bool Contains(const Point<U>& point) const {
    if (point.x < 0 || point.y < 0) {
      return false;
    }
    return static_cast<size_t>(point.y) < this->size() && static_cast<size_t>(point.x) < this->at(point.y).size();
  }
};

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;

  // 0 - no house, 1 - house
  GridT<int> grid(n, m);
  GridT<std::optional<size_t>> distances(n, m);

  using P = Point<int>;

  std::queue<P> q;

  for (size_t y = 0; y < n; ++y) {
    for (size_t x = 0; x < m; ++x) {
      Point<size_t> cur(x, y);
      std::cin >> grid.At(cur);
      if (grid.At(cur) == 1) {
        // Has house
        q.emplace(x, y);
        distances.At(cur) = 0;
      }
    }
  }

  while (!q.empty()) {
    auto current = q.front();
    q.pop();

    // Iterate through current neighbors
    for (int dy = -1; dy <= 1; ++dy) {
      for (int dx = -1; dx <= 1; ++dx) {
        if (std::abs(dx) + std::abs(dy) != 1) {
          // Diagonal neighbors
          continue;
        }
        P diff(dx, dy);
        auto next = current + diff;
        if (distances.Contains(next) && !distances.At(next).has_value()) {
          distances.At(next) = distances.At(current).value() + 1;
          q.emplace(next);
        }
      }
    }
  }

  for (size_t y = 0; y < n; ++y) {
    for (size_t x = 0; x < m; ++x) {
      Point<size_t> cur(x, y);
      std::cout << distances.At(cur).value() << " ";
    }
    std::cout << "\n";
  }
}
