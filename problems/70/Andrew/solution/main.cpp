// Copyright 2024 Andrew

#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>
#include <vector>

auto Find(const std::vector<std::optional<size_t>>& tmp, size_t n) -> size_t {
  if (!tmp[n]) {
    // Can't open n, have to break it
    return n;
  }
  return Find(tmp, tmp[n].value());
}

size_t Join(std::vector<std::optional<size_t>>& tmp, size_t cur, size_t next) {
  // this = [? , ... , ? , i, ..., n]
  // i = at(i) = Find(i)
  auto fb = Find(tmp, next);
  // at(fb) = fb
  // Opening i results in opening fb
  if (cur == fb) {
    // Opening i does not result in opening some other bank
    return 0;
  }
  // Opening i results in opening some other bank
  tmp[cur] = fb;
  return 1;
}

void Solution0(const std::vector<size_t>& data) {
  size_t n = data.size();
  std::vector<std::optional<size_t>> tmp(n);
  size_t count = n;
  for (size_t i = 0; i < n; ++i) {
    count -= Join(tmp, i, data[i]);
  }
  std::cout << count << '\n';
  /* Same result:
   count = 0;
   for (size_t i = 0; i < n; ++i) {
     if (i == tmp[i]) {
       ++count;
     }
   } */
}

/* Similar to Solution0 but with recursive lambdas 🤯*/
void Solution1(const std::vector<size_t>& data) {
  size_t n = data.size();
  std::vector<std::optional<size_t>> tmp(n);

  std::function<size_t(size_t)> find;
  find = [&tmp, &find](size_t n) -> size_t {
    if (!tmp[n]) {
      return n;
    }
    return find(tmp[n].value());
  };

  std::function<size_t(size_t, size_t)> join;
  join = [&tmp, &find](size_t cur, size_t next) -> size_t {
    auto fb = find(next);
    if (cur == fb) {
      return 0;
    }
    tmp[cur] = fb;
    return 1;
  };

  size_t count = n;
  for (size_t i = 0; i < n; ++i) {
    count -= join(i, data[i]);
  }
  std::cout << count << '\n';
}

/* Similar to Solution0 but with struct */
void Solution2(const std::vector<size_t>& data) {
  size_t n = data.size();
  struct Tmp : public std::vector<size_t> {
    using Base = std::vector<size_t>;
    using Base::at;
    explicit Tmp(size_t size) : Base(size) {
      for (size_t i = 0; i < size; ++i) {
        at(i) = i;
      }
    }
    size_t Find(size_t n) {
      if (n == at(n)) {
        return n;
      }
      return Find(at(n));
    }
    size_t Join(size_t cur, size_t next) {
      auto fb = Find(next);
      if (cur == fb) {
        return 0;
      }
      at(cur) = fb;
      return 1;
    }
  };
  Tmp tmp(n);
  size_t count = n;
  for (size_t i = 0; i < n; ++i) {
    count -= tmp.Join(i, data[i]);
  }
  std::cout << count << '\n';
}

int main() {
  size_t n{};
  std::cin >> n;
  std::vector<size_t> data(n);
  for (size_t i = 0; i < n; ++i) {
    size_t v{};
    std::cin >> v;
    --v;
    data[i] = v;
  }

  Solution0(data);

  return 0;
}
