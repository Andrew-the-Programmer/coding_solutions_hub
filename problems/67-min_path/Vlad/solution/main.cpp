#include <iostream>
#include <vector>
#include <queue>
#include <set>

std::vector<int> Djkstra(const std::vector<std::vector<std::pair<int, int>>> &graph, int s) {
  int inf = 100000;
  std::vector<int> dist(graph.size(), inf);
  dist[s - 1] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
  queue.emplace(0, s);
  std::pair<int, int> cur{};
  while (!queue.empty()) {
    cur = queue.top();
    queue.pop();
    for (auto &i : graph[cur.second - 1]) {
      if (dist[i.first - 1] > dist[cur.second - 1] + i.second) {
        dist[i.first - 1] = dist[cur.second - 1] + i.second;
        queue.emplace(dist[cur.second - 1] + i.second, i.first);
      }
    }
  }
  return dist;
};

int main() {
  size_t n{};
  size_t m{};
  int s{};
  int f{};
  int a{};
  int b{};
  int t{};
  std::cin >> n >> m >> s >> f;
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> a >> b >> t;
    graph[a - 1].emplace_back(b, t);
  }
  std::vector<int> lens = Djkstra(graph, s);
  if (lens[f - 1] == 100000) {
    std::cout << -1;
  } else {
    std::cout << lens[f - 1];
  }
  return 0;
}