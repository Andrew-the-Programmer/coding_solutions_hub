// Copyright 2024 Andrew

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

bool CheckPalindrome(const std::string& word) {
  size_t l = 0;
  size_t r = word.size() - 1;
  while (l < r) {
    if (word[l++] != word[r--]) {
      return false;
    }
  }
  return true;
}

auto FindPairedPalindromes(const std::vector<std::string>& words) {
  std::unordered_map<std::string, size_t> index;
  std::set<std::pair<size_t, size_t>> answer;

  for (size_t i = 0; i < words.size(); ++i) {
    index[words[i]] = i;
  }
  for (size_t i = 0; i < words.size(); ++i) {
    const auto& word = words[i];

    auto rword = std::string(word.rbegin(), word.rend());

    if (index.contains(rword) && index[rword] != i) {
      answer.emplace(index[rword], i);
    }

    for (size_t j = 0; j < word.size(); ++j) {
      auto prefix = word.substr(0, j);
      auto suffix = word.substr(j);

      if (CheckPalindrome(prefix)) {
        auto rsuffix = std::string(suffix.rbegin(), suffix.rend());
        if (index.contains(rsuffix) && index[rsuffix] != i) {
          answer.emplace(index[rsuffix], i);
        }
      }
      if (CheckPalindrome(suffix)) {
        auto rprefix = std::string(prefix.rbegin(), prefix.rend());
        if (index.contains(rprefix) && index[rprefix] != i) {
          answer.emplace(i, index[rprefix]);
        }
      }
    }
  }
  return answer;
}

void Solution(const std::vector<std::string>& words) {
  auto answer = FindPairedPalindromes(words);
  std::cout << answer.size() << '\n';
  for (const auto& [i, j] : answer) {
    std::cout << i + 1 << ' ' << j + 1 << '\n';
  }
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<std::string> words(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> words[i];
  }
  Solution(words);
  return 0;
}
