
#pragma once

#include <utility>
#include <stddef.h>

template <class T>
class SharedPtr {
 public:
  SharedPtr() : value_(nullptr), count_(nullptr) {
  }

  SharedPtr(T* value) : value_(value), count_(value ? new size_t(1) : nullptr) {  // NOLINT
  }

  SharedPtr(const SharedPtr& other) : value_(other.value_), count_(other.count_) {
    IncrementCount();
  }

  SharedPtr(SharedPtr&& other) noexcept : value_(other.value_), count_(other.count_) {
    other.value_ = nullptr;
    other.count_ = nullptr;
  }

  ~SharedPtr() {
    Unlink();
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this == &other) {
      return *this;
    }
    Unlink();
    value_ = other.value_;
    count_ = other.count_;
    IncrementCount();
    return *this;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    Unlink();
    value_ = other.value_;
    count_ = other.count_;
    other.value_ = nullptr;
    other.count_ = nullptr;
    return *this;
  }

 protected:
  bool IsValid() const {
    return value_ && count_;
  }

  bool NotValid() const {
    return !IsValid();
  }

  void IncrementCount() {
    if (NotValid()) {
      return;
    }
    ++(*count_);
  }

  void DecrementCount() {
    if (NotValid()) {
      return;
    }
    --(*count_);
  }

  void Delete() {
    if (NotValid()) {
      return;
    }
    delete value_;
    delete count_;
    value_ = nullptr;
    count_ = nullptr;
  }

  void Unlink() {
    if (UseCount() < 2) {
      Delete();
    } else {
      DecrementCount();
    }
  }

 public:
  size_t UseCount() const {
    if (NotValid()) {
      return 0;
    }
    return *count_;
  }

  void Reset(T* ptr = nullptr) {
    Unlink();
    value_ = ptr;
    count_ = (ptr ? new size_t(1) : nullptr);
  }

  void Swap(SharedPtr& other) {
    std::swap(value_, other.value_);
    std::swap(count_, other.count_);
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
  size_t* count_ = nullptr;
};
