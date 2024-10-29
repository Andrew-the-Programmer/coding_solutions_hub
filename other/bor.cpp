#include <array>
#include <cstddef>
#include <queue>
#include <string>

using Symbol = char;
constexpr size_t kAlphabetPower = 26;

struct Node {
  std::array<Node*, kAlphabetPower> children;
  Node* link = nullptr;
  Node* short_link = nullptr;
  bool terminated = false;
};

class Trie {
  explicit Trie(const std::vector<std::string>& words) {
    root = new Node();
    for (auto&& word : words) {
      AddWord(word);
    }
    CreateLinks();
    CreateShortLinks();
  }

  void AddWord(const std::string& word) {
    auto cur = root;
    for (auto symbol : word) {
      auto& next = cur->children[symbol];
      if (next) {
        cur = next;
        continue;
      }
      auto new_node = new Node();
      next = new_node;
      cur = next;
    }
    cur->terminated = true;
  }

  Node* CreateLink(Node* cur_link, Symbol symbol) {
    if (auto next = cur_link->children[symbol]; next) {
      return next;
    }
    return CreateLink(cur_link->link, symbol);
  }

  Node* CreateShortLink(Node* cur_link, Symbol symbol) {
    auto next = cur_link->children[symbol];
    if (next && next->terminated) {
      return next;
    }
    return CreateLink(cur_link->link, symbol);
  }

  void CreateLinks() {
    std::queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto cur = queue.front();
      for (size_t i = 0; i < cur->children.size(); ++i) {
        auto child = cur->children[i];
        child->link = CreateLink(cur->link, static_cast<Symbol>(i));
        queue.push(child);
      }
    }
  }

  void CreateShortLinks() {
    std::queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto cur = queue.front();
      for (size_t i = 0; i < cur->children.size(); ++i) {
        auto child = cur->children[i];
        child->link = CreateShortLink(cur->link, static_cast<Symbol>(i));
        queue.push(child);
      }
    }
  }

 protected:
  Node* root;
};
