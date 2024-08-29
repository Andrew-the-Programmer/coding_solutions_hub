#include <iostream>
#include <queue>
#include <vector>

using NodeType = size_t;

// Edge: oriented, not weighted
struct Edge {
  NodeType from;
  NodeType to;

  Edge() = default;
  Edge(NodeType from, NodeType to) : from(from), to(to) {
  }
};

// Graph: oriented
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit Graph(size_t n) : adj_list_(n) {
  }

  void AddEdge(const Edge& edge) {
    adj_list_[edge.from].emplace_back(edge);
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

std::vector<NodeType> TopologicalSort(const Graph& graph) {
  size_t n = graph.CountNodes();
  // degree_in[i] = number of incoming edges
  std::vector<NodeType> degree_in(n, 0);
  std::vector<NodeType> result;
  for (size_t cur = 0; cur < n; cur++) {
    for (auto& edge : graph.GetEdges(cur)) {
      degree_in[edge.to]++;
    }
  }
  std::queue<NodeType> q;
  for (size_t cur = 0; cur < n; cur++) {
    if (degree_in[cur] == 0) {
      q.push(cur);
    }
  }
  while (!q.empty()) {
    NodeType cur = q.front();
    q.pop();
    result.push_back(cur);
    for (auto& edge : graph.GetEdges(cur)) {
      auto neighbor = edge.to;
      if (--degree_in[neighbor] == 0) {
        q.push(neighbor);
      }
    }
  }
  if (result.size() != n) {
    return {};
  }
  return result;
}
void SetIostream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
}

int main() {
  SetIostream();
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(n);
  for (size_t i = 0; i < m; i++) {
    NodeType from{};
    NodeType to{};
    std::cin >> from >> to;
    --from;
    --to;
    graph.AddEdge({from, to});
  }
  std::vector<NodeType> sorted_nodes = TopologicalSort(graph);
  if (sorted_nodes.size() != n) {
    std::cout << -1 << std::endl;
  } else {
    for (auto& node : sorted_nodes) {
      std::cout << node + 1 << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
