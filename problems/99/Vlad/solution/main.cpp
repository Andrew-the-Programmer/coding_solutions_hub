#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

std::vector<int64_t> FordBelman(int64_t vertice, const std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph) {
  size_t n = graph.size();
  std::vector<int64_t> d(n, 2'009'000'999);
  d[vertice] = 0;

  for (int64_t i = 0; i < static_cast<int64_t>(n) - 1; i++) {
    for (int64_t j = 0; j < static_cast<int64_t>(n); j++) {
      for (const auto& node : graph[j]) {
        int64_t v = node.first;
        int64_t weight = node.second;
        if (d[j] != 2'009'000'999 && d[j] + weight < d[v]) {
          d[v] = d[j] + weight;
        }
      }
    }
  }
  return d;
}

std::vector<int64_t> Dijkstra(int64_t vertice, const std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph) {
  std::vector<int64_t> d(graph.size(), 2'009'000'999);
  std::vector<bool> visited(graph.size(), false);
  d[vertice] = 0;

  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.emplace(0, vertice);

  while (!queue.empty()) {
    int64_t num = queue.top().second;
    queue.pop();

    if (visited[num]) {
      continue;
    }
    visited[num] = true;

    for (const auto& node : graph[num]) {
      int64_t vertex = node.first;
      int64_t weight = node.second;

      if (d[num] + weight < d[vertex]) {
        d[vertex] = d[num] + weight;
        queue.emplace(d[vertex], vertex);
      }
    }
  }

  return d;
}

std::vector<std::vector<int64_t>> Johnson(std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph) {
  size_t n = graph.size();
  std::vector<std::vector<std::pair<int64_t, int64_t>>> new_graph = graph;
  for (int64_t i = 0; i < static_cast<int64_t>(n); ++i) {
    new_graph.push_back({{i, 0}});
  }
  std::vector<int64_t> h = FordBelman(n, new_graph);  // NOLINT
  std::vector<std::vector<std::pair<int64_t, int64_t>>> modified_graph(n);
  for (int64_t u = 0; u < static_cast<int64_t>(n); ++u) {
    for (const auto& node : graph[u]) {
      int64_t v = node.first;
      int64_t weight = node.second;
      modified_graph[u].emplace_back(v, weight + h[u] - h[v]);
    }
  }
  std::vector<std::vector<int64_t>> d(n, std::vector<int64_t>(n, 2'009'000'999));
  for (int64_t u = 0; u < static_cast<int64_t>(n); ++u) {
    d[u] = Dijkstra(u, modified_graph);
  }
  for (int64_t u = 0; u < static_cast<int64_t>(n); ++u) {
    for (int64_t v = 0; v < static_cast<int64_t>(n); ++v) {
      if (d[u][v] < 2'009'000'999) {
        d[u][v] += h[v] - h[u];
      }
    }
  }
  return d;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int64_t n{};
  int64_t m{};
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int64_t, int64_t>>> graph(n);
  for (int64_t i = 0; i < m; i++) {
    int64_t a{};
    int64_t b{};
    int64_t w{};
    std::cin >> a >> b >> w;
    graph[a].emplace_back(b, w);
  }
  std::vector<std::vector<int64_t>> d = Johnson(graph);
  int64_t max = std::numeric_limits<int64_t>::min();
  for (int64_t i{}; i < n; i++) {
    for (int64_t j{}; j < n; j++) {
      if (d[i][j] < 2'009'000'999) {
        max = std::max(max, d[i][j]);
      }
    }
  }
  std::cout << max;
  return 0;
}
