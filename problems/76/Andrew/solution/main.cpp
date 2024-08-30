#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

void DFS(std::vector<std::vector<std::pair<int, int>>> &graph, int v, std::vector<int> &colors,
         std::vector<int> &time_in, std::vector<int> &time_out, int &time,
         std::vector<std::pair<std::pair<int, int>, int>> &bridge, int p) {
  colors[v] = 1;
  time_in[v] = time_out[v] = time++;
  for (auto &i : graph[v]) {
    if (i.first == p) {
      continue;
    }
    if (colors[i.first] == 1) {
      time_out[v] = std::min(time_out[v], time_in[i.first]);
    } else if (colors[i.first] == 0) {
      DFS(graph, i.first, colors, time_in, time_out, time, bridge, v);
      time_out[v] = std::min(time_out[v], time_out[i.first]);
      if (time_in[v] < time_out[i.first]) {
        bridge.emplace_back(std::pair(v, i.first), i.second);
      }
    }
  }
  colors[v] = 2;
}

int main() {
  int n{};
  size_t m{};
  int time = 0;
  std::cin >> n >> m;
  if (n == 0 && m == 0) {
    std::cout << 0;
    return 0;
  }
  std::vector<std::pair<std::pair<int, int>, int>> bridge{};
  std::vector<int> time_in(n, 999999);
  std::vector<int> time_out(n, 999999);
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  int a{};
  int b{};
  for (size_t i = 0; i < m; ++i) {
    std::cin >> a >> b;
    a--, b--;
    graph[a].emplace_back(b, i);
    graph[b].emplace_back(a, i);
  }
  std::vector<int> colors(n, 0);
  for (int i = 0; i < n; ++i) {
    if (colors[i] == 2) {
      continue;
    }
    DFS(graph, i, colors, time_in, time_out, time, bridge, -1);
  }
  for (size_t i = 0; i < bridge.size(); ++i) {
    int count = 0;
    for (size_t j = 0; j < graph[bridge[i].first.first].size(); ++j) {
      if (graph[bridge[i].first.first][j].first == bridge[i].first.second) {
        count++;
      }
    }
    if (count >= 2) {
      bridge.erase(bridge.begin() + static_cast<int>(i));
    }
  }
  std::cout << bridge.size() << std::endl;
  std::sort(
      bridge.begin(), bridge.end(),
      [](std::pair<std::pair<int, int>, int> a, std::pair<std::pair<int, int>, int> b) { return a.second < b.second; });
  for (auto &i : bridge) {
    std::cout << i.second + 1 << " ";
  }
  return 0;
}