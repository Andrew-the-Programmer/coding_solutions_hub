#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_set>
#include <memory>
struct Number {
  int num;
  size_t dist;
  std::shared_ptr<Number> parent;
  Number() : num{0}, dist{0}, parent{nullptr} {};
  Number(int num, size_t dist, std::shared_ptr<Number> parent) : num{num}, dist{dist}, parent{std::move(parent)} {};
};

int Add(int n) {
  if (n / 1000 != 9) {
    return (n + 1000);
  }
  return n;
}
int Sub(int n) {
  if (n % 10 != 1) {
    return (n - 1);
  }
  return n;
}
int Right(int n) {
  return ((n / 10) + 1000 * (n % 10));
}
int Left(int n) {
  return ((n % 1000) * 10 + (n / 1000));
}

int main() {
  int s{};
  int f{};
  Number ans{};
  std::cin >> s >> f;
  std::unordered_set<int> visited;
  std::vector<int> parent;
  std::queue<Number> queue;
  visited.insert(s);
  queue.emplace(s, 0, nullptr);
  Number cur{};
  while (!queue.empty()) {
    cur = queue.front();
    queue.pop();
    if (cur.num == f) {
      ans = cur;
      break;
    }
    if (visited.count(Add(cur.num)) == 0) {
      queue.emplace(Add(cur.num), cur.dist + 1, std::make_shared<Number>(cur));
      visited.insert(Add(cur.num));
    }
    if (visited.count(Sub(cur.num)) == 0) {
      queue.emplace(Sub(cur.num), cur.dist + 1, std::make_shared<Number>(cur));
      visited.insert(Sub(cur.num));
    }
    if (visited.count(Left(cur.num)) == 0) {
      queue.emplace(Left(cur.num), cur.dist + 1, std::make_shared<Number>(cur));
      visited.insert(Left(cur.num));
    }
    if (visited.count(Right(cur.num)) == 0) {
      queue.emplace(Right(cur.num), cur.dist + 1, std::make_shared<Number>(cur));
      visited.insert(Right(cur.num));
    }
  }
  std::cout << ans.dist + 1 << "\n";
  auto print = new int[ans.dist + 1];
  size_t i = 0;
  while (ans.parent != nullptr) {
    print[i++] = ans.num;
    ans = *ans.parent;
  }
  print[i] = ans.num;
  while (i != 0) {
    std::cout << print[i] << "\n";
    --i;
  }
  std::cout << print[0];
  delete[] print;
  return 0;
}