// Copyright 2024 Andrew
// 1

#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

auto RandomPrimeInRange(size_t l, size_t r) {
  std::vector<size_t> p;
  for (size_t i = l; i <= r; ++i) {
    bool is_prime = true;
    for (size_t j = 2; j * j <= i; ++j) {
      if (i % j == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      p.emplace_back(i);
    }
  }
  return p[std::rand() % p.size()];
}

size_t CharToInt(char c) {
  return static_cast<size_t>(c - 'a');
}

// a % b
template <class I>
size_t Mod(I a, size_t b) {
  if (a >= 0) {
    return a % b;
  }
  return (a % b) + b;
}

// (a - b) % m
size_t DiffMod(size_t a, size_t b, size_t m) {
  if (a >= b) {
    return Mod(a - b, m);
  }
  return m - Mod(b - a, m);
}

class RC {
 public:
  explicit RC(const std::string& s, size_t p, size_t m) : s(s), p(p), m(m) {
    p_.resize(s.size() + 1, 1);
    h_.resize(s.size() + 1, 0);
    for (size_t i = 0; i < s.size(); ++i) {
      h_[i + 1] = Mod((h_[i] * p) + CharToInt(s[i]), m);
      p_[i + 1] = Mod(p_[i] * p, m);
      // std::cout << i + 1 << ": h[i] = " << h_[i + 1] << '\n';
    }
  }

  auto Size() {
    return h_.size() - 1;
  }

 private:
  auto HashS(size_t l, size_t r) {
    return DiffMod(h_[r], h_[l] * p_[r - l], m);
  }

  auto Hash(const std::string& s) {
    size_t hash = 0;
    auto n = s.size();
    for (size_t i = 0; i < n; ++i) {
      hash += (p_[n - i - 1] * CharToInt(s[i])) % m;
    }
    return hash % m;
  }

 public:
  auto Solution(const std::string& t) {
    if (t.size() > Size()) {
      return;
    }
    auto hash_t = Hash(t);
    std::vector<size_t> answer;
    for (size_t i = 0; i < Size() - t.size() + 1; ++i) {
      auto hash_s = HashS(i, i + t.size());
      // std::cout << i + 1 << ": " << hash_s << " =? " << hash_t << '\n';
      if (hash_s == hash_t) {
        for (size_t j = 0; j < t.size(); ++j) {
          if (t[j] != s[i + j]) {
            throw std::runtime_error("hash intersection");
          }
        }
        answer.emplace_back(i);
      }
    }
    std::cout << answer.size();
    for (auto i : answer) {
      std::cout << " " << i + 1;
    }
    std::cout << '\n';
  }

 public:
  const std::string s;
  const size_t p;
  const size_t m;

 private:
  std::vector<size_t> p_;
  std::vector<size_t> h_;
};

void Solution(const std::string& s, size_t n) {
  std::srand(time(nullptr));
  size_t p = 0;
  size_t m = 0;
  p = 17977;
  m = 3337333;
  // p = RandomPrimeInRange(1, 100000);
  // std::vector<size_t> m_primes = {
  //     1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000103,
  //     1000000123, 1000000181, 1000000193, 1000000209, 1000000233, 1000000257, 1000000277, 1000000293,
  // };
  // m = m_primes[std::rand() % m_primes.size()];

  RC rk(s, p, m);
  for (size_t i = 0; i < n; ++i) {
    std::string word;
    std::cin >> word;
    rk.Solution(word);
  }
}

int main() {
  size_t n = 0;
  std::string word;
  std::cin >> word;
  std::cin >> n;
  Solution(word, n);
  return 0;
}
