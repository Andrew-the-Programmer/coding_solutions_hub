#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include <new>

namespace detail {
namespace compare {
template <class CmpValues, class CmpLength, class Iterator,
          std::enable_if_t<
              std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>,
              bool> = true>
bool lexicographical_compare(  // NOLINT
    Iterator first_begin, Iterator first_end, Iterator second_begin, Iterator second_end,
    CmpValues cmp_values = CmpValues(), CmpLength cmp_length = CmpLength()) {
  auto first_iter = first_begin;
  auto second_iter = second_begin;
  for (;; ++first_iter, ++second_iter) {
    if (first_iter == first_end || second_iter == second_end) {
      return cmp_length(std::distance(first_iter, first_end), std::distance(second_iter, second_end));
    }
    if (*first_iter == *second_iter) {
      continue;
    }
    return cmp_values(*first_iter, *second_iter);
  }
  throw std::runtime_error("lexicographical_compare: reached the end");
}

template <template <class> class Cmp, class Iterator, class iterator_traits = std::iterator_traits<Iterator>,
          std::enable_if_t<std::is_base_of_v<std::input_iterator_tag, typename iterator_traits::iterator_category>,
                           bool> = true>
bool lexicographical_compare(  // NOLINT
    Iterator first_begin, Iterator first_end, Iterator second_begin, Iterator second_end) {
  using T = typename iterator_traits::value_type;
  using D = typename iterator_traits::difference_type;
  return lexicographical_compare(first_begin, first_end, second_begin, second_end, Cmp<T>{}, Cmp<D>{});
}

template <template <class, class> class Cmp, class Iterator, class iterator_traits = std::iterator_traits<Iterator>,
          std::enable_if_t<std::is_base_of_v<std::input_iterator_tag, typename iterator_traits::iterator_category>,
                           bool> = true>
bool lexicographical_compare(  // NOLINT
    Iterator first_begin, Iterator first_end, Iterator second_begin, Iterator second_end) {
  using T = typename iterator_traits::value_type;
  using D = typename iterator_traits::difference_type;
  return lexicographical_compare(first_begin, first_end, second_begin, second_end, Cmp<T, T>{}, Cmp<D, D>{});
}
}  // namespace compare

namespace vector_allocator {
template <class T>
struct BasicAllocator {
  using value_type = T;         // NOLINT
  using pointer = value_type*;  // NOLINT
  using size_type = size_t;     // NOLINT

  [[nodiscard]] constexpr pointer allocate(size_type size) const {  // NOLINT
    return static_cast<pointer>(::operator new(size * sizeof(value_type)));
  }

  constexpr void deallocate(pointer ptr, [[maybe_unused]] size_type size = 0) const {  // NOLINT
    // clang error
    // ::operator delete(ptr, size * sizeof(value_type));  // NOLINT
    std::allocator<value_type>().deallocate(ptr, size);
  }

  template <class... Args>
  void construct(pointer ptr, Args&&... args) const {  // NOLINT
    new (ptr) value_type(std::forward<Args>(args)...);
  }

  void destroy(pointer ptr) const {  // NOLINT
    ptr->~value_type();
  }
};
}  // namespace vector_allocator

namespace vector_memory {
template <class Alloc>
using allocator_traits = std::allocator_traits<Alloc>;  // NOLINT
template <class Iter>
using iterator_traits = std::iterator_traits<Iter>;  // NOLINT

template <class Alloc, class SizeType>
static auto allocate(  // NOLINT
    Alloc& alloc, SizeType count) -> allocator_traits<Alloc>::pointer {
  if (count == 0) {
    return nullptr;
  }
  return allocator_traits<Alloc>::allocate(alloc, count);
}

template <class Alloc, class Pointer, class SizeType, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void deallocate(Alloc& allocator, Pointer ptr, SizeType count) {  // NOLINT
  if (!ptr) {
    return;
  }
  allocator_traits<Alloc>::deallocate(allocator, ptr, count);
}

template <class Alloc, class Pointer, class... Args, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void construct(Alloc& alloc, Pointer ptr, Args&&... args) {  // NOLINT
  allocator_traits<Alloc>::construct(alloc, ptr, std::forward<Args>(args)...);
}

template <class Alloc, class Pointer, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void destroy(Alloc& alloc, Pointer ptr) {  // NOLINT
  allocator_traits<Alloc>::destroy(alloc, ptr);
}

template <class Alloc, class Pointer, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void destroy(Alloc& alloc, Pointer begin, Pointer end) {  // NOLINT
  for (; begin != end; ++begin) {
    destroy(alloc, begin);
  }
}

template <class Alloc, class Pointer, class... Args, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void safe_construct(Alloc& alloc, Pointer ptr, Args&&... args) {  // NOLINT
  try {
    construct(alloc, ptr, std::forward<Args>(args)...);
  } catch (...) {
    destroy(alloc, ptr);
    throw;
  }
}

template <class Alloc, class InputIter, class Pointer, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void uninitialized_copy(Alloc& alloc, InputIter src_begin, InputIter src_end, Pointer dest_begin) {  // NOLINT
  auto dest_iter = dest_begin;
  try {
    for (auto src_iter = src_begin; src_iter != src_end; ++src_iter, ++dest_iter) {
      construct(alloc, dest_iter, *src_iter);
    }
  } catch (...) {
    destroy(alloc, dest_begin, dest_iter);
    throw;
  }
}

template <class Alloc, class InputIter, class Pointer, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void uninitialized_move(Alloc& alloc, InputIter src_begin, InputIter src_end, Pointer dest_begin) {  // NOLINT
  uninitialized_copy(alloc, std::make_move_iterator(src_begin), std::make_move_iterator(src_end), dest_begin);
}

template <class Alloc, class InputIter, class Pointer, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void uninitialized_move_if_noexcept(Alloc& alloc, InputIter src_begin, InputIter src_end,  // NOLINT
                                    Pointer dest_begin) {
  using TypeUnderDest = typename iterator_traits<Pointer>::value_type;
  using TypeUnderSrc = typename iterator_traits<InputIter>::value_type;
  constexpr bool kMovable = std::is_nothrow_constructible_v<TypeUnderDest, std::add_rvalue_reference_t<TypeUnderSrc>>;
  if constexpr (kMovable) {
    uninitialized_move(alloc, src_begin, src_end, dest_begin);
  } else {
    uninitialized_copy(alloc, src_begin, src_end, dest_begin);
  }
}

template <class Alloc, class Pointer, class... Args, std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void uninitialized_fill(Alloc& alloc, Pointer begin, Pointer end, Args&&... args) {  // NOLINT
  auto iter = begin;
  try {
    for (; iter != end; ++iter) {
      construct(alloc, iter, args...);
    }
  } catch (...) {
    destroy(alloc, begin, iter);
    throw;
  }
}

// if KSingle == true: will safe_construct(alloc, begin, std::forward<Args>(args)...);
// else: will uninitialized_fill(alloc, begin, end, std::forward<Args>(args)...);
// TODO{4}: rename
template <bool KSingle, class Alloc, class Pointer, class... Args,
          std::enable_if_t<std::is_pointer_v<Pointer>, bool> = true>
void uninitialized_fill_o(Alloc& alloc, Pointer begin, Pointer end, Args&&... args) {  // NOLINT
  if constexpr (KSingle) {
    safe_construct(alloc, begin, std::forward<Args>(args)...);
  } else {
    uninitialized_fill(alloc, begin, end, std::forward<Args>(args)...);
  }
}
}  // namespace vector_memory
}  // namespace detail

/// @brief
/// @tparam T - storabe type
/// @tparam Alloc - allocator. copy and move constructors should be noexcept.
template <class T, class Alloc = detail::vector_allocator::BasicAllocator<T>>
class Vector {
  /*// TODO: make methods constexpr (since c++20).
   */
  /*// TODO{5}: fix duplicated methods with deducing this (since c++23):
    GetAllocator, begin, end, At, [], Front, Back, Data, _get_pointer, _begin_pointer, _end_pointer
  */

 public:  //^ public types declarations
  template <bool IsConst>
  struct BaseIter;

  using value_type = T;                                                  // NOLINT
  using pointer = value_type*;                                           // NOLINT
  using const_pointer = const value_type*;                               // NOLINT
  using reference = value_type&;                                         // NOLINT
  using const_reference = const value_type&;                             // NOLINT
  using allocator_type = Alloc;                                          // NOLINT
  using allocator_traits = std::allocator_traits<allocator_type>;        // NOLINT
  using size_type = size_t;                                              // NOLINT
  using iterator = BaseIter<false>;                                      // NOLINT
  using const_iterator = BaseIter<true>;                                 // NOLINT
  using reverse_iterator = std::reverse_iterator<iterator>;              // NOLINT
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;  // NOLINT

  // required for problem
  using ValueType = value_type;
  using Pointer = pointer;
  using ConstPointer = const_pointer;
  using Reference = reference;
  using ConstReference = const_reference;
  using SizeType = size_type;
  using Iterator = iterator;
  using ConstIterator = const_iterator;
  using ReverseIterator = reverse_iterator;
  using ConstReverseIterator = const_reverse_iterator;

 protected:
  class _constructor_pr {};                      // NOLINT
  class _constructor_pr_size_alloc {};           // NOLINT
  class _constructor_pr_size_alloc_and_init {};  // NOLINT

 protected:  //^ protected constructorsm
  // (-1)
  Vector(_constructor_pr, size_type size, size_type capacity, pointer data, const allocator_type& alloc) noexcept
      : Vector(_constructor_pr{}, size, capacity, data, allocator_type{alloc}) {
  }

  Vector(_constructor_pr, size_type size, size_type capacity, pointer data, allocator_type&& alloc) noexcept
      : alloc_(std::move(alloc)), size_(size), capacity_(capacity), data_(data) {
  }

  // (-2)
  // allocates memory using <alloc> for <capacity> elements.
  // first <size> elements are uninitialised.
  // TODO{4}: fix
  Vector(_constructor_pr, size_type size, size_type capacity, const allocator_type& alloc = allocator_type())
      : alloc_(alloc)
      , size_(size)
      , capacity_(capacity)
      , data_(detail::vector_memory::allocate(GetAllocator(), capacity)) {
  }

  // (-3)
  // allocates memory using <alloc> for capacity elements, where capacity is determined by <size>.
  // (capacity = Vector::_GetInitCapacity(size)).
  // first <size> elements are uninitialised.
  Vector(_constructor_pr_size_alloc, size_type size, const allocator_type& alloc = allocator_type())
      : Vector(_constructor_pr{}, size, Vector::_GetInitCapacity(size), alloc) {
  }

  // (-4)
  // allocates memory using <alloc> for <capacity> elements, where capacity is determined by <size>.
  // (capacity = Vector::_GetInitCapacity(size)).
  // constructs first <size> elements with <args...>
  template <class... Args>
  Vector(_constructor_pr_size_alloc_and_init, size_type size, const allocator_type& alloc, Args&&... args)
      : Vector(_constructor_pr_size_alloc{}, size, alloc) {
    try {
      detail::vector_memory::uninitialized_fill(GetAllocator(), _begin_pointer(), _end_pointer(),
                                                std::forward<Args>(args)...);
    } catch (...) {
      // elements were destroyed in uninitialized_fill
      _deallocate_data();

      // very important!
      // since deligated constructor was called, destructor will alse be called.
      // if we don't nullify vector, destructor will deallocate already deallocated data
      // and destroy already destroyed elements.
      _set_data(nullptr);
      // consider: _nullify() instead of _set_data(nullptr)
      // _nullify() is possibly costly (not now), but more straightforward.
      // _set_data(nullprt) works, because ~Vector with nullptr data does nothing

      // consider: _set_size(0)
      //? may be implementation defined

      throw;
    }
  }

 public:  //^ public constructors and a destructor
  /* https://en.cppreference.com/w/cpp/container/vector/vector */

  // (1)
  constexpr Vector() noexcept(noexcept(allocator_type{})) : Vector(allocator_type{}) {
  }

  // (2)
  constexpr explicit Vector(const allocator_type& alloc) noexcept : Vector(_constructor_pr{}, 0, 0, nullptr, alloc) {
  }

  // (3)
  constexpr Vector(size_type size, const_reference default_value, const allocator_type& alloc = allocator_type())
      : Vector(_constructor_pr_size_alloc_and_init{}, size, alloc, default_value) {
  }

  // (4)
  constexpr explicit Vector(size_type size, const allocator_type& alloc = allocator_type())
      : Vector(_constructor_pr_size_alloc_and_init{}, size, alloc) {
  }

  // (5)
  // consider/todo: should be input iterator?
  // TODO{4}: fix: std::distance
  // TODO{4}: fix code duplication with constructor (-4)
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  constexpr Vector(Iterator begin, Iterator end, const allocator_type& alloc = allocator_type())
      : Vector(_constructor_pr_size_alloc{}, static_cast<size_type>(std::distance(begin, end)), alloc) {
    try {
      detail::vector_memory::uninitialized_copy(this->GetAllocator(), begin, end, this->Data());
    } catch (...) {
      // see constructor (-4) for details
      _deallocate_data();
      _set_data(nullptr);
      throw;
    }
  }

  // (6)
  // check: allocator awareness
  constexpr Vector(const Vector& other) : Vector(other, other.GetAllocator()) {
  }

  // (7)
  // TODO{4}: fix
  // check: allocator awareness
  constexpr Vector(const Vector& other, const allocator_type& alloc) : Vector(alloc) {
    *this = other;
  }

  // (8)
  constexpr Vector(Vector&& other) noexcept : Vector(std::move(other), std::move(other.GetAllocator())) {
  }

  // (9)
  // CHECK: allocator awareness
  constexpr Vector(Vector&& other, const allocator_type& alloc) noexcept
      : Vector(std::move(other), allocator_type{alloc}) {
  }

  // (9.1)
  // helper for constructors (8) and (9)
  // needed for solving allocator copy in constructors (8) and (9)
  // CHECK: allocator awareness
  // CONSIDER: _copy_fields(std::move(other))
  constexpr Vector(Vector&& other, allocator_type&& alloc) noexcept
      : Vector(_constructor_pr{}, other.Size(), other.Capacity(), other.Data(), std::move(alloc)) {
    other._nullify();
  }

  // (10)
  //? why do we only need this constructor for initializer_list?
  constexpr Vector(std::initializer_list<value_type> list, const allocator_type& alloc = allocator_type())
      : Vector(std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()), alloc) {
  }

  // TODO{2}: implement constructor (11) (since c++23).

  ~Vector() {
    _clear_data();
  }

 protected:  //^ simple protected methods
  // TODO{3}: rename
  static size_type _GetInitCapacity(size_type size) noexcept {  // NOLINT
    return size;
  }

  // TODO{3}: rename
  static size_type IncreaseFactorResult(size_type size) noexcept {  // NOLINT
    if (size == 0) {
      return 1;
    }
    return static_cast<size_type>(static_cast<double>(size) * Vector::GetIncreaseFactor());
  }

  bool IsInBounds(size_type index) const {
    return index < Size();
  }

  // throws std::out_of_range if index >= this->Size()
  // TODO{3}: improve throw msg
  void ThrowIfOutOfRange(size_type index) const {
    if (!IsInBounds(index)) {
      throw std::out_of_range{"Vector::ThrowIfOutOfRange"};
    }
  }

  // throws std::length_error if this->Empty()
  void ThrowIfEmpty() const {
    if (Empty()) {
      throw std::length_error{"Vector::ThrowIfEmpty: this->Size() == 0"};
    }
  }

  void _set_size(size_type new_size) noexcept {  // NOLINT
    size_ = new_size;
  }

  void _set_capacity(size_type new_capacity) noexcept {  // NOLINT
    capacity_ = new_capacity;
  }

  void _set_data(pointer new_data) noexcept {  // NOLINT
    data_ = new_data;
  }

  void _set_allocator(const allocator_type& new_allocator) noexcept {  // NOLINT
    alloc_ = new_allocator;
  }

  void _nullify() noexcept {  // NOLINT
    _set_size(0);
    _set_capacity(0);
    _set_data(nullptr);
    // _set_allocator(allocator_type{});  //? why?
  }

  void _copy_fields(const Vector& other) {  // NOLINT
    _set_size(other.Size());
    _set_capacity(other.Capacity());
    _set_data(other.Data());
    _set_allocator(other.GetAllocator());
  }

  void _copy_fields(Vector&& other) {  // NOLINT
    _set_size(other.Size());
    _set_capacity(other.Capacity());
    _set_data(other.Data());
    _set_allocator(std::move(other.GetAllocator()));

    other._nullify();
  }

  void _destroy_elements() {  // NOLINT
    detail::vector_memory::destroy(GetAllocator(), _begin_pointer(), _end_pointer());
  }

  void _deallocate_data() {  // NOLINT
    if (Data()) {
      detail::vector_memory::deallocate(GetAllocator(), Data(), Capacity());
    }
  }

  void _clear_data() {  // NOLINT
    _destroy_elements();
    _deallocate_data();
  }

  pointer _get_pointer(size_type index) {  // NOLINT
    if (!Data()) {
      return nullptr;
    }
    return Data() + index;
  }

  const_pointer _get_pointer(size_type index) const {  // NOLINT
    if (!Data()) {
      return nullptr;
    }
    return Data() + index;
  }

  pointer _begin_pointer() {  // NOLINT
    return _get_pointer(0);
  }
  const_pointer _begin_pointer() const {  // NOLINT
    return _get_pointer(0);
  }

  pointer _end_pointer() {  // NOLINT
    return _get_pointer(Size());
  }
  const_pointer _end_pointer() const {  // NOLINT
    return _get_pointer(Size());
  }

  constexpr const allocator_type& GetAllocator() const {
    return alloc_;
  }

  constexpr allocator_type& GetAllocator() {
    return alloc_;
  }

 protected:  //^ complex protected methods
  // CHECK: new_capacity = 0
  // CHECK: deallocate(nullptr)
  // consider: use _resize
  void Reallocate(size_type new_capacity) {
    size_type new_size = std::min(Size(), new_capacity);
    auto& alloc = GetAllocator();
    auto new_arr = detail::vector_memory::allocate(alloc, new_capacity);

    try {
      detail::vector_memory::uninitialized_move_if_noexcept(alloc, begin(), begin() + new_size, new_arr);
    } catch (...) {
      detail::vector_memory::deallocate(alloc, new_arr, new_capacity);
      throw;
    }

    _clear_data();

    this->_set_data(new_arr);
    this->_set_size(new_size);
    this->_set_capacity(new_capacity);
  }

  // TODO{7}: fix (wtf is this???)
  // note: _resize(new_size, {}) is CE (see Resize(size_type, const_reference))
  template <bool KSingle, class... Args>
  void _resize(size_type new_size, Args&&... args) {  // NOLINT
    auto& alloc = GetAllocator();

    if (new_size <= Capacity()) {
      if (new_size <= Size()) {
        detail::vector_memory::destroy(alloc, _begin_pointer() + new_size, _end_pointer());
      } else {
        detail::vector_memory::uninitialized_fill_o<KSingle>(alloc, _end_pointer(), _begin_pointer() + new_size,
                                                             std::forward<Args>(args)...);
      }
      _set_size(new_size);
      return;
    }

    // new_size > Capacity():

    auto new_capacity = IncreaseFactorResult(new_size);
    // new data
    auto m = detail::vector_memory::allocate(alloc, new_capacity);

    auto m_begin = m;
    auto m_end = m_begin + Size();
    auto m_new_end = m_begin + new_size;

    // move/copy elements to m
    constexpr bool kMove = std::is_nothrow_move_constructible_v<value_type>;  // TODO{4}: move somewhere else
    if constexpr (kMove) {
      detail::vector_memory::uninitialized_move(alloc, begin(), end(), m_begin);
    } else {
      try {
        detail::vector_memory::uninitialized_copy(alloc, begin(), end(), m_begin);
      } catch (...) {
        detail::vector_memory::deallocate(alloc, m, new_capacity);
        throw;
      }
    }

    // construct new elements in m
    try {
      detail::vector_memory::uninitialized_fill_o<KSingle>(alloc, m_end, m_new_end, std::forward<Args>(args)...);
    } catch (...) {
      if constexpr (kMove) {
        detail::vector_memory::uninitialized_move(alloc, m_begin, m_end, _begin_pointer());
      }
      detail::vector_memory::destroy(alloc, m_begin, m_end);
      detail::vector_memory::deallocate(alloc, m, new_capacity);
      throw;
    }

    _clear_data();

    this->_set_data(m);
    this->_set_size(new_size);
    this->_set_capacity(new_capacity);
  }

 public:  //^ simple public methods
  bool Empty() const {
    return Size() == 0;
  }

  bool Full() const {
    return Size() == Capacity();
  }

  // elements count
  size_type Size() const {
    return size_;
  }

  // maximum size before realocation
  size_type Capacity() const {
    return capacity_;
  }

  // augmentation ratio of vector capacity after reallocation
  static double GetIncreaseFactor() {
    return kIncreaseFactor;
  }

  const_iterator begin() const {  // NOLINT
    return const_iterator(_begin_pointer());
  }

  iterator begin() {  // NOLINT
    return iterator(_begin_pointer());
  }

  const_iterator end() const {  // NOLINT
    return const_iterator(_end_pointer());
  }

  iterator end() {  // NOLINT
    return iterator(_end_pointer());
  }

  const_iterator cbegin() const {  // NOLINT
    return begin();
  }

  const_iterator cend() const {  // NOLINT
    return end();
  }

  reverse_iterator rbegin() {  // NOLINT
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {  // NOLINT
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() {  // NOLINT
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const {  // NOLINT
    return const_reverse_iterator(begin());
  }

  const_reverse_iterator crbegin() const {  // NOLINT
    return rbegin();
  }

  const_reverse_iterator crend() const {  // NOLINT
    return rend();
  }

  const_reference At(size_type index) const {
    ThrowIfOutOfRange(index);
    return (*this)[index];
  }

  reference At(size_type index) {
    ThrowIfOutOfRange(index);
    return (*this)[index];
  }

  const_reference operator[](size_type index) const {
    return Data()[index];
  }

  reference operator[](size_type index) {
    return Data()[index];
  }

  // first element
  // throws std::length_error if vector is empty (size() == 0)
  const_reference Front() const {
    ThrowIfEmpty();
    return *begin();
  }

  // first element
  // throws std::length_error if vector is empty (size() == 0)
  reference Front() {
    ThrowIfEmpty();
    return *begin();
  }

  // last element
  // throws std::length_error if vector is empty (size() == 0)
  const_reference Back() const {
    ThrowIfEmpty();
    return *(end() - 1);
  }

  // last element
  // throws std::length_error if vector is empty (size() == 0)
  reference Back() {
    ThrowIfEmpty();
    return *(end() - 1);
  }

  // returns pointer to first element
  // or nullptr if vector is empty (size() == 0)
  const_pointer Data() const {
    return data_;
  }

  // returns pointer to first element
  // or nullptr if vector is empty (size() == 0)
  pointer Data() {
    return data_;
  }

 public:  //^ complex public methods
  // TODO: fix allocator awareness
  Vector& operator=(const Vector& other) {
    if (this == &other) {
      return *this;
    }
    constexpr bool kPropagate = allocator_traits::propagate_on_container_copy_assignment::value;
    allocator_type new_alloc = kPropagate ? other.GetAllocator() : this->GetAllocator();
    pointer new_arr = detail::vector_memory::allocate(new_alloc, other.Capacity());

    try {
      detail::vector_memory::uninitialized_copy(new_alloc, other.begin(), other.end(), new_arr);
    } catch (...) {
      detail::vector_memory::deallocate(new_alloc, new_arr, other.Capacity());
      throw;
    }

    _clear_data();

    this->_set_allocator(new_alloc);  // noexcept
    this->_set_data(new_arr);
    this->_set_size(other.Size());
    this->_set_capacity(other.Capacity());

    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    _clear_data();
    _copy_fields(std::move(other));

    return *this;
  }

  void Clear() noexcept {
    _destroy_elements();
    _set_size(0);
  }

  void Swap(Vector& other) {
    std::swap(alloc_, other.alloc_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }

  // TODO{2}: Swap(Vector&&)

  void PopBack() {
    ThrowIfEmpty();
    detail::vector_memory::destroy(GetAllocator(), _end_pointer() - 1);
    _set_size(Size() - 1);
  }

  void Reserve(size_type new_capacity) {
    if (new_capacity <= Capacity()) {
      return;
    }
    Reallocate(new_capacity);
  }

  template <class... Args>
  void EmplaceBack(Args&&... args) {
    _resize<true>(Size() + 1, std::forward<Args>(args)...);
  }

  void PushBack(const_reference value) {
    EmplaceBack(value);
  }

  void PushBack(value_type&& value) {
    EmplaceBack(std::move(value));
  }

  void Resize(size_type new_size) {
    _resize<false>(new_size);
  }

  void Resize(size_type new_size, const_reference def_value) {
    _resize<false>(new_size, def_value);
  }

  void ShrinkToFit() noexcept {
    Reallocate(Size());
  }

  // TODO: move compare to base class

  template <template <class> class Cmp>
  static bool Compare(const Vector& first, const Vector& second) {
    return detail::compare::lexicographical_compare<Cmp>(first.begin(), first.end(), second.begin(), second.end());
  }

  friend bool operator<(const Vector& first, const Vector& second) {
    return Compare<std::less>(first, second);
  }

  friend bool operator<=(const Vector& first, const Vector& second) {
    return Compare<std::less_equal>(first, second);
  }

  friend bool operator>=(const Vector& first, const Vector& second) {
    return !(first < second);
  }

  friend bool operator>(const Vector& first, const Vector& second) {
    return !(first <= second);
  }

  friend bool operator==(const Vector& first, const Vector& second) {
    return Compare<std::equal_to>(first, second);
  }

  friend bool operator!=(const Vector& first, const Vector& second) {
    return !(first == second);
  }

 protected:  //^ fields
  allocator_type alloc_ = allocator_type();
  size_type size_ = 0;
  size_type capacity_ = 0;
  pointer data_ = nullptr;

 public:  //^ static fields
  static constexpr double kIncreaseFactor = 2;
};

template <class T, class Alloc>
template <bool IsConst>
struct Vector<T, Alloc>::BaseIter {
 public:
  friend class Vector<T, Alloc>;

 public:
  using value_type = T;                                                                    // NOLINT
  using pointer = typename std::conditional_t<IsConst, const value_type*, value_type*>;    // NOLINT
  using reference = typename std::conditional_t<IsConst, const value_type&, value_type&>;  // NOLINT
  using difference_type = int64_t;                                                         // NOLINT
  using iterator_category = typename std::random_access_iterator_tag;                      // NOLINT

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
    ++copy;
    return copy;
  }

  BaseIter& operator--() {
    --ptr_;
    return *this;
  }

  BaseIter operator--(int) {
    BaseIter copy = *this;
    --copy;
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

  template <class DiffT = difference_type>
  BaseIter& operator+=(DiffT step) {
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
