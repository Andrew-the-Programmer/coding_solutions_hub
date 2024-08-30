#include <iostream>
#include <vector>
#include <queue>
struct Point {
  int x{};
  int y{};
  Point(int x, int y) : x(x), y(y) {
  }
};
int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  std::vector<std::vector<int>> grid(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> grid[i][j];
    }
  }
  std::queue<Point> q;
  std::vector<std::vector<int>> distances(n, std::vector<int>(m, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 1) {
        q.emplace(i, j);
        distances[i][j] = 0;
      }
    }
  }
  while (!q.empty()) {
    Point current = q.front();
    q.pop();
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (abs(dx) + abs(dy) != 1) {
          continue;
        }
        int nx = current.x + dx;
        int ny = current.y + dy;
        if (0 <= nx && nx < n && 0 <= ny && ny < m && distances[nx][ny] == -1) {
          distances[nx][ny] = distances[current.x][current.y] + 1;
          q.emplace(nx, ny);
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << distances[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
