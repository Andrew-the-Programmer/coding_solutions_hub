// Copyright 2024 Andrew

#include <cstddef>
#include <iostream>
#include <optional>
#include <set>
#include <vector>
#include <utility>
#include <queue>

template <class T>
struct Edge {
  T src;
  T dst;

  Edge() = default;

  template <class TT>
  friend std::ostream& operator<<(std::ostream& os, const Edge<TT>& edge) {
    os << edge.src << " -> " << edge.dst;
    return os;
  }

  template <class TT>
  friend std::istream& operator>>(std::istream& stream, Edge<TT>& edge) {
    std::cin >> edge.src >> edge.dst;
    return stream;
  }
};

struct Graph : public std::vector<std::set<size_t>> {
 protected:
  using Base = std::vector<std::set<size_t>>;
  using Base::Base;

 public:
  using VertexType = size_t;
  using EdgeType = Edge<size_t>;

 public:
  explicit Graph(std::vector<EdgeType> edges) {
    for (auto&& edge : edges) {
      AddEdge(edge);
    }
  }

 public:
  const auto& Neighbors(VertexType v) const {
    return this->at(v);
  }

  void AddNeighbor(VertexType src, VertexType dst) {
    this->at(src).emplace(dst);
  }

  void AddEdge(EdgeType edge) {
    AddNeighbor(edge.src, edge.dst);
    AddNeighbor(edge.dst, edge.src);
  }

 public:
  // func: (VertexType, VertexType) -> bool
  // if func returns false, BFS stops
  template <class Func>
    requires requires(Func func, VertexType v1, VertexType v2) {
      { func(v1, v2) } -> std::same_as<bool>;
    }
  void BFS(VertexType start, Func func) const {
    std::vector<bool> visited(this->size(), false);
    visited[start] = true;

    std::deque<VertexType> queue{start};
    while (!queue.empty()) {
      auto cur = queue.front();
      queue.pop_front();
      for (auto&& neighbor : this->Neighbors(cur)) {
        if (visited[neighbor]) {
          continue;
        }
        visited[neighbor] = true;
        if (!func(cur, neighbor)) {
          return;
        }
        queue.emplace_back(neighbor);
      }
    }
  }

 public:
  // return: pair(distance: optional<size_t>, path: vector<VertexType>)
  std::pair<std::optional<size_t>, std::vector<VertexType>> Distance(VertexType start, VertexType end) const {
    using DistType = size_t;

    std::vector<std::optional<DistType>> dist(this->size());
    dist[start] = 0;
    std::vector<std::optional<VertexType>> parent(this->size());

    auto func = [&dist, &end, &parent](VertexType s, VertexType v) -> bool {
      dist[v] = dist[s].value() + 1;
      parent[v] = s;
      return v != end;
    };

    BFS(start, func);

    if (!dist[end].has_value()) {
      return {};
    }

    std::vector<VertexType> path;
    path.reserve(this->size());

    for (auto cur = end; cur != start; cur = parent[cur].value()) {
      path.emplace_back(cur);
    }
    path.emplace_back(start);

    return {dist[end], {path.rbegin(), path.rend()}};
  }
};

void Solution(const Graph& graph, Graph::VertexType start, Graph::VertexType end) {
  auto result = graph.Distance(start, end);

  if (!result.first.has_value()) {
    std::cout << "-1\n";
    return;
  }

  std::cout << result.first.value() << "\n";
  for (auto&& v : result.second) {
    std::cout << v << " ";
  }
  std::cout << "\n";
}

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;

  size_t a = 0;
  size_t b = 0;
  std::cin >> a >> b;

  Graph graph(n + 1);
  for (size_t i = 0; i < m; ++i) {
    Edge<size_t> edge;
    std::cin >> edge;
    graph.AddEdge(edge);
  }

  Solution(graph, a, b);
}
