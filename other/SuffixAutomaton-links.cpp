#include <memory>
#include <string>
#include <array>
#include <cstddef>

using Symbol = char;
constexpr size_t kAlphabetPower = 26;

Symbol CharToSymbol(char c) {
  return static_cast<Symbol>(c - 'a');
}

char SymbolToChar(Symbol i) {
  return static_cast<char>('a' + i);
}

class SuffixAutomaton {
 public:
  struct Node {
    using PointerType = std::shared_ptr<Node>;
    using LinkType = std::weak_ptr<Node>;
    using LengthType = int;

    std::array<PointerType, kAlphabetPower> children;
    LinkType link;
    // bool terminated = false;
    LengthType length = 0;

    // for this problem
    // p: (Path(root->this) + p + string) - min (shortlex) string not in s
    Symbol p = 0;

    Node() {
      children.fill(nullptr);
    }

    PointerType& Go(Symbol symbol) {
      return children[symbol];
    }

    template <class... Args>
    static auto New(Args&&... args) {
      return std::make_shared<Node>(std::forward<Args>(args)...);
    }
  };

 public:
  using PointerType = Node::PointerType;

 public:
  explicit SuffixAutomaton(const std::string& word) {
    root = Node::New();
    last = root;
    for (auto c : word) {
      AddSymbol(CharToSymbol(c));
    }
  }

  // Extend the automaton with a new character
  void AddSymbol(Symbol symbol) {
    // std::cout << SymbolToChar(symbol) << '\n';

    auto new_node = Node::New();
    new_node->length = last->length + 1;
    auto current = last;

    while (current != nullptr && current->Go(symbol) == nullptr) {
      current->Go(symbol) = new_node;
      current = current->link.lock();
    }

    if (current == nullptr) {
      new_node->link = root;
    } else if (current->length + 1 == current->Go(symbol)->length) {
      new_node->link = current->Go(symbol);
    } else {
      new_node->link = Clone(current, symbol, current->Go(symbol));
    }

    last = new_node;
  }

  const PointerType GetRoot() {
    return root;
  }

 protected:
  PointerType Clone(PointerType parent, Symbol symbol, PointerType node) {
    auto clone = Node::New(*node);
    clone->length = parent->length + 1;
    node->link = clone;
    while (parent != nullptr && parent->Go(symbol) == node) {
      parent->Go(symbol) = clone;
      parent = parent->link.lock();
    }
    return clone;
  }

 protected:
  PointerType root = nullptr;
  PointerType last = nullptr;
};
