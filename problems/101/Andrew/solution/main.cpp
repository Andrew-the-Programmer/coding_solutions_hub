// Copyright 2024 Andrew

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stack>
#include <unordered_map>
#include <vector>

using NodeType = uint16_t;
using CapacityType = int32_t;

struct Edge {
  NodeType from;
  NodeType to;

  Edge() = default;
  Edge(NodeType from, NodeType to) : from(from), to(to) {
  }

  Edge Reversed() const {
    return {to, from};
  }

  friend std::ostream& operator<<(std::ostream& stream, const Edge& edge) {
    return stream << edge.from << ' ' << edge.to;
  }
};

// Not oriented
class Graph {
  using AdjListT = std::vector<std::vector<NodeType>>;

 public:
  explicit Graph(size_t n, size_t m) : adj_list_(n), count_edges_(m) {
  }

  void AddEdge(const Edge& edge) {
    adj_list_[edge.from].emplace_back(edge.to);
  }

  size_t CountNodes() const {
    return adj_list_.size();
  }
  size_t CountEdges() const {
    return count_edges_;
  }

  auto&& GetEdges(NodeType node) const {
    return adj_list_[node];
  }

 protected:
  AdjListT adj_list_;
  size_t count_edges_ = 0;
};

auto FordFulkerson(const Graph& graph, NodeType start, NodeType end,
                   std::vector<std::unordered_map<NodeType, CapacityType>>& flow) {
  auto n = graph.CountNodes();
  CapacityType max_flow = 0;
  std::vector<bool> visited(n);
  std::vector<NodeType> parent(n);

  auto dfs = [&]() {
    std::fill(visited.begin(), visited.end(), false);
    visited[start] = true;
    std::stack<NodeType> stack;
    stack.push(start);
    while (!stack.empty()) {
      auto curr_node = stack.top();
      stack.pop();
      for (auto& next_node : graph.GetEdges(curr_node)) {
        if (visited[next_node]) {
          continue;
        }
        if (flow[curr_node][next_node] <= 0) {
          continue;
        }
        visited[next_node] = true;
        parent[next_node] = curr_node;
        stack.push(next_node);
        if (next_node == end) {
          return true;
        }
      }
    }
    return false;
  };

  while (dfs()) {
    auto max_excess_flow = std::numeric_limits<CapacityType>::max();
    for (auto node = end; node != start; node = parent[node]) {
      auto p = parent[node];
      max_excess_flow = std::min(max_excess_flow, flow[p][node]);
    }
    for (auto node = end; node != start; node = parent[node]) {
      auto p = parent[node];
      flow[node][p] += max_excess_flow;
      flow[p][node] -= max_excess_flow;
    }
    max_flow += max_excess_flow;
  }
  return max_flow;
}

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;

  const NodeType start = 0;
  const NodeType end = n - 1;
  std::vector<std::unordered_map<NodeType, CapacityType>> flow(n);

  Graph graph(n, m);
  for (size_t i = 0; i < m; i++) {
    NodeType from{};
    NodeType to{};
    CapacityType capacity{};
    std::cin >> from >> to >> capacity;
    --from;
    --to;
    if (!flow[from].contains(to)) {
      Edge edge(from, to);
      graph.AddEdge(edge);
      graph.AddEdge(edge.Reversed());
      flow[from][to] = 0;
    }
    flow[from][to] += capacity;
  }

  std::cout << '\n';
  std::cout << FordFulkerson(graph, start, end, flow) << '\n';
}  // I hate this problem a lot
