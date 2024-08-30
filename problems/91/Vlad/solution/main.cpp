#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
struct Edge {
  int64_t fr;
  int64_t to;
  int64_t wght;
  Edge() = default;
  Edge(const int64_t& from, const int64_t& to, const int64_t& wght) : fr(from), to(to), wght(wght) {
  }
};
class DSU {
 public:
  void MakeSet(int64_t vertex);
  int64_t FindSet(int64_t vertex);
  void Union(int64_t first_vertex, int64_t second_vertex);
  explicit DSU(int64_t quantity_vert) {
    prnt.resize(quantity_vert + 1);
    rk.resize(quantity_vert + 1);
    for (int64_t i = 0; i < quantity_vert; ++i) {
      MakeSet(i);
    }
  }
  DSU() = default;
  std::vector<int64_t> prnt;
  std::vector<int64_t> rk;
};
class Graph {
 public:
  explicit Graph(int64_t quantity_vertexes) {
    dsu = DSU(quantity_vertexes);
  }
  int64_t Kruskal();
  void PushEdge(int64_t first_vert, int64_t second_vert, int64_t wght);
  std::vector<Edge> ed;
  DSU dsu;
};
void DSU::MakeSet(int64_t vertex) {
  prnt[vertex] = vertex;
  rk[vertex] = 1;
}
int64_t DSU::FindSet(int64_t vertex) {
  if (vertex == prnt[vertex]) {
    return vertex;
  }
  return prnt[vertex] = FindSet((prnt[vertex]));
}
void DSU::Union(int64_t first_vertex, int64_t second_vertex) {
  first_vertex = FindSet(first_vertex);
  second_vertex = FindSet(second_vertex);
  if (rk[first_vertex] < rk[second_vertex]) {
    prnt[first_vertex] = second_vertex;
  } else if (rk[first_vertex] > rk[second_vertex]) {
    prnt[second_vertex] = first_vertex;
  } else {
    prnt[first_vertex] = second_vertex;
    rk[second_vertex] += 1;
  }
}
void Graph::PushEdge(int64_t first_vert, int64_t second_vert, int64_t wght) {
  ed.emplace_back(first_vert, second_vert, wght);
}
int64_t Graph::Kruskal() {
  int64_t wghtmst{};
  for (auto& edge : ed) {
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
  int64_t quantity_edges{};
  int64_t quantity_vertexes{};
  int64_t first_vert{};
  int64_t second_vert{};
  int64_t wght{};
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  for (int64_t i = 0; i < quantity_edges; i++) {
    std::cin >> first_vert >> second_vert >> wght;
    graph.PushEdge(first_vert, second_vert, wght);
  }
  int64_t min_wght = graph.Kruskal();
  std::cout << min_wght;
  return 0;
}