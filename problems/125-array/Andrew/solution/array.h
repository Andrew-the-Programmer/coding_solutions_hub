#pragma once

#include <cstdint>
#include <utility>
#include <iostream>

using SizeT = uint64_t;

template <class T, SizeT N>
class Array {
//-----------------------------------------------------------------------
 public:
  const T& Front() const { return *data_; }
  T& Front() { return *data_; }
  const T& Back() const { return data_[N - 1]; }
  T& Back() { return data_[N - 1]; }
  const T* Data() const { return data_; }
  T* Data() { return data_; }
  SizeT Size() const { return N; }
  bool Empty() const {
    return Size() == 0;
  }
  void Fill(const T& value) {
    for (T& val : data_) {
      val = value;
    }
  }
  void Swap(Array& other) {
    if (other.Size() == Size()) {
      for (SizeT i = 0; i < N; ++i) {
        std::swap(data_[i], other.Data()[i]);
      }
    }
  }
//-----------------------------------------------------------------------
 public:
  const T& operator[](SizeT index) const {
    return data_[index];
  }
  T& operator[](SizeT index) {
    return data_[index];
  }
//-----------------------------------------------------------------------
public:
  T data_[N];

  friend std::ostream& operator<< (std::ostream& stream, const Array& other) {
    for (auto val : other.data_) {
      stream << val << " ";
    }
    return stream;
  }
};