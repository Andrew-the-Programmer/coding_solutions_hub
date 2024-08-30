#include <algorithm>
#include <iostream>
#include <vector>
struct Edge {
  int64_t fr;
  int64_t to;
  int64_t wght;
  Edge() = default;
  Edge(const int64_t& from, const int64_t& to, const int64_t& weight) : fr(from), to(to), wght(weight) {
  }
};
class DSU {
 public:
  std::vector<int64_t> prnt;
  std::vector<int64_t> rk;
  int64_t quantity_components_;
  void MakeSet(int64_t vertex);
  int64_t SetCount() const;
  int64_t FindSet(int64_t vertex);
  bool Union(int64_t first_vertex, int64_t second_vertex);
  explicit DSU(int64_t quantity_vert) : quantity_components_(quantity_vert) {
    prnt.resize(quantity_vert);
    rk.resize(quantity_vert);
    for (int64_t i = 0; i < quantity_vert; i++) {
      MakeSet(i);
    }
  }
  DSU() = default;
};
class Graph {
 public:
  explicit Graph(int64_t quantity_vertexes) : vert_amoun(quantity_vertexes) {
    dsu = DSU(quantity_vertexes);
  }
  int64_t Boruvka();
  void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight);
  std::vector<Edge> edges_;
  int64_t vert_amoun;
  DSU dsu;
  int64_t k_max_wght = 10000000000;
};
void DSU::MakeSet(const int64_t vertex) {
  prnt[vertex] = vertex;
  rk[vertex] = 1;
}
int64_t DSU::FindSet(const int64_t vertex) {
  if (vertex == prnt[vertex]) {
    return vertex;
  }
  return prnt[vertex] = FindSet((prnt[vertex]));
}
int64_t DSU::SetCount() const {
  return quantity_components_;
}
bool DSU::Union(int64_t first_vertex, int64_t second_vertex) {
  first_vertex = FindSet(first_vertex);
  second_vertex = FindSet(second_vertex);
  if (first_vertex == second_vertex) {
    return false;
  }
  if (rk[first_vertex] < rk[second_vertex]) {
    prnt[first_vertex] = second_vertex;
  } else if (rk[first_vertex] > rk[second_vertex]) {
    prnt[second_vertex] = first_vertex;
  } else {
    prnt[first_vertex] = second_vertex;
    rk[second_vertex] += 1;
  }
  --quantity_components_;
  return true;
}
void Graph::PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
  edges_.emplace_back(first_vert, second_vert, weight);
}
int64_t Graph::Boruvka() {
  int64_t wghtmst{};
  while (dsu.SetCount() > 1) {
    std::vector<Edge> min_edge;
    min_edge.resize(vert_amoun, Edge(-1, -1, k_max_wght));
    for (auto& edge : edges_) {
      int64_t component_from = dsu.FindSet(edge.fr);
      int64_t component_to = dsu.FindSet(edge.to);
      if (component_from != component_to) {
        if (edge.wght < min_edge[component_to].wght) {
          min_edge[component_to] = edge;
        }
        if (edge.wght < min_edge[component_from].wght) {
          min_edge[component_from] = edge;
        }
      }
    }
    for (auto& edge : min_edge) {
      if (edge.fr == -1) {
        continue;
      }
      if (dsu.Union(edge.fr, edge.to)) {
        wghtmst += edge.wght;
      }
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
  int64_t quantity_edges{};
  int64_t quantity_vertexes{};
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  int64_t first_vert{};
  int64_t second_vert{};
  int64_t weight{};
  for (int64_t i = 0; i < quantity_edges; i++) {
    std::cin >> first_vert >> second_vert >> weight;
    graph.PushEdge(first_vert - 1, second_vert - 1, weight);
  }
  int64_t min_weight = graph.Boruvka();
  std::cout << min_weight;
  return 0;
}