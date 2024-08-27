// Copyright 2024 Andrew

#include <cstddef>
#include <iostream>
#include <optional>
#include <vector>
#include <queue>

using NodeType = size_t;
using WeightType = int;

struct EdgeOW {
  NodeType from;
  NodeType to;
  WeightType weight;

  EdgeOW() = default;
  EdgeOW(NodeType from, NodeType to, WeightType weight) : from(from), to(to), weight(weight) {
  }

  friend auto& operator<<(std::ostream& stream, const EdgeOW& edge) {
    stream << edge.from << ' ' << edge.to << ' ' << edge.weight;
    return stream;
  }

  friend std::istream& operator>>(std::istream& stream, EdgeOW& edge) {
    stream >> edge.from >> edge.to >> edge.weight;
    return stream;
  }
};

class GraphOW {
  using AdjListT = std::vector<std::vector<EdgeOW>>;

 public:
  explicit GraphOW(size_t n) : adj_list_(n) {
  }

  void AddEdge(const EdgeOW& edge) {
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

using E = EdgeOW;
using G = GraphOW;

auto Djkstra(const G& graph, NodeType start) {
  std::vector<std::optional<size_t>> dist(graph.CountNodes());
  dist[start] = 0;

  auto cmp = [](const E& first, const E& second) { return first.weight > second.weight; };

  std::priority_queue<E, std::vector<E>, decltype(cmp)> queue(cmp);

  queue.emplace(start, start, 0);
  // Current edge (weights are distances)
  E cur;
  while (!queue.empty()) {
    cur = queue.top();
    queue.pop();

    // Iterate through edges from cur.to
    for (auto&& next : graph.GetEdges(cur.to)) {
      if (!dist[next.to].has_value() || dist[next.to].value() > dist[next.from].value() + next.weight) {
        // Update dist to next.to
        dist[next.to] = dist[next.from].value() + next.weight;
        queue.emplace(next.from, next.to, dist[next.to].value());
      }
    }
  }
  return dist;
}

int main() {
  size_t n{};
  size_t m{};

  NodeType start{};
  NodeType finish{};
  E edge;

  std::cin >> n >> m;
  std::cin >> start >> finish;
  --start;
  --finish;

  G graph(n);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> edge;
    --edge.from;
    --edge.to;
    graph.AddEdge(edge);
  }

  auto dists = Djkstra(graph, start);
  if (dists[finish].has_value()) {
    std::cout << dists[finish].value();
  } else {
    std::cout << -1;
  }
  return 0;
}
