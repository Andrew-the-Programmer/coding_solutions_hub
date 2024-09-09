#include <cstddef>
#include <queue>
#include <vector>
#include <iostream>

using NodeType = size_t;
using WeightType = size_t;

struct Edge {
  NodeType from;
  NodeType to;
  WeightType weight;

  Edge() = default;
  Edge(NodeType from, NodeType to, WeightType weight) : from(from), to(to), weight(weight) {
  }

  Edge Reverse() const {
    return {to, from, weight};
  }

  friend auto& operator<<(std::ostream& out, const Edge& edge) {
    return out << edge.from << ' ' << edge.to << ' ' << edge.weight;
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

size_t PrimAlgorithm(const Graph& graph) {
  auto n = graph.CountNodes();
  auto cmp = [](const Edge& first, const Edge& second) { return first.weight > second.weight; };
  std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> queue(cmp);
  std::vector<bool> visited(n, false);
  WeightType total_weight = 0;

  queue.emplace(0, 0, 0);
  while (!queue.empty()) {
    auto cur_edge = queue.top();
    queue.pop();
    if (visited[cur_edge.to]) {
      continue;
    }
    visited[cur_edge.to] = true;
    total_weight += cur_edge.weight;
    for (auto& next_edge : graph.GetEdges(cur_edge.to)) {
      if (!visited[next_edge.to]) {
        queue.push(next_edge);
      }
    }
  }
  return total_weight;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(n);
  for (size_t i = 0; i < m; i++) {
    NodeType from{};
    NodeType to{};
    WeightType weight{};
    std::cin >> from >> to >> weight;
    --from;
    --to;
    graph.AddEdge({from, to, weight});
  }

  auto min_weight = PrimAlgorithm(graph);
  std::cout << min_weight << '\n';
}
