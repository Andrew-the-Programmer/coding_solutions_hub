#include <iostream>
#include <vector>
#include <queue>

bool Isbipartite(const std::vector<std::vector<int>> &graph) {
  int n = static_cast<int>(graph.size());
  std::vector<int> colors(n, -1);
  for (int start = 0; start < n; ++start) {
    if (colors[start] != -1) {
      continue;
    }
    std::queue<int> q;
    q.push(start);
    colors[start] = 0;
    while (!q.empty()) {
      int node = q.front();
      q.pop();
      for (int neighbor : graph[node]) {
        if (colors[neighbor] == -1) {
          colors[neighbor] = 1 - colors[node];
          q.push(neighbor);
        } else if (colors[neighbor] == colors[node]) {
          return false;
        }
      }
    }
  }
  return true;
}
int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < m; ++i) {
    int a{};
    int b{};
    std::cin >> a >> b;
    a--;
    b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  if (Isbipartite(graph)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}