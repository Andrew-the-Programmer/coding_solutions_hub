#include <iostream>
#include <vector>
#include <deque>
#include <set>

std::vector<int> BFS(std::vector<std::vector<std::pair<int, int>>> &graph, int s) {
  int inf = 10000000;
  std::vector<int> dist(graph.size(), inf);
  std::deque<int> deque;
  deque.push_back(s);
  dist[s - 1] = 0;
  while (!deque.empty()) {
    int v = deque.front();
    deque.pop_front();
    for (auto &i : graph[v - 1]) {
      if (dist[i.first - 1] > dist[v - 1] + i.second) {
        dist[i.first - 1] = dist[v - 1] + i.second;
        if (i.second == 0) {
          deque.push_front(i.first);
        } else {
          deque.push_back(i.first);
        }
      }
    }
  }
  return dist;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  size_t n{};
  size_t m{};
  int s{};
  int f{};
  int a{};
  int b{};
  int k{};
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> a >> b;
    graph[a - 1].emplace_back(b, 0);
    graph[b - 1].emplace_back(a, 1);
  }
  std::cin >> k;
  for (int j = 0; j < k; ++j) {
    std::cin >> s >> f;
    std::vector<int> lens = BFS(graph, s);
    if (lens[f - 1] == 10000000) {
      std::cout << -1 << "\n";
    } else {
      std::cout << lens[f - 1] << "\n";
    }
  }
  return 0;
}
