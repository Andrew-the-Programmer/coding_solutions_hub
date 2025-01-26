// Copyright 2024 Andrew

#include <cstddef>
#include <tuple>
#include <vector>
#include <string>
#include <queue>
#include <array>
#include <iostream>

using SymbolType = int;
constexpr size_t kAlphabetPower = 26;
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
  friend auto& operator<<(std::ostream& os, const Ptr& ptr) {  // NOLINT
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

    std::array<PointerType, kAlphabetPower> children;
    LinkType link = PointerType(nullptr);
    LinkType short_link = PointerType(nullptr);
    bool terminated = false;
    LengthType length = 0;

    std::vector<LR> lr;

    Node() {
      children.fill(nullptr);
    }
    ~Node() = default;

    PointerType& Go(SymbolType symbol) {
      return children[symbol];
    }
  };

  std::vector<Node> nodes;

 public:
  using PointerType = Node::PointerType;
  using LinkType = Node::LinkType;

 public:
  Trie() : root(NewNode()) {
  }

  explicit Trie(size_t n) : Trie() {
    flags_.resize(n, false);
    nodes.reserve(n);
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
    return nodes.size() - 1;
  }

  Node* Node(PointerType p) {
    if (!p) {
      return nullptr;
    }
    return &nodes[p.index];
  }

  void AddWord(const std::string& word, size_t l, size_t r) {
    auto cur = root;
    for (auto c : word) {
      auto s = CharToSymbol(c);
      auto next = Node(cur)->Go(s);
      if (next) {
        cur = next;
        continue;
      }
      auto new_node = NewNode();
      Node(cur)->Go(s) = new_node;
      cur = new_node;
    }
    Node(cur)->terminated = true;
    Node(cur)->length = word.size();
    Node(cur)->lr.emplace_back(l, r, counter_++);
  }

 protected:
  PointerType FindLink(PointerType parent, SymbolType symbol) {
    auto link = Node(parent)->link;
    if (!link) {
      return root;
    }
    auto next = Node(link)->Go(symbol);
    if (next) {
      return next;
    }
    return FindLink(link, symbol);
  }

  void CreateLinks() {
    std::queue<PointerType> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto cur = queue.front();
      queue.pop();
      for (SymbolType s = 0; s < static_cast<SymbolType>(kAlphabetPower); ++s) {
        auto child = Node(cur)->Go(s);
        if (!child) {
          continue;
        }
        Node(child)->link = FindLink(cur, s);
        queue.push(child);
      }
    }
  }

  PointerType FindShortLink(PointerType node) {
    auto link = Node(node)->link;
    if (!link) {
      return nullptr;
    }
    if (Node(link)->terminated) {
      return link;
    }
    return Node(link)->short_link;
  }

  void CreateShortLinks() {
    std::queue<PointerType> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto cur = queue.front();
      queue.pop();
      Node(cur)->short_link = FindShortLink(cur);
      for (SymbolType s = 0; s < static_cast<SymbolType>(kAlphabetPower); ++s) {
        auto child = Node(cur)->Go(s);
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
    if (Node(node)->terminated) {
      for (auto [l, r, i] : Node(node)->lr) {
        if (index < r && l < index - Node(node)->length + 3) {
          flags_[i] = true;
        }
      }
    }
    return Find(index, Node(node)->short_link);
  }

  PointerType Next(PointerType node, SymbolType s) {
    if (!node) {
      return root;
    }
    auto next = Node(node)->Go(s);
    if (next) {
      return next;
    }
    return Next(Node(node)->link, s);
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
  PointerType root;

 private:
  size_t counter_ = 0;
  std::vector<bool> flags_;
};
