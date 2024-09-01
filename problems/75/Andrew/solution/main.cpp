// Copyright 2024 Andrew

#include <cstddef>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

using NodeType = size_t;

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

auto FindArticulationPoints(const Graph &graph) {
  size_t n = graph.CountNodes();
  std::vector<bool> visited(n, false);
  // First time visiting a node
  // Represents dfs traverse order
  std::vector<size_t> time_in(n, 0);
  // time_out[i] = max(time_in[j]) for every j, such that path from i to j exists.
  std::vector<size_t> time_out(n, 0);
  std::set<NodeType> articulation_points;
  size_t time_count = 0;

  std::function<void(NodeType)> helper = [&](NodeType cur) {
    visited[cur] = true;
    time_in[cur] = time_out[cur] = time_count++;
    for (auto &edge : graph.GetEdges(cur)) {
      auto next = edge.to;
      if (visited[next]) {
        time_out[cur] = std::min(time_out[cur], time_in[next]);
        continue;
      }
      helper(next);
      time_out[cur] = std::min(time_out[cur], time_out[next]);
      if (time_out[next] >= time_in[cur]) {
        articulation_points.emplace(cur);
      }
    }
  };

  std::function<void(NodeType)> helper_root = [&](NodeType root) {
    visited[root] = true;
    time_in[root] = time_out[root] = time_count++;
    size_t child_count = 0;
    for (auto &edge : graph.GetEdges(root)) {
      auto next = edge.to;
      if (visited[next]) {
        continue;
      }
      ++child_count;
      helper(next);
    }
    if (child_count > 1) {
      articulation_points.emplace(root);
    }
  };

  for (size_t root = 0; root < graph.CountNodes(); root++) {
    if (!visited[root]) {
      helper_root(root);
    }
  }

  return articulation_points;
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
    graph.AddEdge({from, to});
  }
  auto articulation_points = FindArticulationPoints(graph);
  std::cout << articulation_points.size() << std::endl;
  for (auto &node : articulation_points) {
    std::cout << node + 1 << "\n";
  }
}
