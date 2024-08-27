#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <type_traits>

#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

struct StringIsEmpty {};

struct BaseStringAllocator {
  template <class CharT>
  CharT* allocate(size_t length) const {  // NOLINT
    return length == 0 ? nullptr : new CharT[length];
  }

  template <class CharT>
  void deallocate(CharT* ptr, [[maybe_unused]] size_t size = 0) const {  // NOLINT
    delete[] ptr;
  }

  template <class CharT, class... Args>
  void construct(CharT* ptr, const Args&... args) const {  // NOLINT
    new (ptr) CharT(args...);
  }

  template <class CharT>
  void construct(CharT* ptr) const {  // NOLINT
    ptr->~CharT();
  }
};

template <class CharT, class Alloc = BaseStringAllocator>
class BaseString {
 public:
  template <bool IsConst>
  struct BaseIter {
   public:
    using value_type = CharT;                                                                // NOLINT
    using pointer = typename std::conditional_t<IsConst, const value_type*, value_type*>;    // NOLINT
    using reference = typename std::conditional_t<IsConst, const value_type&, value_type&>;  // NOLINT
    using difference_type = int64_t;                                                         // NOLINT

   public:
    explicit BaseIter(pointer ptr) : ptr_(ptr) {  // NOLINT
    }

    BaseIter(const BaseIter&) = default;

    BaseIter& operator=(const BaseIter&) = default;

    reference operator*() const {
      return *ptr_;
    }

    pointer operator->() const {
      return ptr_;
    }

    BaseIter& operator++() {
      ++ptr_;
      return *this;
    }

    BaseIter operator++(int) {
      BaseIter copy = *this;
      ++ptr_;
      return copy;
    }

    friend bool operator==(const BaseIter& first, const BaseIter& second) {
      return first.ptr_ == second.ptr_;
    }

    friend bool operator!=(const BaseIter& first, const BaseIter& second) {
      return !(first == second);
    }

    operator bool() const {  // NOLINT
      return ptr_;
    }

    BaseIter& operator+=(difference_type step) {
      if (ptr_) {
        ptr_ += step;
      }
      return *this;
    }

    template <class DiffT = difference_type>
    friend BaseIter operator+(const BaseIter& iter, DiffT step) {
      BaseIter copy = iter;
      copy += step;
      return copy;
    }

    template <class DiffT = difference_type>
    friend BaseIter operator+(DiffT step, const BaseIter& iter) {
      return iter + step;
    }

    BaseIter& operator-=(difference_type step) {
      *this += (-step);
      return *this;
    }

    template <class DiffT = difference_type>
    friend BaseIter operator-(const BaseIter& iter, DiffT step) {
      return iter + (-step);
    }

    template <class DiffT = difference_type>
    friend BaseIter operator-(DiffT step, const BaseIter& iter) {
      return iter - step;
    }

    friend difference_type operator-(const BaseIter& first, const BaseIter& second) {
      return first && second ? first.ptr_ - second.ptr_ : 0;
    }

   protected:
    pointer ptr_ = nullptr;
  };

  using iterator = BaseIter<false>;                                      // NOLINT
  using const_iterator = BaseIter<true>;                                 // NOLINT
  using reverse_iterator = std::reverse_iterator<iterator>;              // NOLINT
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;  // NOLINT

 protected:
  BaseString(size_t length, size_t capacity, CharT* data) : length_(length), capacity_(capacity), data_(data) {
  }

  BaseString(size_t length, size_t capacity) : BaseString(length, capacity, Allocate(capacity)) {
  }

  explicit BaseString(size_t length) : BaseString(length, static_cast<size_t>(length * 2)) {
  }

 public:
  BaseString() : BaseString(0, 0, nullptr) {
  }

  template <class II>
  BaseString(II begin, II end) : BaseString(begin && end ? std::distance(begin, end) : 0) {
    BaseString::Copy(begin, end, this->begin());
  }

  BaseString(size_t length, const CharT& symbol) : BaseString(length) {
    Fill(begin(), end(), symbol);
  }

  BaseString(const std::initializer_list<CharT>& list) : BaseString(list.begin(), list.end()) {
  }

  BaseString(const BaseString& other) : BaseString(other.Size(), other.Capacity()) {
    BaseString::Copy(other.begin(), other.end(), begin());
  }

  BaseString(BaseString&& other) noexcept : BaseString(other.length_, other.capacity_, other.data_) {
    other.length_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }

  BaseString(const CharT* cstr)  // NOLINT
      : BaseString(const_iterator(cstr), const_iterator(cstr) + std::strlen(cstr)) {
  }

  BaseString(const CharT* cstr, size_t length)
      : BaseString(const_iterator(cstr), const_iterator(cstr) + std::min(length, std::strlen(cstr))) {
  }

  ~BaseString() {
    Deallocate();
  }

  BaseString& operator=(const BaseString& other) {
    if (this == &other) {
      return *this;
    }
    length_ = other.length_;
    capacity_ = other.capacity_;
    ResetData(Allocate(capacity_));
    BaseString::Copy(other.begin(), other.end(), data_);
    return *this;
  }

  BaseString& operator=(BaseString&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    length_ = other.length_;
    capacity_ = other.capacity_;
    ResetData(other.data_);
    other.length_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
    return *this;
  }

 protected:
  bool IsInBounds(size_t index) const {
    return index < Length();
  }

  void ThrowIfOutOfRange(size_t index) const {
    if (!IsInBounds(index)) {
      throw StringOutOfRange{};
    }
  }

  void ThrowIfEmpty() const {
    if (Empty()) {
      throw std::length_error{""};
    }
  }

  CharT* Allocate(size_t length) const {
    return alloc_.template allocate<CharT>(length);  // ?
  }

  void Deallocate() {
    allocator_traits::deallocate(alloc_, Data(), Capacity());
  }

  void Reallocate(size_t new_capacity) noexcept {
    size_t new_length = std::min(length_, new_capacity);
    auto new_arr = Allocate(new_capacity);
    BaseString::Copy(begin(), begin() + new_length, new_arr);
    Deallocate();
    capacity_ = new_capacity;
    length_ = new_length;
    data_ = new_arr;
  }

  template <class II, class OI>
  static void Copy(II src_begin, II src_end, OI dest_begin) {
    if (!src_begin || !src_end || !dest_begin) {
      return;
    }
    std::copy(src_begin, src_end, dest_begin);
  }

  template <class FI>
  static void Fill(FI begin, FI end, const CharT& symbol) {
    if (!begin || !end) {
      return;
    }
    std::fill(begin, end, symbol);
  }

  void ResetData(CharT* new_data) {
    Deallocate();
    data_ = new_data;
  }

 public:
  bool Empty() const {
    return Length() == 0;
  }

  bool Full() const {
    return Length() == Capacity();
  }

  // memory size in bytes
  size_t Size() const {
    return Length() * sizeof(CharT);
  }

  // length of string
  size_t Length() const {
    return length_;
  }

  // maximum size before realocation
  size_t Capacity() const {
    return capacity_;
  }

  // augmentation ratio of string capacity after reallocation
  double IncreaseFactor() const {
    return increase_factor_;
  }

  const_iterator begin() const {  // NOLINT
    return const_iterator(data_);
  }

  iterator begin() {  // NOLINT
    return iterator(data_);
  }

  const_iterator end() const {  // NOLINT
    return begin() + Length();
  }

  iterator end() {  // NOLINT
    return begin() + Length();
  }

  const_iterator cbegin() const {  // NOLINT
    return begin();
  }

  const_iterator cend() const {  // NOLINT
    return end();
  }

  const CharT& At(size_t index) const {
    ThrowIfOutOfRange(index);
    return data_[index];
  }
  CharT& At(size_t index) {
    ThrowIfOutOfRange(index);
    return data_[index];
  }

  const CharT& operator[](size_t index) const {
    return data_[index];
  }

  CharT& operator[](size_t index) {
    return data_[index];
  }

  // first element
  const CharT& Front() const {
    ThrowIfEmpty();
    return data_[0];
  }

  // first element
  CharT& Front() {
    ThrowIfEmpty();
    return data_[0];
  }

  // last element
  const CharT& Back() const {
    ThrowIfEmpty();
    return data_[Length() - 1];
  }

  // last element
  CharT& Back() {
    ThrowIfEmpty();
    return data_[Length() - 1];
  }

  const CharT* Data() const {
    return data_;
  }

  CharT* Data() {
    return data_;
  }

  const CharT* CStr() const {
    return Data();
  }

  CharT* CStr() {
    return Data();
  }

  void Clear() noexcept {
    length_ = 0;
  }

  void Swap(BaseString& other) {
    std::swap(alloc_, other.alloc_);
    std::swap(increase_factor_, other.increase_factor_);
    std::swap(length_, other.length_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }

  void PopBack() {
    ThrowIfEmpty();
    --length_;
  }

  void Reserve(size_t new_capacity) noexcept {
    if (new_capacity <= capacity_) {
      return;
    }
    Reallocate(new_capacity);
  }

  void PushBack(const CharT& value) noexcept {
    if (length_ < capacity_) {
      data_[length_++] = value;
      return;
    }
    Reserve(capacity_ > 0 ? capacity_ * increase_factor_ : 16);
    data_[length_++] = value;
  }

  void Resize(size_t new_length, const CharT& symbol = CharT()) {
    if (new_length <= length_) {
      length_ = new_length;
      return;
    }
    if (new_length >= capacity_) {
      Reserve(static_cast<double>(new_length) * increase_factor_);
    }
    std::fill(end(), begin() + new_length, symbol);
    length_ = new_length;
  }

  void ShrinkToFit() noexcept {
    Reallocate(length_);
  }

  friend BaseString& operator+=(BaseString& first, const BaseString& second) {
    size_t new_length = first.Length() + second.Length();
    if (new_length >= first.Capacity()) {
      first.Reserve(new_length * first.IncreaseFactor());
    }
    BaseString::Copy(second.begin(), second.end(), first.end());
    first.length_ = new_length;
    return first;
  }

  friend BaseString operator+(const BaseString& first, const BaseString& second) {
    BaseString result = first;
    result += second;
    return result;
  }

  template <class Cmp>
  static bool Compare(const BaseString& first, const BaseString& second, Cmp cmp = Cmp()) {
    size_t min_length = std::min(first.Length(), second.Length());
    for (size_t i = 0; i < min_length; ++i) {
      if (first[i] == second[i]) {
        continue;
      }
      return cmp(first[i], second[i]);
    }
    return cmp(first.Length(), second.Length());
  }

  friend bool operator<(const BaseString& first, const BaseString& second) {
    return Compare<std::less<CharT>>(first, second);
  }

  friend bool operator<=(const BaseString& first, const BaseString& second) {
    return Compare<std::less_equal<CharT>>(first, second);
  }

  friend bool operator>=(const BaseString& first, const BaseString& second) {
    return !(first < second);
  }

  friend bool operator>(const BaseString& first, const BaseString& second) {
    return !(first <= second);
  }

  friend bool operator==(const BaseString& first, const BaseString& second) {
    return Compare<std::equal_to<CharT>>(first, second);
  }

  friend bool operator!=(const BaseString& first, const BaseString& second) {
    return !(first == second);
  }

  friend std::ostream& operator<<(std::ostream& stream, const BaseString& str) {
    std::copy(str.begin(), str.end(), std::ostream_iterator<CharT>(stream));
    return stream;
  }

 protected:
  Alloc alloc_ = Alloc();
  double increase_factor_ = 2;
  size_t length_ = 0;
  size_t capacity_ = 0;
  CharT* data_ = nullptr;
};

using String = BaseString<char>;
