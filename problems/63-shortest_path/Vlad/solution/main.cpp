#include <vector>
#include <iostream>
#include <queue>
#include <set>

std::pair<std::vector<int>, std::vector<int>> BFS(std::vector<std::set<int>> graph, int s) {
  int inf = 10000000;
  std::vector<int> dist(graph.size(), inf);
  std::vector<int> parent(graph.size(), 0);
  std::queue<int> queue;
  queue.push(s);
  dist[s - 1] = 0;
  int v = 0;
  while (!queue.empty()) {
    v = queue.front();
    queue.pop();
    for (auto &i : graph[v - 1]) {
      if (dist[i - 1] == inf) {
        dist[i - 1] = dist[v - 1] + 1;
        parent[i - 1] = v;
        queue.push(i);
      }
    }
  }
  return {dist, parent};
}

int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  std::vector<std::set<int>> graph(n);
  int a{};
  int b{};
  int a0{};
  int b0{};
  std::cin >> a0 >> b0;
  if (a0 == b0) {
    std::cout << 0 << "\n" << a0;
    return 0;
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    graph[a - 1].emplace(b);
    graph[b - 1].emplace(a);
  }
  auto pair = BFS(graph, a0);
  if (pair.first[b0 - 1] == 10000000) {
    std::cout << -1;
    return 0;
  }
  int len = pair.first[b0 - 1];
  std::cout << len << "\n";
  auto ans = new int[len + 1];
  ans[0] = b0;
  int j = 1;
  while (pair.second[b0 - 1] != a0) {
    ans[j++] = (pair.second[b0 - 1]);
    b0 = pair.second[b0 - 1];
  }
  ans[len] = a0;
  for (int i = len; i >= 0; --i) {
    std::cout << ans[i] << " ";
  }
  delete[] ans;
  return 0;
}