// Copyright 2024 Andrew

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <array>
#include <cstddef>
#include <iostream>

using Symbol = int8_t;
using SizeType = int32_t;

constexpr size_t kAlphabetPower = 26;
constexpr SizeType kNullValue = -1;

Symbol CharToSymbol(char c) {
  return static_cast<Symbol>(c - 'a');
}

char SymbolToChar(Symbol i) {
  return static_cast<char>('a' + i);
}

class SuffixAutomaton {
 public:
  struct Node {
    using PointerType = SizeType;
    using LinkType = PointerType;

    std::array<PointerType, kAlphabetPower> children;
    LinkType link;
    SizeType length;

    // for this problem
    // p: (Path(root->this) + p + string) - min (shortlex) string not in s
    Symbol p = 0;

    Node() : link(kNullValue), length(0) {
      children.fill(kNullValue);
    }

    auto& To(Symbol symbol) {
      return children[symbol];
    }
  };

 protected:
  std::vector<Node> nodes;

 public:
  using PointerType = Node::PointerType;
  using ReferenceType = Node&;

  template <class... Args>
  PointerType NewNode(Args&&... args) {
    nodes.emplace_back(std::forward<Args>(args)...);
    return static_cast<PointerType>(nodes.size() - 1);
  }

  Node& GetNode(PointerType index) {
    return nodes[index];
  }

  PointerType& Next(PointerType index, Symbol symbol) {
    return GetNode(index).To(symbol);
  }

  bool IsNull(PointerType index) {
    return index == kNullValue;
  }

 public:
  SuffixAutomaton() : root(NewNode()), last(root) {
  }

  explicit SuffixAutomaton(const std::string& word) : SuffixAutomaton() {
    nodes.reserve(word.size());
    for (auto c : word) {
      AddSymbol(CharToSymbol(c));
    }
  }

  void AddSymbol(Symbol symbol) {
    auto new_node = NewNode();
    GetNode(new_node).length = GetNode(last).length + 1;
    auto current = last;

    while (!IsNull(current) && IsNull(Next(current, symbol))) {
      Next(current, symbol) = new_node;
      current = GetNode(current).link;
    }

    if (IsNull(current)) {
      GetNode(new_node).link = root;
    } else if (GetNode(current).length + 1 == GetNode(Next(current, symbol)).length) {
      GetNode(new_node).link = Next(current, symbol);
    } else {
      GetNode(new_node).link = Clone(current, symbol, Next(current, symbol));
    }

    last = new_node;
  }

  PointerType GetRoot() {
    return root;
  }

 protected:
  PointerType Clone(PointerType parent, Symbol symbol, PointerType node) {
    auto clone = NewNode(GetNode(node));
    GetNode(clone).length = GetNode(parent).length + 1;
    GetNode(node).link = clone;
    while (!IsNull(parent) && Next(parent, symbol) == node) {
      GetNode(parent).To(symbol) = clone;
      parent = GetNode(parent).link;
    }
    return clone;
  }

 protected:
  PointerType root;
  PointerType last;
};

void Solution(const std::string& s, size_t k) {
  using PointerType = SuffixAutomaton::PointerType;

  SuffixAutomaton sa(s);

  // recursively finds min (shortlex) path not in string s
  // see SuffixAutomaton::Node::p
  std::function<size_t(PointerType)> min_path_length = [&sa, k, &min_path_length](PointerType cur) -> size_t {
    std::optional<size_t> min_length;
    size_t next_length = 0;
    Symbol best_symbol = 0;
    for (Symbol s = 0; s < static_cast<Symbol>(k); ++s) {
      auto next = sa.Next(cur, s);
      if (sa.IsNull(next)) {
        sa.GetNode(cur).p = s;
        return 1;
      }
      next_length = min_path_length(next);
      if (!min_length.has_value() || next_length < min_length) {
        min_length = next_length;
        best_symbol = s;
      }
    }
    sa.GetNode(cur).p = best_symbol;
    return 1 + min_length.value();
  };

  auto cur = sa.GetRoot();
  min_path_length(cur);

  std::string answer;

  // restore min path
  while (!sa.IsNull(cur)) {
    auto s = sa.GetNode(cur).p;
    answer += SymbolToChar(s);
    cur = sa.Next(cur, s);
  }

  std::cout << answer << '\n';
}

int main() {
  size_t n = 0;
  size_t k = 0;
  std::string s;
  std::cin >> n >> k >> s;
  Solution(s, k);
  return 0;
}
