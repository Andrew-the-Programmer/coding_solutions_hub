// Copyright 2024 Andrew

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <set>
#include <stack>
#include <vector>

using NodeType = size_t;

struct Edge {
  NodeType from;
  NodeType to;

  Edge() = default;
  Edge(NodeType from, NodeType to) : from(from), to(to) {
  }
};

// Graph: oriented
// with degree
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit Graph(size_t n) : adj_list_(n), degree_in_(n, 0), degree_out_(n, 0) {
  }

  void AddEdge(const Edge &edge) {
    adj_list_[edge.from].emplace_back(edge);
    ++degree_out_[edge.from];
    ++degree_in_[edge.to];
    ++count_edges_;
  }
  size_t CountNodes() const {
    return adj_list_.size();
  }
  size_t CountEdges() const {
    return count_edges_;
  }

  auto &&GetEdges(NodeType node) const {
    return adj_list_[node];
  }
  auto &&GetEdges(NodeType node) {
    return adj_list_[node];
  }

  auto GetDegreeIn(NodeType node) const {
    return degree_in_[node];
  }
  auto GetDegreeOut(NodeType node) const {
    return degree_out_[node];
  }

  auto GetDegree(NodeType node) const {
    return static_cast<int64_t>(GetDegreeIn(node)) - GetDegreeOut(node);
  }

 protected:
  AdjListT adj_list_;
  std::vector<size_t> degree_in_;
  std::vector<size_t> degree_out_;
  size_t count_edges_ = 0;
};

bool CheckEulerCycle(const Graph &graph) {
  for (size_t i = 0; i < graph.CountNodes(); ++i) {
    if (graph.GetDegree(i) != 0) {
      return false;
    }
  }
  return true;
}

std::vector<NodeType> FindEulerCycle(Graph &graph) {
  std::vector<NodeType> cycle;

  if (!CheckEulerCycle(graph)) {
    // std::cout << "No cycle" << std::endl;
    return {};
  }

  std::function<void(NodeType, std::optional<Edge>)> dfs = [&](NodeType node, std::optional<Edge> cur_edge) {
    // std::cout << "begin: " << node << std::endl;
    auto &neighbors = graph.GetEdges(node);
    // std::optional<Edge> edge_to_parent;
    while (!neighbors.empty()) {
      auto edge = neighbors.begin();
      auto size = neighbors.size();
      if (size != 1 && cur_edge && edge->to == cur_edge->from) {
        edge = neighbors.begin() + 1;
      }
      auto next = edge->to;
      neighbors.erase(edge);
      dfs(next, *edge);

      // auto size = neighbors.size();
      // if (size != 1 && cur_edge && next == cur_edge->from) {
      //   auto edge = neighbors[1];
      //   auto next = edge.to;
      //   neighbors.erase(neighbors.begin() + 1);
      //   dfs(neighbor, )
      // } else {
      //   int64_t neighbor = edges_[node][0];
      //   edges_[node].erase(edges_[node].begin());
      //   DfsEulerCycle(node, neighbor);
      // }
    }
    // std::cout << "end: " << node << std::endl;
    cycle.emplace_back(node);
  };

  for (size_t i = 0; i < graph.CountNodes(); ++i) {
    if (graph.GetDegreeOut(i) != 0) {
      dfs(i, {});
      break;
    }
  }

  if (cycle.size() != graph.CountEdges() + 1) {
    // std::cout << "No cycle" << std::endl;
    return {};
  }

  return cycle;
}

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(m);
  for (size_t i = 0; i < n; ++i) {
    size_t len{};
    std::cin >> len;
    NodeType from{};
    std::cin >> from;
    --from;
    for (size_t j = 0; j < len; ++j) {
      NodeType to{};
      std::cin >> to;
      --to;
      graph.AddEdge({from, to});
      from = to;
    }
  }
  auto cycle = FindEulerCycle(graph);
  std::cout << cycle.size() << std::endl;
  for (auto &node : cycle) {
    std::cout << node + 1 << " ";
  }
  std::cout << std::endl;
}
