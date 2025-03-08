#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <map>

struct Node {
  std::weak_ptr<Node> suf;
  int64_t length;
  std::map<char, std::shared_ptr<Node>> sons;
  int64_t num;
  Node() : suf(), length(0), sons(), num(0){};
  explicit Node(int64_t len, int64_t num) : suf(), length(len), sons(), num(num){};
  Node(const Node& other) = default;
};

struct SuffixAutomaton {
  std::shared_ptr<Node> root;
  int64_t size;
  SuffixAutomaton() : root(std::make_shared<Node>()), size(1){};

  void Build(const std::string& str) {
    std::shared_ptr<Node> last = root;
    for (int64_t i = 0; i < static_cast<int64_t>(str.size()); ++i) {
      char symb = str[i];
      std::shared_ptr<Node> curr(new Node(i + 1, size));
      ++size;
      while (last != root && last->sons[symb] == nullptr) {
        last->sons[symb] = curr;
        last = last->suf.lock();
      }
      if (last == root && last->sons[symb] == nullptr) {
        last->sons[symb] = curr;
        curr->suf = last;
        last = curr;
        continue;
      }
      last->sons.insert({symb, nullptr});
      auto q = last->sons[symb];
      if (q->length - 1 == last->length) {
        curr->suf = q;
        last = curr;
        continue;
      }
      std::shared_ptr<Node> copy(new Node(*q));
      copy->num = size;
      ++size;
      copy->length = last->length + 1;
      curr->suf = copy;
      q->suf = copy;
      while (last != nullptr && last->sons[symb] == q) {
        last->sons[symb] = copy;
        last = last->suf.lock();
      }
      last = curr;
    }
  }
};

void BFS(const SuffixAutomaton& suf_auto) {
  std::queue<std::shared_ptr<Node>> queue;
  std::vector<bool> visited(suf_auto.size, false);
  queue.push(suf_auto.root);
  while (!queue.empty()) {
    auto curr = queue.front();
    queue.pop();
    if (!visited[curr->num]) {
      for (const auto& [symb, value] : curr->sons) {
        queue.push(curr->sons[symb]);
        std::cout << curr->num << " " << symb << " " << curr->sons[symb]->num << '\n';
      }
      visited[curr->num] = true;
    }
  }
}

int main() {
  std::string str;
  std::cin >> str;
  SuffixAutomaton suf_auto;
  suf_auto.Build(str);
  std::cout << suf_auto.size << '\n';
  BFS(suf_auto);
}
