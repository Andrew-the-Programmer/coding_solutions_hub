// #include <iostream>
// #include <queue>
// #include <vector>
// using G = std::vector<std::vector<std::pair<int, bool>>>;
//
// bool Bfs(const G &graph, int start, int target, bool color) {
//   std::vector<bool> visited(graph.size(), false);
//   std::queue<int> q;
//   q.push(start);
//   visited[start] = true;
//   while (!q.empty()) {
//     int current = q.front();
//     q.pop();
//     if (current == target) {
//       return true;
//     }
//     for (auto &i : graph[current]) {
//       if (!visited[i.first] && i.second == color) {
//         visited[i.first] = true;
//         q.push(i.first);
//       }
//     }
//   }
//   return false;
// }
//
// int main() {
//   std::ios_base::sync_with_stdio(false);
//   std::cin.tie(nullptr);
//   std::cout.tie(nullptr);
//   std::cout.setf(std::ios::fixed);
//   std::cout.precision(10);
//   int n{};
//   std::cin >> n;
//   char l{};
//   G graph(n);
//   for (int i = 0; i < n - 1; ++i) {
//     for (int j = 0; j < n - i - 1; ++j) {
//       std::cin >> l;
//       if (l == 'R') {
//         graph[i].emplace_back(i + j + 1, true);
//       } else {
//         graph[i].emplace_back(i + j + 1, false);
//       }
//     }
//   }
//   for (int i = 0; i < n - 1; ++i) {
//     for (int j = i + 1; j < n; ++j) {
//       if (Bfs(graph, i, j, true) && Bfs(graph, i, j, false)) {
//         std::cout << "NO";
//         return 0;
//       }
//     }
//   }
//   std::cout << "YES";
//   return 0;
// }

// #include <algorithm>
// #include <iostream>
// #include <vector>
// #include <set>
//
// using G = std::vector<std::vector<std::pair<int, bool>>>;
// using A = std::vector<std::pair<std::set<int>, std::set<int>>>;
//
// bool HasIntersection(const std::set<int> &v1, const std::set<int> &v2) {
//   std::vector<int> intersection{};
//   set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
//   back_inserter(intersection)); return !intersection.empty();
// }
//
// void Dfs(const G &graph, int current, bool color, std::vector<bool> &visited,
// std::set<int> &avail) {
//   visited[current] = true;
//   for (const auto &neighbor : graph[current]) {
//     if (!visited[neighbor.first] && neighbor.second == color) {
//       avail.emplace(neighbor.first);
//       Dfs(graph, neighbor.first, color, visited, avail);
//     }
//   }
// }
//
// int main() {
//   std::ios_base::sync_with_stdio(false);
//   std::cin.tie(nullptr);
//   std::cout.tie(nullptr);
//   std::cout.setf(std::ios::fixed);
//   std::cout.precision(10);
//   int n{};
//   std::cin >> n;
//   char l{};
//   G graph(n);
//   for (int i = 0; i < n - 1; ++i) {
//     for (int j = 0; j < n - i - 1; ++j) {
//       std::cin >> l;
//       if (l == 'R') {
//         graph[i].emplace_back(i + j + 1, true);
//       } else {
//         graph[i].emplace_back(i + j + 1, false);
//       }
//     }
//   }
//
//   A avail(n);
//
//   for (int i = 0; i < n - 1; ++i) {
//     std::vector<bool> visited1(n, false);
//     std::vector<bool> visited2(n, false);
//     Dfs(graph, i, true, visited1, avail[i].first);
//     Dfs(graph, i, false, visited2, avail[i].second);
//   }
//
//   for (auto &i : avail) {
//     if (i.first.empty() || i.second.empty()) {
//       continue;
//     }
//     if (HasIntersection(i.first, i.second)) {
//       std::cout << "NO";
//       return 0;
//     }
//   }
//
//   std::cout << "YES";
//   return 0;
// }

// #include <iostream>
// #include <vector>
//
// using G = std::vector<std::vector<std::pair<int, bool>>>;
//
// void Dfs(const G &graph, int current, bool color, std::vector<bool> &visited,
// std::vector<bool> &avail) {
//   visited[current] = true;
//   for (const auto &neighbor : graph[current]) {
//     if (!visited[neighbor.first] && neighbor.second == color) {
//       avail[neighbor.first] = true;
//       Dfs(graph, neighbor.first, color, visited, avail);
//     }
//   }
// }
//
// int main() {
//   std::ios_base::sync_with_stdio(false);
//   std::cin.tie(nullptr);
//   std::cout.tie(nullptr);
//   std::cout.setf(std::ios::fixed);
//
//   int n{};
//   std::cin >> n;
//   char l{};
//   G graph(n);
//   for (int i = 0; i < n - 1; ++i) {
//     for (int j = 0; j < n - i - 1; ++j) {
//       std::cin >> l;
//       if (l == 'R') {
//         graph[i].emplace_back(i + j + 1, true);
//       } else {
//         graph[i].emplace_back(i + j + 1, false);
//       }
//     }
//   }
//
//   std::vector<std::vector<bool>> red(n);
//   std::vector<std::vector<bool>> blue(n);
//   for (int i = 0; i < n; ++i) {
//     red[i].resize(n);
//     for (int j = 0; j < n; ++j) {
//       red[i][j] = false;
//     }
//   }
//   for (int i = 0; i < n; ++i) {
//     blue[i].resize(n);
//     for (int j = 0; j < n; ++j) {
//       blue[i][j] = false;
//     }
//   }
//   for (int i = 0; i < n - 1; ++i) {
//     std::vector<bool> visited1(n, false);
//     std::vector<bool> visited2(n, false);
//     Dfs(graph, i, true, visited1, red[i]);
//     Dfs(graph, i, false, visited2, blue[i]);
//   }
//
//   for (int i = 0; i < n; ++i) {
//     for (int j = i + 1; j < n; ++j) {
//       if (red[i][j] && blue[i][j]) {
//         std::cout << "NO";
//         return 0;
//       }
//     }
//   }
//   std::cout << "YES";
//   return 0;
// }
#include <iostream>
#include <stack>
#include <vector>

bool Cycle(int v, std::vector<std::vector<int>> &adj, std::vector<bool> &visited, std::vector<bool> &inst) {
  if (!visited[v]) {
    visited[v] = true;
    inst[v] = true;

    for (int neighbor : adj[v]) {
      if (!visited[neighbor] && Cycle(neighbor, adj, visited, inst)) {
        return true;
      }
      if (inst[neighbor]) {
        return true;
      }
    }
  }
  inst[v] = false;
  return false;
}

bool Mono(int n, const std::vector<std::vector<char>> &edges) {
  std::vector<std::vector<int>> adj(n);

  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (edges[i][j] == 'B') {
        adj[i].push_back(i + j + 1);
      } else {
        adj[i + j + 1].push_back(i);
      }
    }
  }

  std::vector<bool> visited(n, false);
  std::vector<bool> inst(n, false);

  for (int i = 0; i < n; ++i) {
    if (Cycle(i, adj, visited, inst)) {
      return false;
    }
  }

  return true;
}

int main() {
  int n{};
  std::cin >> n;
  std::vector<std::vector<char>> edges(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    edges[i].resize(n - i - 1);
    for (int j = 0; j < n - i - 1; ++j) {
      std::cin >> edges[i][j];
    }
  }
  if (Mono(n, edges)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}