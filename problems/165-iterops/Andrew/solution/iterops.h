#pragma once

#include <iterator>

namespace concepts {
template <class Iter>
concept InputIterator = requires(Iter it) {
  it != it;
  *it;
  ++it;
};

template <class Iter>
concept ForwardIterator = InputIterator<Iter> && requires(Iter it) { it++; };

template <class Iter>
concept BidirectionalIterator = ForwardIterator<Iter> && requires(Iter it) {
  it--;
  --it;
};

template <class Iter>
concept RandomAccessIterator = BidirectionalIterator<Iter> && requires(Iter it) {
  it += 1;
  it -= 1;
  it + 1;
  it - 1;
  it - it;
};
}  // namespace concepts

template <class Iter>
using DiffType = typename std::iterator_traits<Iter>::difference_type;

template <concepts::InputIterator Iter>
void Advance(Iter& it, DiffType<Iter> n) {
  size_t m = n;
  for (size_t i = 0; i < m; ++i) {
    ++it;
  }
}

template <concepts::BidirectionalIterator Iter>
void Advance(Iter& it, DiffType<Iter> n) {
  size_t m = std::abs(n);
  if (n < 0) {
    for (size_t i = 0; i < m; ++i) {
      --it;
    }
    return;
  }
  for (size_t i = 0; i < m; ++i) {
    ++it;
  }
}

template <concepts::RandomAccessIterator Iter>
void Advance(Iter& it, DiffType<Iter> n) {
  it += n;
}

template <class Iter>
Iter Next(Iter it, DiffType<Iter> n = 1) {
  Advance(it, n);
  return it;
}

template <class Iter>
Iter Prev(Iter it, DiffType<Iter> n = 1) {
  return Next(it, -n);
}

template <concepts::InputIterator Iter>
auto Distance(Iter first, Iter last) {
  DiffType<Iter> n = 0;
  while (first != last) {
    ++first;
    ++n;
  }
  return n;
}

template <concepts::RandomAccessIterator Iter>
auto Distance(Iter first, Iter last) {
  return last - first;
}
