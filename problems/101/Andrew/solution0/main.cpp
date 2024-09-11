// Copyright 2024 Andrew

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <stack>
#include <vector>

using NodeType = uint32_t;
using CapacityType = uint32_t;

struct Edge {
  NodeType from;
  NodeType to;
  CapacityType capacity;
  size_t id;

  Edge() = default;
  Edge(NodeType from, NodeType to, CapacityType capacity = 0, size_t id = 0)
      : from(from), to(to), capacity(capacity), id(id) {
  }

  Edge Reversed() const {
    return {to, from, capacity, id};
  }

  bool operator==(const Edge& other) const {
    return (from == other.from) && (to == other.to) && (capacity == other.capacity);
    // return id == other.id;
  }

  bool operator<(const Edge& other) const {
    return id < other.id;
  }

  friend std::istream& operator>>(std::istream& stream, Edge& edge) {
    stream >> edge.from >> edge.to >> edge.capacity;
    return stream;
  }

  friend std::ostream& operator<<(std::ostream& stream, const Edge& edge) {
    stream << edge.from << ' ' << edge.to << ' ' << edge.capacity << ' ' << edge.id;
    return stream;
  }
};

template <>
struct std::hash<Edge> {
  size_t operator()(const Edge& edge) const {
    return std::hash<size_t>{}(edge.id);
  }
};

// Not oriented
class Graph {
  using AdjListT = std::vector<std::vector<Edge>>;

 public:
  explicit Graph(size_t n, size_t m = 0) : adj_list_(n), count_edges_(m) {
  }

  void AddEdge(const Edge& edge) {
    adj_list_[edge.from].emplace_back(edge);
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

// func: Edge -> int
// 0 - continue
// 1 - break
// 2 - stop
void Dfs(const Graph& graph, std::function<int(Edge)> func) {
  auto n = graph.CountNodes();
  std::vector<bool> visited(n, false);

  std::function<void(const Edge&)> helper = [&](const Edge& cur_edge) {
    // visited[cur_edge.to] = true;
    auto rv = func(cur_edge);
    if (rv == 1) {
      // break
      return;
    }
    for (auto& edge : graph.GetEdges(cur_edge.to)) {
      if (!visited[edge.to]) {
        helper(edge);
      }
    }
  };

  auto helper_root = [&](NodeType root) {
    // visited[root] = true;
    for (auto& edge : graph.GetEdges(root)) {
      if (!visited[edge.to]) {
        helper(edge);
      }
    }
  };

  for (NodeType root = 0; root < n; ++root) {
    if (!visited[root]) {
      helper_root(root);
    }
  }
}

std::optional<std::vector<Edge>> FindPath(const Graph& graph, NodeType start, NodeType end,
                                          std::function<int(Edge)> func) {
  auto n = graph.CountNodes();
  std::vector<bool> visited(n, false);
  std::vector<Edge> parent(n);
  std::stack<Edge> queue;

  visited[start] = true;
  for (auto& next_edge : graph.GetEdges(start)) {
    if (visited[next_edge.to]) {
      continue;
    }
    queue.push(next_edge);
  }

  while (!queue.empty()) {
    auto cur_edge = queue.top();
    queue.pop();

    parent[cur_edge.to] = cur_edge;

    auto rv = func(cur_edge);
    if (rv == 1) {
      continue;
    }
    if (rv == 2) {
      return {};
    }

    visited[cur_edge.to] = true;

    if (cur_edge.to == end) {
      std::vector<Edge> path;
      auto cur = end;
      path.emplace_back(parent[cur]);
      while (parent[cur].from != start) {
        cur = parent[cur].from;
        path.emplace_back(parent[cur]);
      }
      return path;
    }

    for (auto& next_edge : graph.GetEdges(cur_edge.to)) {
      if (visited[next_edge.to]) {
        continue;
      }
      queue.push(next_edge);
    }
  }
  return {};
}

auto FordFulkerson(const Graph& graph, NodeType start, NodeType end) {
  auto n = graph.CountNodes();
  auto m = graph.CountEdges();

  struct Flow {
    CapacityType flow;
    CapacityType capacity;

    Flow() = default;
    Flow(CapacityType flow, CapacityType capacity) : flow(flow), capacity(capacity) {
    }
  };

  CapacityType max_flow = 0;
  std::vector<std::optional<Flow>> flow(m);
  Graph super_graph = graph;

  for (NodeType from = 0; from < n; ++from) {
    for (auto& edge : graph.GetEdges(from)) {
      auto imaginary_edge = edge.Reversed();
      imaginary_edge.id += m;
      super_graph.AddEdge(imaginary_edge);
      flow[edge.id] = {0, edge.capacity};
    }
  }

  auto get_flow = [&](Edge edge) -> Flow& { return flow[edge.id].value(); };

  auto is_real = [&](Edge edge) -> bool { return edge.id < flow.size() && flow[edge.id].has_value(); };

  auto find_real_flow = [&](Edge edge) -> Flow& {
    // std::cout << edge << '\n';
    return flow[edge.id - m].value();
  };

  auto get_excess_flow = [&](Edge edge) {
    if (is_real(edge)) {
      return get_flow(edge).capacity - get_flow(edge).flow;
    }
    return find_real_flow(edge).flow;
  };

  auto get_max_excess_flow = [&](const std::vector<Edge>& path) -> CapacityType {
    auto cmp = [&](const Edge& lhs, const Edge& rhs) { return get_excess_flow(lhs) < get_excess_flow(rhs); };
    auto max = std::min_element(path.begin(), path.end(), cmp);
    return get_excess_flow(*max);
  };

  auto push_flow = [&](Edge edge, CapacityType new_flow) {
    if (is_real(edge)) {
      get_flow(edge).flow += new_flow;
    } else {
      find_real_flow(edge).flow -= new_flow;
    }
  };

  std::vector<bool> visited(n);
  std::vector<Edge> parent(n);
  std::vector<Edge> path(m);
  auto find_path = [&]() -> std::optional<std::vector<Edge>> {
    auto& graph = super_graph;

    std::fill(visited.begin(), visited.end(), false);
    visited[start] = true;

    std::stack<Edge> stack;
    for (auto& next_edge : graph.GetEdges(start)) {
      if (visited[next_edge.to]) {
        continue;
      }
      stack.push(next_edge);
    }

    while (!stack.empty()) {
      auto cur_edge = stack.top();
      stack.pop();

      parent[cur_edge.to] = cur_edge;

      // std::cout << cur_edge << '\n';

      if (get_excess_flow(cur_edge) == 0) {
        continue;
      }

      visited[cur_edge.to] = true;

      if (cur_edge.to == end) {
        path.resize(0);
        auto cur = end;
        path.emplace_back(parent[cur]);
        while (parent[cur].from != start) {
          cur = parent[cur].from;
          path.emplace_back(parent[cur]);
        }
        return path;
      }

      for (auto& next_edge : graph.GetEdges(cur_edge.to)) {
        if (visited[next_edge.to]) {
          continue;
        }
        stack.push(next_edge);
        // if (queue.size() > m * 10) {
        //   throw std::runtime_error("queue is too big");
        // }
      }
    }
    return {};
  };

  while (true) {
    auto path = find_path();
    if (!path.has_value()) {
      break;
    }
    auto max_excess_flow = get_max_excess_flow(path.value());
    for (auto& edge : path.value()) {
      push_flow(edge, max_excess_flow);
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

  Graph graph(n, m);
  for (size_t i = 0; i < m; i++) {
    NodeType from{};
    NodeType to{};
    CapacityType capacity{};
    std::cin >> from >> to >> capacity;
    --from;
    --to;
    graph.AddEdge({from, to, capacity, i});
  }

  std::cout << '\n';

  std::cout << FordFulkerson(graph, start, end) << '\n';
  return 0;
}
