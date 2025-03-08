#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <vector>

struct Node {
  std::weak_ptr<Node> suf;
  int64_t length;
  std::map<char, std::shared_ptr<Node>> sons;
  int64_t num;
  int64_t pref;
  Node() : suf(), length(0), sons(), num(0), pref(0){};
  explicit Node(int64_t len, int64_t num) : suf(), length(len), sons(), num(num), pref(0){};
  Node(const Node& other) = default;
};

struct SuffixAutomaton {
  std::shared_ptr<Node> root;
  int64_t size;
  std::shared_ptr<Node> last;
  SuffixAutomaton() : root(std::make_shared<Node>()), size(1), last(root){};

  std::shared_ptr<Node> GetSon(std::shared_ptr<Node> node, char symb) {
    if (!node->sons.contains(symb)) {
      return nullptr;
    }
    return node->sons[symb];
  }

  void Build(const std::string& str) {
    for (int64_t i = 0; i < static_cast<int64_t>(str.size()); ++i) {
      char symb = str[i];
      std::shared_ptr<Node> curr(new Node(last->length + 1, size));
      ++size;
      auto node = last;
      while (node != root && GetSon(node, symb) == nullptr) {
        node->sons[symb] = curr;
        node = node->suf.lock();
      }
      if (node == root && GetSon(node, symb) == nullptr) {
        node->sons[symb] = curr;
        curr->suf = node;
      } else {
        auto q = node->sons[symb];
        if (q->length - 1 == node->length) {
          curr->suf = q;
        } else {
          std::shared_ptr<Node> copy(new Node(*q));
          copy->num = size;
          ++size;
          copy->length = node->length + 1;
          curr->suf = copy;
          q->suf = copy;
          while (node != nullptr && GetSon(node, symb) == q) {
            node->sons[symb] = copy;
            node = node->suf.lock();
          }
        }
      }
      if (curr == nullptr) {
        std::cout << "curr\n";
      }
      if (last == nullptr) {
        std::cout << "last\n";
      }
      if (curr->suf.lock() == nullptr) {
        std::cout << "suf\n";
      }
      curr->pref = curr->length + last->pref - curr->suf.lock()->length;
      std::cout << curr->pref << '\n';
      last = curr;
    }
  }

  bool Find(int64_t length) {
    if (!last || last->suf.expired()) {
      return false;
    }
    if (!last->suf.lock()) {
      return false;
    }
    return last->suf.lock()->length < length;
  }
};

int main() {
  std::string str;
  std::cin >> str;
  SuffixAutomaton suf_auto;
  suf_auto.Build(str);
}
