// Copyright 2024 Andrew

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>
#include <queue>

using NodeType = uint16_t;
using WeightType = int32_t;

struct Edge {
  NodeType from;
  NodeType to;
  WeightType weight;

  Edge() = default;
  Edge(NodeType from, NodeType to, WeightType weight) : from(from), to(to), weight(weight) {
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

// Not oriented
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

auto Diijkstra(const Graph& graph, NodeType start) {
  auto n = graph.CountNodes();
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
  SetIostream();

  size_t n{};
  NodeType start{};
  NodeType finish{};
  std::cin >> n >> start >> finish;
  --start;
  --finish;
  Graph graph(n);

  for (NodeType from = 0; from < n; ++from) {
    for (NodeType to = 0; to < n; ++to) {
      WeightType weight{};
      std::cin >> weight;
      if (from == to || weight == -1) {
        continue;
      }
      graph.AddEdge({from, to, weight});
    }
  }

  auto dists = Diijkstra(graph, start);
  auto dist = dists[finish];
  if (dist) {
    std::cout << *dist;
  } else {
    std::cout << -1;
  }
  std::cout << '\n';
}
