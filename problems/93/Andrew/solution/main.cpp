#include <iostream>
#include <algorithm>
#include <vector>
struct Edge {
  int64_t fr;
  int64_t to;
  int64_t wght;
  Edge(const int64_t& from, const int64_t& to, const int64_t& weight) : fr(from), to(to), wght(weight) {
  }
  friend bool operator<(const Edge& first, const Edge& second) {
    return ((first.wght < second.wght) || ((first.wght == second.wght) && (first.fr < second.fr)) ||
            ((first.wght == second.wght) && (first.fr == second.fr) && (first.to < second.to)));
  }
  Edge() = default;
};
class DSU {
 public:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
  void MakeSet(int64_t vertex);
  int64_t FindSet(int64_t vertex);
  void Union(int64_t first_vertex, int64_t second_vertex);
  explicit DSU(const int64_t quantity_vert) {
    parent_.resize(quantity_vert);
    rank_.resize(quantity_vert);
    for (int64_t i = 0; i < quantity_vert; i++) {
      MakeSet(i);
    }
  }
  DSU() = default;
};
class Graph {
 public:
  std::vector<Edge> edg;
  DSU dsu;
  explicit Graph(const int64_t quantity_vertexes) {
    dsu = DSU(quantity_vertexes);
  }
  int64_t Kruskal();
  void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight);
};
void DSU::MakeSet(const int64_t vertex) {
  parent_[vertex] = vertex;
  rank_[vertex] = 1;
}
int64_t DSU::FindSet(const int64_t vertex) {
  if (vertex == parent_[vertex]) {
    return vertex;
  }
  return parent_[vertex] = FindSet((parent_[vertex]));
}
void DSU::Union(int64_t first_vertex, int64_t second_vertex) {
  first_vertex = FindSet(first_vertex);
  second_vertex = FindSet(second_vertex);
  if (rank_[first_vertex] < rank_[second_vertex]) {
    parent_[first_vertex] = second_vertex;
  } else if (rank_[first_vertex] > rank_[second_vertex]) {
    parent_[second_vertex] = first_vertex;
  } else {
    parent_[first_vertex] = second_vertex;
    rank_[second_vertex]++;
  }
}
void Graph::PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
  edg.emplace_back(first_vert, second_vert, weight);
}
int64_t Graph::Kruskal() {
  std::sort(edg.begin(), edg.end());
  int64_t wghtmst = 0;
  for (auto& edge : edg) {
    if (dsu.FindSet(edge.fr) != dsu.FindSet(edge.to)) {
      dsu.Union(edge.fr, edge.to);
      wghtmst += edge.wght;
    }
  }
  return wghtmst;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int64_t quantity_vertexes{};
  std::cin >> quantity_vertexes;
  Graph graph(quantity_vertexes + 1);
  int64_t weight{};
  for (int64_t i = 0; i < quantity_vertexes; i++) {
    for (int64_t j = 0; j < quantity_vertexes; j++) {
      std::cin >> weight;
      if (i < j) {
        graph.PushEdge(i, j, weight);
      }
    }
  }
  for (int64_t j{}; j < quantity_vertexes; j++) {
    std::cin >> weight;
    graph.PushEdge(quantity_vertexes, j, weight);
  }
  const int64_t min_weight = graph.Kruskal();
  std::cout << min_weight;
  return 0;
}