
#pragma once

#include <utility>

template <class T>
class UniquePtr {
 public:
  UniquePtr() : value_(nullptr) {
  }

  UniquePtr(T* value) : value_(value) {  // NOLINT
  }
  
  UniquePtr(const UniquePtr&) = delete;

  UniquePtr(UniquePtr&& other) noexcept : value_(other.value_) {
    other.value_ = nullptr;
  }

  ~UniquePtr() {
    Unlink();
  }

  auto operator=(const UniquePtr&) = delete;

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    Unlink();
    value_ = other.value_;
    other.value_ = nullptr;
    return *this;
  }

 protected:
  void Unlink() {
    if (!value_) {
      return;
    }
    delete value_;
  }

 public:
  T* Release() {
    auto result = value_;
    value_ = nullptr;
    return result;
  }

  void Reset(T* ptr = nullptr) {
    Unlink();
    value_ = ptr;
  }

  void Swap(UniquePtr& other) {
    std::swap(value_, other.value_);
  }

  T* Get() const {
    return value_;
  }

  T& operator*() const {
    return *value_;
  }

  T* operator->() const {
    return value_;
  }

  operator bool() const {  // NOLINT
    return value_;
  }

 protected:
  T* value_ = nullptr;
};

template <class T, class... Args>
UniquePtr<T> MakeUnique(Args... args) {
  return UniquePtr<T>(new T(args...));
}
