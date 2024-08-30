// Copyright 2024 Andrew

#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>
#include <deque>

using NodeType = size_t;

struct Edge {
  NodeType from;
  NodeType to;

  Edge() = default;
  Edge(NodeType from, NodeType to) : from(from), to(to) {
  }
};

// Graph: oriented
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

void DfsStack(const Graph& graph, NodeType u, std::vector<bool>& visited, std::deque<NodeType>& dfs_stack) {
  visited[u] = true;
  for (auto& edge : graph.GetEdges(u)) {
    auto neighbor = edge.to;
    if (!visited[neighbor]) {
      DfsStack(graph, neighbor, visited, dfs_stack);
    }
  }
  dfs_stack.push_front(u);
}

void DfsHelper(const Graph& graph, NodeType cur, std::vector<bool>& visited, std::function<void(NodeType)> func) {
  visited[cur] = true;
  func(cur);
  for (auto& edge : graph.GetEdges(cur)) {
    auto neighbor = edge.to;
    if (!visited[neighbor]) {
      DfsHelper(graph, neighbor, visited, func);
    }
  }
}

void Dfs(const Graph& graph, std::function<void(NodeType)> func) {
  std::vector<bool> visited(graph.CountNodes(), false);
  for (NodeType start = 0; start < graph.CountNodes(); ++start) {
    if (!visited[start]) {
      DfsHelper(graph, start, visited, func);
    }
  }
}

auto Solution(const Graph& graph, const Graph& graph_reversed) {
  auto n = graph.CountNodes();

  // Nodes in order of DFS
  std::deque<NodeType> nodes;
  // auto add_node = [&nodes](NodeType cur) { nodes.push_back(cur); };
  // Dfs(graph, add_node);

  std::vector<bool> visited1(n, false);

  for (NodeType i = 0; i < n; i++) {
    if (!visited1[i]) {
      DfsStack(graph, i, visited1, nodes);
    }
  }

  // components[node] - number of strong component
  std::vector<size_t> components(n, 0);
  size_t component_count = 0;
  auto add_component = [&components, &component_count](NodeType cur) { components[cur] = component_count; };
  std::vector<bool> visited(n, false);
  while (!nodes.empty()) {
    auto cur = nodes.front();
    nodes.pop_front();
    if (!visited[cur]) {
      component_count++;
      DfsHelper(graph_reversed, cur, visited, add_component);
    }
  }

  std::cout << component_count << std::endl;
  for (size_t i = 0; i < n; i++) {
    std::cout << components[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  Graph graph(n);
  Graph graph_reversed(n);

  for (size_t i = 0; i < m; i++) {
    size_t from{};
    size_t to{};
    std::cin >> from >> to;
    --from;
    --to;
    graph.AddEdge({from, to});
    graph_reversed.AddEdge({to, from});
  }

  Solution(graph, graph_reversed);
}
