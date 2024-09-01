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
  size_t number;

  Edge() = default;
  Edge(NodeType from, NodeType to, size_t number) : from(from), to(to), number(number) {
  }

  Edge Reverse() const {
    return {to, from, number};
  }
};

struct TriangleEdge {
  NodeType first_node;
  NodeType second_node;
  NodeType third_node;
  size_t number;
};

// Graph: not oriented
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit Graph(size_t n, size_t m) : n(n), m(m), adj_list_(n + m) {
  }

  void AddEdge(const Edge &edge) {
    adj_list_[edge.from].emplace_back(edge);
    adj_list_[edge.to].emplace_back(edge.Reverse());
  }
  void AddEdge(const TriangleEdge &edge) {
    auto strange_node = n + edge.number;
    AddEdge(Edge{edge.first_node, strange_node, edge.number});
    AddEdge(Edge{edge.second_node, strange_node, edge.number});
    AddEdge(Edge{edge.third_node, strange_node, edge.number});
  }

  size_t CountNodes() const {
    return adj_list_.size();
  }

  auto &&GetEdges(NodeType node) const {
    return adj_list_[node];
  }

 public:
  size_t n = 0;
  size_t m = 0;

  AdjListT adj_list_;
};

void Solution(const Graph &graph) {
  size_t size = graph.CountNodes();
  std::vector<bool> visited(size, false);
  std::vector<size_t> time_in(size, 0);
  std::vector<size_t> time_up(size, 0);
  std::set<size_t> articulation_points;
  size_t time_count = 0;

  std::function<void(NodeType, bool)> dfs_helper = [&](NodeType cur, bool is_root) {
    visited[cur] = true;
    time_in[cur] = time_up[cur] = time_count++;
    size_t children_count = 0;
    for (auto &edge : graph.GetEdges(cur)) {
      auto next = edge.to;
      if (visited[next]) {
        time_up[cur] = std::min(time_up[cur], time_in[next]);
        continue;
      }
      ++children_count;
      dfs_helper(next, false);
      time_up[cur] = std::min(time_up[cur], time_up[next]);
      if (!is_root && cur >= graph.n && time_up[next] >= time_in[cur]) {
        articulation_points.insert(cur);
      }
    }
    if (is_root && cur >= graph.n && children_count > 1) {
      articulation_points.insert(cur);
    }
  };
  for (size_t i = 0; i < size; ++i) {
    if (!visited[i]) {
      dfs_helper(i, true);
    }
  }

  std::cout << articulation_points.size() << '\n';
  for (auto &point : articulation_points) {
    std::cout << point - graph.n + 1 << '\n';
  }
}

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(n, m);
  for (size_t i = 0; i < m; ++i) {
    NodeType first{};
    NodeType second{};
    NodeType third{};
    std::cin >> first >> second >> third;
    --first;
    --second;
    --third;
    graph.AddEdge({first, second, third, i});
  }
  Solution(graph);
}
