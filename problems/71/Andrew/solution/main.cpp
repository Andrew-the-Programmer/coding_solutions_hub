// Copyright 2024 Andrew

#include <cstddef>
#include <iostream>
#include <vector>

using NodeType = size_t;

// Edge: not oriented, not weighted
struct Edge {
  NodeType from;
  NodeType to;

  Edge() = default;
  Edge(NodeType from, NodeType to) : from(from), to(to) {
  }

  Edge Reverse() const {
    return {to, from};
  }
};

// Graph: not oriented
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit Graph(size_t n) : adj_list_(n) {
  }

  void AddEdge(const Edge& edge) {
    adj_list_[edge.from].emplace_back(edge);
    adj_list_[edge.to].emplace_back(edge.Reverse());
  }

  size_t CountNodes() const {
    return adj_list_.size();
  }

  auto&& GetEdges(NodeType node) const {
    return adj_list_[node];
  }

 protected:
  AdjListT adj_list_;
};

using E = Edge;
using G = Graph;

// (DFS)
void PaintGraphHelper(const G& graph, NodeType cur, std::vector<bool>& visited, std::vector<size_t>& colors,
                      size_t color) {
  colors[cur] = color;
  visited[cur] = true;
  for (auto& edge : graph.GetEdges(cur)) {
    auto next = edge.to;
    if (visited[next]) {
      continue;
    }
    PaintGraphHelper(graph, next, visited, colors, color);
  }
}

auto PaintGraph(const G& graph) {
  size_t n = graph.CountNodes();
  std::vector<size_t> colors(n);
  std::vector<bool> visited(n, false);
  size_t count = 0;
  for (size_t start = 0; start < n; ++start) {
    if (visited[start]) {
      continue;
    }
    PaintGraphHelper(graph, start, visited, colors, start);
    count++;
  }
  return std::pair(colors, count);
}

void Solution(const G& graph) {
  auto n = graph.CountNodes();
  auto [colors, count] = PaintGraph(graph);
  std::cout << count << "\n";
  std::vector<std::vector<NodeType>> groups(n);
  for (size_t i = 0; i < n; ++i) {
    groups[colors[i]].emplace_back(i);
  }
  for (auto& group : groups) {
    if (group.empty()) {
      continue;
    }
    std::cout << group.size() << "\n";
    for (auto& node : group) {
      std::cout << node + 1 << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  G graph(n);
  for (size_t i = 0; i < m; ++i) {
    NodeType from{};
    NodeType to{};
    std::cin >> from >> to;
    --from;
    --to;
    graph.AddEdge({from, to});
  }
  Solution(graph);
  return 0;
}
