#pragma once

#include <deque>

template <class T, class Container = std::deque<T>>
class Stack {
 public:
  Stack() = default;

  explicit Stack(const Container& container) : container_(container) {
  }

  template <class ForwardIterator>
  Stack(ForwardIterator begin, ForwardIterator end) : container_(begin, end) {
  }

  const T& Top() const {
    return container_.back();
  }

  T& Top() {
    return container_.back();
  }

  bool Empty() const {
    return container_.empty();
  }

  size_t Size() const {
    return container_.size();
  }

  void Push(const T& value) {
    container_.emplace_back(value);
  }

  void Push(T&& value) {
    container_.emplace_back(std::move(value));
  }

  template <class... Args>
  void Emplace(Args&&... args) {
    container_.emplace_back(std::forward<Args>(args)...);
  }

  void Pop() {
    container_.pop_back();
  }

  void Swap(Stack& other) {
    container_.swap(other.container_);
  }

 protected:
  Container container_;
};
