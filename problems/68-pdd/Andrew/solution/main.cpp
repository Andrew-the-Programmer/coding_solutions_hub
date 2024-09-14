// Copyright 2024 Andrew

#include <cstddef>
#include <deque>
#include <iostream>
#include <vector>
#include <optional>

using NodeType = size_t;
using WeightType = int;

struct Edge {
  NodeType from;
  NodeType to;
  WeightType weight;

  Edge() = default;
  Edge(NodeType from, NodeType to, WeightType weight = 1) : from(from), to(to), weight(weight) {
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

// BFS for 0-1 graph
auto BFS(const Graph& graph, NodeType start) {
  std::vector<std::optional<size_t>> dist(graph.CountNodes());
  dist[start] = 0;
  std::deque<NodeType> deque;
  deque.push_back(start);
  dist[start] = 0;
  while (!deque.empty()) {
    NodeType cur = deque.front();
    deque.pop_front();
    for (auto&& next : graph.GetEdges(cur)) {
      auto new_dist = dist[next.from].value() + next.weight;
      if (dist[next.to].has_value() && dist[next.to].value() <= new_dist) {
        // Don't need to update dist to next.to
        continue;
      }
      // Update dist to next.to
      dist[next.to] = new_dist;
      if (next.weight == 0) {
        deque.push_front(next.to);
      } else {
        deque.push_back(next.to);
      }
    }
  }
  return dist;
}

void SetIostream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  SetIostream();

  size_t n{};
  size_t m{};

  std::cin >> n >> m;

  Graph graph(n);
  // Input graph
  for (size_t i = 0; i < m; ++i) {
    NodeType from{};
    NodeType to{};
    std::cin >> from >> to;
    --from;
    --to;
    graph.AddEdge({from, to, 0});
    graph.AddEdge({to, from, 1});
  }

  size_t k{};
  std::cin >> k;
  for (size_t i = 0; i < k; ++i) {
    NodeType start{};
    NodeType finish{};
    std::cin >> start >> finish;
    --start;
    --finish;
    auto dists = BFS(graph, start);
    if (!dists[finish]) {
      std::cout << -1 << '\n';
    } else {
      std::cout << dists[finish].value() << '\n';
    }
  }

  return 0;
}
