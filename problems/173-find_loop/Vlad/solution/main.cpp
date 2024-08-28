#include <iostream>
#include <queue>
#include <vector>
#include <set>

enum class Color { white, grey, black };

bool DFS(std::vector<std::set<int>> &graph, std::vector<Color> &colors, std::vector<int> &cycle, int cur, int &f) {
  cycle.push_back(cur);
  colors[cur - 1] = Color::grey;
  for (auto &i : graph[cur - 1]) {
    if (colors[i - 1] == Color::grey) {
      f = i;
      return true;
    }
    if (colors[i - 1] == Color::white) {
      if (DFS(graph, colors, cycle, i, f)) {
        return true;
      }
    }
  }
  colors[cur - 1] = Color::black;
  cycle.pop_back();
  return false;
}

int main() {
  int n{};
  size_t m{};
  int a{};
  int b{};
  bool flag = false;
  std::cin >> n >> m;
  std::vector<std::set<int>> graph(n);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> a >> b;
    graph[a - 1].emplace(b);
  }
  std::vector<Color> colors{static_cast<size_t>(n), Color::white};
  std::vector<int> cycle;
  int f = n;
  for (int i = 1; i < n + 1; ++i) {
    if (colors[i - 1] == Color::black) {
      continue;
    }
    auto is_cycle = DFS(graph, colors, cycle, i, f);
    if (is_cycle) {
      std::cout << "YES\n";
      for (auto &j : cycle) {
        if (j == f) {
          flag = true;
        }
        if (flag) {
          std::cout << j << " ";
        }
      }
      return 0;
    }
  }
  std::cout << "NO";
  return 0;
}