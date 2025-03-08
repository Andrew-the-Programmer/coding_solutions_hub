#include <iostream>
#include <map>
#include <memory>
#include <array>

struct Node {
  std::weak_ptr<Node> suf;
  int64_t length;
  std::array<std::shared_ptr<Node>, 256> sons;
  int64_t num;
  Node() : suf(), length(0), sons(), num(0){};
  explicit Node(int64_t len, int64_t num) : suf(), length(len), sons(), num(num){
    sons.fill(nullptr);
  };
  Node(const Node& other) = default;
};

struct SuffixAutomaton {
  std::shared_ptr<Node> root;
  int64_t size;
  std::shared_ptr<Node> last;
  SuffixAutomaton() : root(std::make_shared<Node>()), size(1), last(root){};

  void Build(const std::string& str) {
    // last = root;
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
      // last->sons[symb] = nullptr;
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

  bool Find(int64_t length) {
    if (!last || last->suf.expired()) {
      return false;
    }
    auto suf = last->suf.lock();
    if (!suf) {
      return false;
    }
    return suf->length < length;
  }
};

int main() {
  size_t n = 0;
  std::cin >> n;
  char command = 0;
  std::string symbol;
  int64_t length = 0;
  SuffixAutomaton suf_auto;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> command;
    if (command == '+') {
      std::cin >> symbol;
      suf_auto.Build(symbol);
      continue;
    }
    if (command == '?') {
      std::cin >> length;
      if (suf_auto.Find(length)) {
        std::cout << '+' << '\n';
      } else {
        std::cout << '-' << '\n';
      }
    }
  }
}
