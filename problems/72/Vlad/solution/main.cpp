#include <iostream>
#include <queue>
#include <vector>

std::vector<int> TopologicalSort(const std::vector<std::vector<int>> &graph) {
  size_t n = graph.size();
  std::vector<int> in_degree(n, 0);
  std::vector<int> result;
  for (size_t i = 0; i < n; i++) {
    for (int neighbor : graph[i]) {
      in_degree[neighbor]++;
    }
  }
  std::queue<int> q;
  for (size_t i = 0; i < n; i++) {
    if (in_degree[i] == 0) {
      q.push(static_cast<int>(i));
    }
  }
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    result.push_back(node);
    for (int neighbor : graph[node]) {
      if (--in_degree[neighbor] == 0) {
        q.push(neighbor);
      }
    }
  }
  if (result.size() != n) {
    return {-1};
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int n{};
  int m{};
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < m; i++) {
    int u{};
    int v{};
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
  }
  std::vector<int> sorted_nodes = TopologicalSort(graph);
  if (sorted_nodes[0] == -1) {
    std::cout << -1 << std::endl;
  } else {
    for (int node : sorted_nodes) {
      std::cout << node + 1 << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
