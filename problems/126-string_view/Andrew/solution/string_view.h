#pragma once

#include <stddef.h>
#include <cstring>
#include <cstdint>
#include <utility>
#include <iostream>

class StringView
{
public:
  StringView ();
  StringView (const char* string); // NOLINT
  StringView (const char* string, size_t length);
  StringView (const StringView& other);
  StringView& operator=(const StringView& other);

  const char& operator[] (size_t index) const;

  char Front() const;
  char Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  const char* Data() const;

  void Swap(StringView& other);
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count = -1) const;

  friend std::ostream& operator<< (std::ostream& stream, const StringView& string);

protected:
  const char* string_;
  size_t length_;
};