// Copyright 2024 Andrew

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>
#include <queue>
#include <limits>

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
  auto&& GetEdges(NodeType node) {
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
  std::vector<std::optional<WeightType>> dists(n);
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

auto BellmanFord(const Graph& graph, NodeType start) {
  auto n = graph.CountNodes();
  std::vector<bool> visited(n, false);
  std::vector<std::optional<WeightType>> dists(n);
  dists[start] = 0;

  for (NodeType i = 0; i < n - 1; ++i) {
    for (NodeType j = 0; j < n; ++j) {
      for (const auto& edge : graph.GetEdges(j)) {
        auto from = edge.from;
        auto to = edge.to;
        if (!dists[from].has_value()) {
          continue;
        }
        auto new_dist = dists[from].value() + edge.weight;
        if (!dists[to].has_value() || new_dist < dists[to].value()) {
          dists[to] = new_dist;
        }
      }
    }
  }
  return dists;
}

// Explanation:
// https://www.youtube.com/watch?v=MV7EAD9zL64&t=19s
auto Johnson(const Graph& graph) {
  auto n = graph.CountNodes();
  auto graph_copy = graph;

  // Add a fictitious node "source"
  graph_copy.Resize(n + 1);
  NodeType source = n;
  for (NodeType node = 0; node < n; ++node) {
    graph_copy.AddEdge({source, node, 0});
  }

  auto bf_dists = BellmanFord(graph_copy, source);
  // Note: bf_dists[i][j] always has value

  // Make edges positive
  for (NodeType node = 0; node < n; ++node) {
    for (auto& edge : graph_copy.GetEdges(node)) {
      edge.weight += static_cast<WeightType>(*bf_dists[edge.from] - *bf_dists[edge.to]);
    }
  }

  // This makes Diijkstra correct
  // Note that this does not remove source node
  graph_copy.Resize(n);

  std::vector<std::vector<std::optional<WeightType>>> diij_dists(n);
  for (NodeType start = 0; start < n; ++start) {
    // Note that source node does not affect Diijkstra's result
    diij_dists[start] = Diijkstra(graph_copy, start);
  }

  // Restore the answer
  for (NodeType from = 0; from < n; ++from) {
    for (NodeType to = 0; to < n; ++to) {
      if (diij_dists[from][to].has_value()) {
        *diij_dists[from][to] += static_cast<WeightType>(*bf_dists[to] - *bf_dists[from]);
      }
    }
  }
  return diij_dists;
}

void SetIostream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  SetIostream();

  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(n);

  for (size_t i = 0; i < m; ++i) {
    Edge edge;
    std::cin >> edge;
    graph.AddEdge(edge);
  }

  auto dists = Johnson(graph);

  // Find max
  WeightType max = std::numeric_limits<WeightType>::min();
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (dists[i][j].has_value()) {
        max = std::max(max, dists[i][j].value());
      }
    }
  }
  std::cout << max << std::endl;
}
