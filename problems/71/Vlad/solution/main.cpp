// Copyright 2024 Vlad

#include <iostream>
#include <vector>

void DFS(std::vector<std::vector<int>> &graph, std::vector<int> &colors, int cur, int color) {
  colors[cur] = color;
  for (auto &i : graph[cur]) {
    if (colors[i] == 0) {
      DFS(graph, colors, i, color);
    }
  }
}

int main() {
  int n{};
  int m{};
  int a{};
  int b{};
  int c{};
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    a--;
    b--;
    graph[a].emplace_back(b);
    graph[b].emplace_back(a);
  }
  std::vector<int> colors(n, 0);
  for (int i = 0; i < n; ++i) {
    if (colors[i] != 0) {
      continue;
    }
    DFS(graph, colors, i, i + 1);
    c++;
  }

  std::vector<std::vector<int>> array(n);
  for (int i = 0; i < n; ++i) {
    array[colors[i] - 1].emplace_back(i);
  }
  std::cout << c << "\n";
  for (auto &i : array) {
    if (i.empty()) {
      continue;
    }
    std::cout << i.size() << "\n";
    for (auto &j : i) {
      std::cout << j + 1 << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
