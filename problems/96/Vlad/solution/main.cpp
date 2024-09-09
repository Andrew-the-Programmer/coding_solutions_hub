#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

constexpr int64_t kMaximum = 2009000999;

std::vector<int64_t> Dijkstra(int64_t vertice, std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph) {
  std::vector<int64_t> distance(graph.size(), kMaximum);
  std::vector<bool> visited(graph.size(), false);
  distance[vertice] = 0;
  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.emplace(0, vertice);
  while (!queue.empty()) {
    const int64_t num = queue.top().second;
    queue.pop();
    if (visited[num]) {
      continue;
    }
    visited[num] = true;
    for (auto& [fst, snd] : graph[num]) {
      int64_t v = fst;
      if (const int64_t weight = snd; distance[num] + weight < distance[v]) {
        distance[v] = distance[num] + weight;
        queue.emplace(distance[v], v);
      }
    }
  }
  return distance;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t k{};
  std::cin >> k;
  for (int64_t i = 0; i < k; i++) {
    int64_t n{};
    int64_t m{};
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int64_t, int64_t>>> graph(n);
    for (int64_t j = 0; j < m; ++j) {
      int64_t a{};
      int64_t b{};
      int64_t t{};
      std::cin >> a >> b >> t;
      graph[a].emplace_back(b, t);
      graph[b].emplace_back(a, t);
    }
    int64_t s = 0;
    std::cin >> s;
    auto distance = Dijkstra(s, graph);
    for (const int64_t dist : distance) {
      std::cout << dist << ' ';
    }
  }
}
