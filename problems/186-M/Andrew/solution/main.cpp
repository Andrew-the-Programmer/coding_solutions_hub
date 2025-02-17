// Copyright 2024 Andrew

#include <cstddef>
#include <tuple>
#include <map>
#include <array>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

using SymbolType = size_t;
// constexpr size_t kAlphabetPower = 26;
constexpr char kStartSymbol = 'a';

SymbolType CharToSymbol(char c) {
  return static_cast<SymbolType>(c - kStartSymbol);
}

char SymbolToChar(SymbolType i) {
  return static_cast<char>(kStartSymbol + i);
}

class Ptr {
  using T = int;

 public:
  T index;

 public:
  explicit Ptr(size_t i) : index(static_cast<T>(i)) {
  }
  Ptr() : index(-1) {
  }
  Ptr(std::nullptr_t) : Ptr() {  // NOLINT
  }

  bool operator==(std::nullptr_t) const {
    return index < 0;
  }
  bool operator!=(std::nullptr_t) const {
    return !(*this == nullptr);
  }
  operator bool() const {  // NOLINT
    return *this != nullptr;
  }
  explicit operator int() const {
    return index;
  }
  friend auto& operator<<(std::ostream& os, const Ptr& ptr) {
    os << ptr.index;
    return os;
  }
  bool operator==(Ptr other) const {
    return index == other.index;
  }
  bool operator!=(Ptr other) const {
    return !(*this == other);
  }
};

struct Trie {
 protected:
  struct Node {
    using PointerType = Ptr;
    using LinkType = Ptr;
    using LengthType = size_t;
    using LR = std::tuple<LengthType, LengthType, LengthType>;

    // std::array<PointerType, kAlphabetPower> children;
    std::map<SymbolType, PointerType> children;
    LinkType link = PointerType(nullptr);
    LinkType short_link = PointerType(nullptr);

    bool terminated = false;
    LengthType length = 0;
    std::vector<LR> lr;

    // Node() {
    //   children.fill(nullptr);
    // }

    PointerType Go(SymbolType symbol) const {
      if (!children.contains(symbol)) {
        return nullptr;
      }
      return children.at(symbol);
    }

    void Set(SymbolType symbol, PointerType child) {
      children[symbol] = child;
    }

    // PointerType& Go(SymbolType symbol) {
    //   // if (!children.contains(symbol)) {
    //   //   children[symbol] = nullptr;
    //   // }
    //   return children[symbol];
    // }

    auto& Children() {
      // std::vector<std::pair<SymbolType, PointerType>> res;
      // for (SymbolType s = 0; s < static_cast<SymbolType>(children.size()); ++s) {
      //   if (Go(s)) {
      //     res.emplace_back(s, Go(s));
      //   }
      // }
      // return res;
      return children;
    }
  };

 public:
  using PointerType = Node::PointerType;
  using LinkType = Node::LinkType;

 public:
  Trie() {
    root = NewNode();
  }

  explicit Trie(size_t n) : Trie() {
    flags_.resize(n, false);
    nodes.reserve(2 * n);
    for (size_t i = 0; i < n; ++i) {
      std::string word;
      size_t l = 0;
      size_t r = 0;
      std::cin >> l >> r >> word;
      AddWord(word, l, r);
    }
    CreateLinks();
    CreateShortLinks();
  }

 public:
  template <class... Args>
  PointerType NewNode(Args&&... args) {
    nodes.emplace_back(std::forward<Args>(args)...);
    return PointerType(nodes.size() - 1);
  }

  Node* NodePtr(PointerType p) {
    if (!p) {
      return nullptr;
    }
    return &nodes[p.index];
  }

  void AddWord(const std::string& word, size_t l, size_t r) {
    auto cur = root;
    for (auto c : word) {
      auto s = CharToSymbol(c);
      auto next = NodePtr(cur)->Go(s);
      if (next) {
        cur = next;
        continue;
      }
      auto new_node = NewNode();
      NodePtr(cur)->Set(s, new_node);
      cur = new_node;
    }
    NodePtr(cur)->terminated = true;
    NodePtr(cur)->length = word.size();
    NodePtr(cur)->lr.emplace_back(l, r, counter_++);
  }

 protected:
  PointerType FindLink(PointerType parent, SymbolType symbol) {
    auto link = NodePtr(parent)->link;
    while (link && !NodePtr(link)->Go(symbol)) {
      link = NodePtr(link)->link;
    }
    if (!link) {
      return root;
    }
    return NodePtr(link)->Go(symbol);
  }

  void CreateLinks() {
    std::queue<PointerType> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto cur = queue.front();
      queue.pop();
      for (auto& [s, child] : NodePtr(cur)->Children()) {
        NodePtr(child)->link = FindLink(cur, s);
        queue.push(child);
      }
    }
  }

  PointerType FindShortLink(PointerType node) {
    auto link = NodePtr(node)->link;
    if (!link) {
      return nullptr;
    }
    if (NodePtr(link)->terminated) {
      return link;
    }
    return NodePtr(link)->short_link;
  }

  void CreateShortLinks() {
    std::queue<PointerType> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto cur = queue.front();
      queue.pop();
      NodePtr(cur)->short_link = FindShortLink(cur);
      for (auto& [_, child] : NodePtr(cur)->Children()) {
        if (!child) {
          continue;
        }
        queue.push(child);
      }
    }
  }

  void Find(size_t index, PointerType node) {
    if (!node) {
      return;
    }
    if (!NodePtr(node)->terminated) {
      node = NodePtr(node)->short_link;
    }
    while (node) {
      if (NodePtr(node)->terminated) {
        for (auto [l, r, i] : NodePtr(node)->lr) {
          if (index < r && l < index - NodePtr(node)->length + 3) {
            flags_[i] = true;
          }
        }
      }
      node = NodePtr(node)->short_link;
    }
  }

  PointerType Next(PointerType node, SymbolType s) {
    while (node && !NodePtr(node)->Go(s)) {
      node = NodePtr(node)->link;
    }
    if (!node) {
      return root;
    }
    return NodePtr(node)->Go(s);
  }

 public:
  void Solution(const std::string& s) {
    auto cur = root;
    for (size_t i = 0; i < s.size(); ++i) {
      auto symbol = CharToSymbol(s[i]);
      cur = Next(cur, symbol);
      Find(i, cur);
    }
    for (auto flag : flags_) {
      std::cout << (flag ? '+' : '-');
    }
    std::cout << '\n';
  }

 public:
  std::vector<Node> nodes;
  PointerType root;

 private:
  size_t counter_ = 0;
  std::vector<bool> flags_;
};

void Solution(const std::string& s, size_t n) {
  Trie trie(n);
  trie.Solution(s);
}

int main() {
  size_t n = 0;
  std::string word;
  std::cin >> word;
  std::cin >> n;
  Solution(word, n);
  return 0;
}
