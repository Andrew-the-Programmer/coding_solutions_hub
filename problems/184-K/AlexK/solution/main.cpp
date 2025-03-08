#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

struct Node {
  std::map<char, Node*> sons;
  Node* suf;
  size_t length = 0;
  char state;
  Node() = default;
  explicit Node(size_t length) : length(length) {
  }
};

struct SuffixAutomaton {
  Node* root;
  Node* last;
  SuffixAutomaton() : root(new Node), last(root){};

  void Build(const std::string& str) {
    for (auto symb : str) {
      auto curr = new Node(last->length + 1);
      auto node = last;
      while (node != root && node->sons[symb] == nullptr) {
        node->sons[symb] = curr;
        node = node->suf;
      }
      if (node == root && node->sons[symb] == nullptr) {
        node->sons[symb] = curr;
        curr->suf = node;
      } else {
        auto q = node->sons[symb];
        if (q->length - 1 == node->length) {
          curr->suf = q;
        } else {
          auto copy = new Node(*q);
          // std::shared_ptr<Node> copy(new Node(*q));
          copy->length = node->length + 1;
          curr->suf = copy;
          q->suf = copy;
          while (node != nullptr && node->sons[symb] == q) {
            node->sons[symb] = copy;
            node = node->suf;
          }
        }
      }
      last = curr;
    }
  }

  ~SuffixAutomaton() {
    if (!root) {
      return;
    }
    std::stack<Node*> stack;
    stack.push(root);
    std::map<Node*, bool> visited;
    while (!stack.empty()) {
      auto curr = stack.top();
      stack.pop();
      for (auto& [symb, son] : curr->sons) {
        if (son && !visited[son]) {
          visited[son] = true;
          stack.push(son);
        }
      }
      delete curr;
    }
  }
};

int main() {
  int64_t n = 0;
  int64_t k = 0;
  std::string str;
  str.reserve(n);
  std::cin >> n >> k >> str;
  SuffixAutomaton suf_auto;
  suf_auto.Build(str);

  std::function<size_t(Node*)> find_way = [k, &find_way](Node* root) -> size_t {
    auto curr = root;
    size_t min_length = 0;
    size_t next_length = 0;
    char best_symbol = 0;
    for (char s = 'a'; s < 'a' + k; ++s) {
      auto next = curr->sons[s];
      if (!next) {
        curr->state = s;
        return 1;
      }
      next_length = find_way(next);
      if (min_length == 0 || next_length < min_length) {
        min_length = next_length;
        best_symbol = s;
      }
    }
    curr->state = best_symbol;
    return 1 + min_length;
  };

  find_way(suf_auto.root);
  std::string password;
  password.reserve(n);
  auto curr = suf_auto.root;
  while (curr) {
    auto s = curr->state;
    password += s;
    curr = curr->sons[s];
  }
  std::cout << password << '\n';
}
