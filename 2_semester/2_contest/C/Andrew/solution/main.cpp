// Copyright 2024 Andrew
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_set>
#include <memory>
#include <functional>

using T = int;
using ActionArrayT = std::vector<std::function<T(const T&)>>;

struct Node {
  T num;
  size_t dist;
  std::shared_ptr<Node> parent;
  Node() : num{0}, dist{0}, parent{nullptr} {};
  Node(int num, size_t dist, std::shared_ptr<Node> parent) : num{num}, dist{dist}, parent{std::move(parent)} {};
};

T Add(T n) {
  if (n / 1000 != 9) {
    return (n + 1000);
  }
  return n;
}
T Sub(T n) {
  if (n % 10 != 1) {
    return (n - 1);
  }
  return n;
}
T Right(T n) {
  return (1000 * (n % 10) + (n / 10));
}
T Left(T n) {
  return ((n % 1000) * 10 + (n / 1000));
}

void Solution(T start, T finish, ActionArrayT actions) {
  Node ans{};
  std::unordered_set<T> visited;
  std::queue<Node> queue;
  visited.insert(start);
  queue.emplace(start, 0, nullptr);
  Node cur{};
  while (!queue.empty()) {
    cur = queue.front();
    queue.pop();
    if (cur.num == finish) {
      ans = cur;
      break;
    }
    for (auto&& action : actions) {
      auto next = action(cur.num);
      if (!visited.contains(next)) {
        queue.emplace(next, cur.dist + 1, std::make_shared<Node>(cur));
        visited.insert(next);
      }
    }
  }
  // Output final dist
  std::cout << ans.dist + 1 << "\n";

  // Output path start -> finish
  std::vector<T> path;
  cur = ans;
  while (cur.parent != nullptr) {
    path.push_back(cur.num);
    cur = *cur.parent;
  }
  path.push_back(start);
  for (auto it = path.rbegin(); it != path.rend(); it++) {
    std::cout << *it << "\n";
  }
}

int main() {
  T start{};
  T finish{};
  std::cin >> start >> finish;
  ActionArrayT actions{Add, Sub, Left, Right};
  Solution(start, finish, actions);
  return 0;
}
