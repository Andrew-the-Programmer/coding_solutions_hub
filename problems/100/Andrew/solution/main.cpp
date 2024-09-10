// Copyright 2024 Andrew

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ios>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

using NodeType = uint16_t;
using WeightType = int32_t;

struct Edge {
  NodeType from;
  NodeType to;
  WeightType weight;

  Edge() = default;
  Edge(NodeType from, NodeType to, WeightType weight) : from(from), to(to), weight(weight) {
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

auto FloydWarshall(const Graph& graph) {
  auto n = graph.CountNodes();
  std::vector dists(n, std::vector<std::optional<WeightType>>(n));

  // Lambda function to simplify code a little
  auto update_value_to_min = [](std::optional<WeightType>& value, WeightType new_value) {
    if (!value.has_value() || new_value < value.value()) {
      value = new_value;
    }
  };

  for (size_t from = 0; from < n; from++) {
    update_value_to_min(dists[from][from], 0);
    for (const auto& edge : graph.GetEdges(from)) {
      auto to = edge.to;
      update_value_to_min(dists[from][to], edge.weight);
    }
  }

  for (size_t middle = 0; middle < n; middle++) {
    for (size_t from = 0; from < n; from++) {
      for (size_t to = 0; to < n; to++) {
        if (!dists[from][middle] || !dists[middle][to]) {
          continue;
        }
        auto new_dist = dists[from][middle].value() + dists[middle][to].value();
        update_value_to_min(dists[from][to], new_dist);
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
  std::cin >> n;
  Graph graph(n);

  for (NodeType from = 0; from < n; from++) {
    for (NodeType to = 0; to < n; to++) {
      WeightType weight{};
      std::cin >> weight;
      graph.AddEdge({from, to, weight});
    }
  }

  auto dists = FloydWarshall(graph);
  for (NodeType from = 0; from < n; from++) {
    for (NodeType to = 0; to < n; to++) {
      if (dists[from][to].has_value()) {
        std::cout << dists[from][to].value() << ' ';
      } else {
        throw std::logic_error{"No path found"};
      }
    }
    std::cout << '\n';
  }
}
