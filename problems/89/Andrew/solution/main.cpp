#include <iostream>
#include <vector>

struct Node {
  int parent{};
  int rank{};
  int weight{};
};

int Find(std::vector<Node> &nodes, int x) {
  if (nodes[x].parent != x) {
    nodes[x].parent = Find(nodes, nodes[x].parent);
  }
  return nodes[x].parent;
}
void Unite(std::vector<Node> &nodes, int x, int y, int w) {
  int root_x = Find(nodes, x);
  int root_y = Find(nodes, y);

  if (root_x == root_y) {
    return;
  }

  if (nodes[root_x].rank < nodes[root_y].rank) {
    std::swap(root_x, root_y);
  } else if (nodes[root_x].rank == nodes[root_y].rank) {
    nodes[root_x].rank++;
  }
  nodes[root_y].parent = root_x;
  nodes[root_x].weight += nodes[root_y].weight + w;
}

int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  std::vector<Node> nodes(n + 1);
  for (int i = 1; i <= n; ++i) {
    nodes[i].parent = i;
    nodes[i].rank = 0;
    nodes[i].weight = 0;
  }

  for (int i = 0; i < m; ++i) {
    int operation{};
    std::cin >> operation;

    if (operation == 1) {
      int x{};
      int y{};
      int w{};
      std::cin >> x >> y >> w;
      Unite(nodes, x, y, w);
    } else if (operation == 2) {
      int x{};
      std::cin >> x;
      int root_x = Find(nodes, x);
      std::cout << nodes[root_x].weight << std::endl;
    }
  }
  return 0;
}
