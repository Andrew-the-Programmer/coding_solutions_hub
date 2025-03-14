// Copyright 2024 Andrew

#include <cstddef>
#include <array>
#include <vector>
#include <string>
#include <iostream>

using SymbolType = int8_t;
using SizeType = int32_t;
constexpr SymbolType kAlphabetPower = 26;

SymbolType CharToSymbol(char c) {
  return static_cast<SymbolType>(c - 'a');
}

char SymbolToChar(SymbolType i) {
  return static_cast<char>('a' + i);
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

class SuffixAutomaton {
 public:
  struct Node {
    using PointerType = Ptr;
    using LinkType = Ptr;
    using LengthType = size_t;

    std::array<PointerType, kAlphabetPower> children;
    LinkType link = PointerType(nullptr);
    LengthType length = 0;

    size_t substr_count = 0;

    Node() {
      children.fill(nullptr);
    }
    ~Node() = default;

    auto& Go(SymbolType symbol) {
      return children[symbol];
    }
  };

  std::vector<Node> nodes;

 public:
  using PointerType = Node::PointerType;
  using LinkType = Node::LinkType;

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

 public:
  SuffixAutomaton() : root(NewNode()), last(root) {
  }

  explicit SuffixAutomaton(const std::string& word) : SuffixAutomaton() {
    nodes.reserve(2 * word.size());
    AddWord(word);
  }

  void AddWord(const std::string& word) {
    for (auto c : word) {
      AddSymbol(CharToSymbol(c));
    }
  }

  void AddSymbol(SymbolType symbol) {
    auto new_node = NewNode();
    NodePtr(new_node)->length = NodePtr(last)->length + 1;
    auto current = last;

    while (current && !NodePtr(current)->Go(symbol)) {
      NodePtr(current)->Go(symbol) = new_node;
      current = NodePtr(current)->link;
    }

    if (!current) {
      NodePtr(new_node)->link = root;
    } else {
      auto next = NodePtr(current)->Go(symbol);
      if (NodePtr(current)->length + 1 == NodePtr(next)->length) {
        NodePtr(new_node)->link = next;
      } else {
        NodePtr(new_node)->link = Clone(current, symbol, next);
      }
    }

    // For this problem
    {
      auto length = NodePtr(new_node)->length;
      auto last_count = NodePtr(last)->substr_count;
      auto link_length = NodePtr(NodePtr(new_node)->link)->length;

      NodePtr(new_node)->substr_count = length + last_count - link_length;
      std::cout << NodePtr(new_node)->substr_count << std::endl;
    }

    last = new_node;
  }

 protected:
  PointerType Clone(PointerType parent, SymbolType symbol, PointerType node) {
    auto clone = NewNode(*NodePtr(node));
    NodePtr(clone)->length = NodePtr(parent)->length + 1;
    NodePtr(node)->link = clone;
    while (parent && NodePtr(parent)->Go(symbol) == node) {
      NodePtr(parent)->Go(symbol) = clone;
      parent = NodePtr(parent)->link;
    }
    return clone;
  }

 protected:
  PointerType root;
  PointerType last;
};

void Solution(const std::string& s) {
  SuffixAutomaton sa(s);
}

int main() {
  std::string s;
  std::cin >> s;
  Solution(s);
  return 0;
}
