#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

bool Check(std::string& word) {
  size_t left = 0;
  size_t right = word.size() - 1;
  while (left < right) {
    if (word[left] != word[right]) {
      return false;
    }
    ++left;
    --right;
  }
  return true;
}

auto GetPairs(std::vector<std::string>& words) {
  std::unordered_map<std::string, size_t> index;
  std::set<std::pair<size_t, size_t>> result;
  for (size_t i = 0; i < words.size(); ++i) {
    index[words[i]] = i;
  }
  for (size_t i = 0; i < words.size(); ++i) {
    auto& word = words[i];
    auto reversed = std::string(word.rbegin(), word.rend());
    if (index.contains(reversed) && index[reversed] != i) {
      result.emplace(index[reversed], i);
    }
    for (size_t j = 0; j < word.size(); ++j) {
      auto pref = word.substr(0, j);
      auto suf = word.substr(j);
      if (Check(pref)) {
        auto reversed_suf = std::string(suf.rbegin(), suf.rend());
        if (index.contains(reversed_suf) && index[reversed_suf] != i) {
          result.emplace(index[reversed_suf], i);
        }
      }
      if (Check(suf)) {
        auto reversed_pref = std::string(pref.rbegin(), pref.rend());
        if (index.contains(reversed_pref) && index[reversed_pref] != i) {
          result.emplace(i, index[reversed_pref]);
        }
      }
    }
  }
  return result;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<std::string> words(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> words[i];
  }
  auto answer = GetPairs(words);
  std::cout << answer.size() << '\n';
  for (const auto& pair : answer) {
    std::cout << pair.first + 1 << ' ' << pair.second + 1 << '\n';
  }
}
