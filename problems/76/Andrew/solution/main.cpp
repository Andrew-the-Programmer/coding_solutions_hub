// Copyright 2024 Andrew

#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>
#include <set>
#include <vector>

using NodeType = size_t;

struct Edge {
  NodeType from;
  NodeType to;
  size_t number;

  Edge() = default;
  Edge(NodeType from, NodeType to, size_t number) : from(from), to(to), number(number) {
  }

  Edge Reverse() const {
    return {to, from, number};
  }

  bool operator<(const Edge &other) const {
    return number < other.number;
  }

  bool operator==(const Edge &other) const {
    return number == other.number;
  }
};

// Graph: not oriented
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit Graph(size_t n) : adj_list_(n) {
  }

  void AddEdge(const Edge &edge) {
    adj_list_[edge.from].emplace_back(edge);
    adj_list_[edge.to].emplace_back(edge.Reverse());
  }

  size_t CountNodes() const {
    return adj_list_.size();
  }

  auto &&GetEdges(NodeType node) const {
    return adj_list_[node];
  }

 protected:
  AdjListT adj_list_;
};

auto FindBridges(const Graph &graph) {
  size_t n = graph.CountNodes();
  std::vector<bool> visited(n, false);
  // First time visiting a node
  // Represents dfs traverse order
  std::vector<size_t> time_in(n, 0);
  // time_out[i] = max(time_in[j]) for every j, such that path from i to j exists.
  std::vector<size_t> time_out(n, 0);
  std::set<size_t> bridges;
  size_t time_count = 0;

  std::function<void(NodeType, NodeType)> helper = [&](NodeType cur, std::optional<NodeType> parent) {
    visited[cur] = true;
    time_in[cur] = time_out[cur] = time_count++;
    for (auto &edge : graph.GetEdges(cur)) {
      auto next = edge.to;
      // only thing parent is useful for
      if (parent && next == *parent) {
        continue;
      }
      if (visited[next]) {
        time_out[cur] = std::min(time_out[cur], time_in[next]);
        continue;
      }
      helper(next, cur);
      time_out[cur] = std::min(time_out[cur], time_out[next]);
      if (time_out[next] > time_in[cur]) {
        bridges.emplace(edge.number);
      }
    }
  };

  for (size_t root = 0; root < n; root++) {
    if (!visited[root]) {
      helper(root, {});
    }
  }
  return bridges;
}

int main() {
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
    graph.AddEdge({from, to, i});
  }
  auto bridges = FindBridges(graph);
  std::cout << bridges.size() << std::endl;
  for (auto &edge : bridges) {
    std::cout << edge + 1 << "\n";
  }
}
