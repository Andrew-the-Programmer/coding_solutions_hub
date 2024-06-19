// Copyright 2024 Andrew
#include <cstddef>
#include <iostream>
#include <vector>

template <class T>
struct Grid : public std::vector<std::vector<T>> {
 protected:
  using Base = std::vector<std::vector<int>>;
  using Base::Base;

public:
    Grid(size_t n, size_t m, const T& default_value = T()) : Base(n, std::vector<T>(m, default_value)) {}

    const T& at(std::pair<size_t, size_t> pos) const {
        return this->at(pos.first).at(pos.second);
    }
}

void Solution(const Grid& grid, size_t n, size_t m) {
    Grid<bool> visited(n, m, false);
    visited[0][0] = true;

    std::queue<std::pair<size_t, size_t>> queue{start};
    while (!queue.empty()) {
      auto cur = queue.front();
      queue.pop_front();
      for (auto&& neighbor : this->Neighbors(cur)) {
        if (visited[neighbor]) {
          continue;
        }
        visited[neighbor] = true;
        if (!func(cur, neighbor)) {
          return;
        }
        queue.emplace_back(neighbor);
      }
    }
  }
}

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;

  Grid<int> manhattan(n, m);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      std::cin >> manhattan[i][j];
    }
  }

  Solution(manhattan, n, m);
}
