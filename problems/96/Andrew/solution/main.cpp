#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>
#include <queue>

using NodeType = int;
using WeightType = int;

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

  friend auto& operator<<(std::ostream& stream, const Edge& edge) {
    stream << edge.from << ' ' << edge.to << ' ' << edge.weight;
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, Edge& edge) {
    stream >> edge.from >> edge.to >> edge.weight;
    return stream;
  }
};

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

  void Clear() {
    for (auto& v : adj_list_) {
      v.clear();
    }
  }
  void Resize(size_t n) {
    adj_list_.resize(n);
  }

 protected:
  AdjListT adj_list_;
};

auto Diijkstra(const Graph& graph, NodeType start) {
  size_t n = graph.CountNodes();
  std::vector<bool> visited(n, false);
  std::vector<std::optional<size_t>> dists(n);
  dists[start] = 0;
  auto cmp = [](const Edge& first, const Edge& second) { return first.weight > second.weight; };
  std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> queue(cmp);
  queue.emplace(start, start, 0);
  while (!queue.empty()) {
    auto cur = queue.top();
    queue.pop();
    if (visited[cur.to]) {
      continue;
    }
    visited[cur.to] = true;
    for (auto&& next : graph.GetEdges(cur.to)) {
      if (!dists[next.to].has_value() || dists[next.to].value() > dists[next.from].value() + next.weight) {
        dists[next.to] = dists[next.from].value() + next.weight;
        queue.emplace(next.from, next.to, dists[next.to].value());
      }
    }
  }
  return dists;
}

void SetIostream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  constexpr size_t kMax = 2009000999;

  SetIostream();

  size_t k{};
  std::cin >> k;

  for (size_t i = 0; i < k; ++i) {
    size_t n{};
    size_t m{};
    std::cin >> n >> m;
    Graph graph(n);
    for (size_t j = 0; j < m; ++j) {
      Edge edge;
      std::cin >> edge;
      graph.AddEdge(edge);
    }
    NodeType start{};
    std::cin >> start;
    auto dists = Diijkstra(graph, start);
    for (auto& dist : dists) {
      if (dist) {
        std::cout << *dist << ' ';
      } else {
        std::cout << kMax << ' ';
      }
    }
  }
}
