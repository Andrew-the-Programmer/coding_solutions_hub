#include <set>
#include <vector>
#include <functional>
#include <iostream>

struct Edge {
  int64_t vrt;
  int64_t wt;

  Edge(const int64_t& vrt, const int64_t& weight) : vrt(vrt), wt(weight) {
  }

  Edge() = default;

  friend bool operator<(const Edge& first, const Edge& second) {
    return ((first.wt < second.wt) || ((first.wt == second.wt) && (first.vrt < second.vrt)));
  }
};

class Graph {
 public:
  explicit Graph(const int64_t& new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    edg.resize(quantity_vert_ + 1);
    dist.resize(quantity_vert_ + 1, k_max_dist);
    prev.resize(quantity_vert_ + 1, -1);
    used.resize(quantity_vert_ + 1, false);
  }

  void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight);
  int64_t Prim();
  const int64_t k_max_dist = 10000000;
  std::vector<std::vector<Edge>> edg;
  int64_t quantity_vert_;
  std::vector<int64_t> prev;
  std::vector<int64_t> dist;
  std::vector<bool> used;
};

void Graph::PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
  edg[first_vert].emplace_back(second_vert, weight);
  edg[second_vert].emplace_back(first_vert, weight);
}

int64_t Graph::Prim() {
  int64_t wtmst{};
  std::set<Edge> set_vrtes;
  dist[1] = 0;
  for (int64_t i = 1; i <= quantity_vert_; i++) {
    set_vrtes.insert(Edge(i, dist[i]));
  }
  while (!set_vrtes.empty()) {
    auto new_vrt = *set_vrtes.begin();
    set_vrtes.erase(set_vrtes.begin());
    used[new_vrt.vrt] = true;
    if (prev[new_vrt.vrt] != -1) {
      wtmst += new_vrt.wt;
    }
    for (auto& edge : edg[new_vrt.vrt]) {
      if ((!used[edge.vrt]) && (edge.wt < dist[edge.vrt])) {
        set_vrtes.erase(Edge(edge.vrt, dist[edge.vrt]));
        set_vrtes.insert(Edge(edge.vrt, edge.wt));
        prev[edge.vrt] = new_vrt.vrt;
        dist[edge.vrt] = edge.wt;
      }
    }
  }
  return wtmst;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vrtes{};
  int64_t quantity_edges{};
  std::cin >> quantity_vrtes >> quantity_edges;
  Graph graph(quantity_vrtes);
  int64_t first_vert{};
  int64_t second_vert{};
  int64_t weight{};
  for (int64_t i = 1; i <= quantity_edges; i++) {
    std::cin >> first_vert >> second_vert >> weight;
    graph.PushEdge(first_vert, second_vert, weight);
  }
  int64_t min_weight = graph.Prim();
  std::cout << min_weight;
  return 0;
}
