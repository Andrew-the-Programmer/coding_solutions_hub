#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct State {
  int len;
  int link;
  std::vector<int> next;

  State() = default;
  explicit State(int l, int alphabet) : len(l), next(alphabet, -1){};
};

class SuffixAutomation {
  int last_;
  int alphabet_;

 public:
  std::vector<State> st;
  int size;

  SuffixAutomation() : last_(0), st(1), size(0) {
    st[0].link = -1;
    st[0].len = 0;
  }

  explicit SuffixAutomation(const std::string& str) : last_(0), st(2 * str.size()), size() {
    st[0].link = -1;
    st[0].len = 0;
    for (size_t i = 0; i < str.size(); ++i) {
      AddChar(str[i]);
    }
  }

  void AddChar(char c) {
    int curr = size + 1;
    st.emplace_back(st[last_].len + 1, alphabet_);
    ++size;
    int p = 0;
    for (p = last_; p != -1 && st[p].next[c - 'a'] == -1; p = st[p].link) {
      st[p].next[c - 'a'] = curr;
    }
    st[curr].link = 0;
    if (p == -1) {
    } else {
      int q = st[p].next[c - 'a'];
      if (st[q].len == st[p].len + 1) {
        st[curr].link = q;
      } else {
        int copy = size + 1;
        ++size;
        st.emplace_back(st[p].len + 1, alphabet_);
        st[copy].next = st[q].next;
        st[copy].link = st[q].link;
        for (; p != -1 && st[p].next[c - 'a'] == q; p = st[p].link) {
          st[p].next[c - 'a'] = copy;
        }
        st[q].link = copy;
        st[curr].link = copy;
      }
    }
    last_ = curr;
  }

  void AddString(const std::string& str) {
    st[0].next.resize(alphabet_, -1);
    for (char c : str) {
      AddChar(c);
    }
  }

  void CountDPCycle() {
    CountDP(0);
  }

  int CountDP(int index) {
    int current = 1'000'000'000;
    int next = 0;
    char symbol = '#';
    for (int c = 0; c < alphabet_; ++c) {
      if (st[index].next[c] == -1) {
        st[index].link = c + 'a';
        return 1;
      }
      next = CountDP(st[index].next[c]);
      if (next < current) {
        current = next;
        symbol = static_cast<char>(c + 'a');
      }
    }
    st[index].link = symbol;
    return 1 + current;
  }

  void Solver() {
    int number = 0;
    int alphabet = 0;
    std::cin >> number >> alphabet;
    alphabet_ = alphabet;
    std::string str;
    std::cin >> str;
    AddString(str);
    CountDPCycle();
    std::string answer;
    int current = 0;
    while (true) {
      char sym = static_cast<char>(st[current].link);
      answer += sym;
      if (st[current].next[sym - 'a'] == -1) {
        break;
      }
      current = st[current].next[sym - 'a'];
    }
    std::cout << answer << '\n';
  }
};

int main() {
  SuffixAutomation suff_aut;
  suff_aut.Solver();
  return 0;
}
