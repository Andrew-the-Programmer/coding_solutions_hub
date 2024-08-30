#include <iostream>
#include <queue>
#include <vector>

std::vector<int64_t> Deikstra(int64_t vertice, std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph) {
  std::vector<int64_t> distance(graph.size(), 2'009'000'999);
  std::vector<bool> visited(graph.size(), false);
  distance[vertice] = 0;

  std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                      std::greater<std::pair<int64_t, int64_t>>>
      queue;
  queue.emplace(0, vertice);

  while (!queue.empty()) {
    int64_t current = queue.top().second;
    queue.pop();

    if (visited[current]) {
      continue;
    }
    visited[current] = true;

    for (const auto& node : graph[current]) {
      int64_t v = node.first;
      int64_t weight = node.second;

      if (distance[current] + weight < distance[v]) {
        distance[v] = distance[current] + weight;
        queue.emplace(distance[v], v);
      }
    }
  }

  return distance;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int64_t n{};
  int64_t s{};
  int64_t t{};
  std::cin >> n >> s >> t;
  s--;
  t--;
  std::vector<std::vector<std::pair<int64_t, int64_t>>> graph(n);

  for (int64_t i{}; i < n; i++) {
    for (int64_t j{}; j < n; j++) {
      int64_t w{};
      std::cin >> w;
      if (i == j) {
        continue;
      }
      if (w == -1) {
        continue;
      }
      graph[i].emplace_back(j, w);
    }
  }

  auto distances = Deikstra(s, graph);
  if (distances[t] == 2'009'000'999) {
    std::cout << -1;
    return 0;
  }
  std::cout << distances[t];
}