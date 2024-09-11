#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

constexpr int kHigh = 2147483647;

bool DFS(int start, int end, std::vector<int>& parent, std::vector<std::vector<int>>& graph,
         std::vector<std::unordered_map<int, int>>& capacity) {
  std::vector<bool> visited(graph.size(), false);
  std::queue<int> queue;
  queue.push(start);
  visited[start] = true;
  parent[start] = -1;
  while (!queue.empty()) {
    int curr_vertex = queue.front();
    queue.pop();
    for (int v : graph[curr_vertex]) {
      if (visited[v]) {
        continue;
      }
      if (capacity[curr_vertex][v] <= 0) {
        continue;
      }
      if (v == end) {
        parent[v] = curr_vertex;
        return true;
      }
      queue.push(v);
      visited[v] = true;
      parent[v] = curr_vertex;
    }
  }
  return false;
}

int FF(int start, int end, std::vector<std::unordered_map<int, int>>& capacity, std::vector<std::vector<int>>& graph) {
  std::vector<int> parent(graph.size());
  int solution{};
  while (DFS(start, end, parent, graph, capacity)) {
    int curr_f = static_cast<int>(kHigh);
    for (int vertex = end; vertex != start; vertex = parent[vertex]) {
      curr_f = std::min(curr_f, capacity[parent[vertex]][vertex]);
    }
    for (int vertex = end; vertex != start; vertex = parent[vertex]) {
      capacity[parent[vertex]][vertex] -= curr_f;
      capacity[vertex][parent[vertex]] += curr_f;
    }
    solution += curr_f;
  }
  return solution;
}

int main() {
  int m{};
  int n{};
  std::cin >> n >> m;
  std::vector<std::unordered_map<int, int>> capacity(n);
  std::vector<std::vector<int>> graph(n);
  for (int i{}; i < m; i++) {
    int x{};
    int y{};
    int t{};
    std::cin >> x >> y >> t;
    x--;
    y--;
    if (capacity[x].find(y) == capacity[x].end()) {
      graph[x].push_back(y);
      graph[y].push_back(x);
    }
    capacity[x][y] += t;
  }
  std::cout << FF(0, n - 1, capacity, graph);
  return 0;
}
