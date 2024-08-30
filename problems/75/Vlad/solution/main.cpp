#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<int> tin, low;
std::vector<bool> visited;
int timer = 0;
std::vector<bool> is_articulation_point;

void Dfs(int u, int parent) {
  visited[u] = true;
  tin[u] = low[u] = timer++;
  int children = 0;
  for (int v : graph[u]) {
    if (v == parent) {
      continue;
    }
    if (!visited[v]) {
      children++;
      Dfs(v, u);
      low[u] = std::min(low[u], low[v]);
      if (parent != -1 && low[v] >= tin[u]) {
        is_articulation_point[u] = true;
      }
    } else {
      low[u] = std::min(low[u], tin[v]);
    }
  }
  if (parent == -1 && children > 1) {
    is_articulation_point[u] = true;
  }
}

int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  graph.resize(n);
  tin.assign(n, -1);
  low.assign(n, -1);
  visited.assign(n, false);
  is_articulation_point.assign(n, false);
  for (int i = 0; i < m; i++) {
    int u{};
    int v{};
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    graph[v - 1].push_back(u - 1);
  }
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      Dfs(i, -1);
    }
  }
  int articulation_points_count = 0;
  for (int i = 0; i < n; i++) {
    if (is_articulation_point[i]) {
      articulation_points_count++;
    }
  }
  std::cout << articulation_points_count << std::endl;
  for (int i = 0; i < n; i++) {
    if (is_articulation_point[i]) {
      std::cout << i + 1 << std::endl;
    }
  }
  return 0;
}
