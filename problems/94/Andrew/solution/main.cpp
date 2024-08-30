#include <iostream>
#include <vector>

const int kMax = 2147483647;

struct Edge {
  int u{};
  int v{};
  int w{};
  Edge(int u, int v, int w) : u(u), v(v), w(w){};
  Edge() = default;
};

int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n);
  for (int i = 0; i < m; ++i) {
    int u{};
    int v{};
    int w{};
    std::cin >> u >> v >> w;
    graph.emplace_back(u, v, w);
  }
  return 0;
}