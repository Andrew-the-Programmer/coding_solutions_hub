#include <iostream>
#include <stack>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> graph_reversed;
std::vector<int> components;
std::vector<bool> visited;
std::stack<int> dfs_stack;

void Dfs1(int u) {
  visited[u] = true;
  for (int v : graph[u]) {
    if (!visited[v]) {
      Dfs1(v);
    }
  }
  dfs_stack.push(u);
}

void Dfs2(int u, int component) {
  visited[u] = true;
  components[u] = component;
  for (int v : graph_reversed[u]) {
    if (!visited[v]) {
      Dfs2(v, component);
    }
  }
}

int main() {
  int n{};
  int m{};
  std::cin >> n >> m;
  graph.resize(n);
  graph_reversed.resize(n);
  visited.assign(n, false);
  components.assign(n, 0);

  for (int i = 0; i < m; i++) {
    int u{};
    int v{};
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
    graph_reversed[v - 1].push_back(u - 1);
  }

  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      Dfs1(i);
    }
  }

  visited.assign(n, false);
  int component_count = 0;
  while (!dfs_stack.empty()) {
    int u = dfs_stack.top();
    dfs_stack.pop();
    if (!visited[u]) {
      component_count++;
      Dfs2(u, component_count);
    }
  }

  std::cout << component_count << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << components[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
