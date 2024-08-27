#include "string_view.h"

StringView::StringView () : string_(nullptr), length_(0) {}
StringView::StringView (const char* string) // NOLINT
: string_(string), length_(strlen(string)) {}
StringView::StringView (const char* string, size_t length)
: string_(string), length_(length) {}
StringView::StringView (const StringView& other) : StringView (other.Data(), other.Size()) {}
StringView& StringView::operator=(const StringView& other) {
  string_ = other.Data();
  length_ = other.Size();
  return *this;
};

const char& StringView::operator[](size_t index) const {
  return string_[index];
}

char StringView::Front() const {
  return string_[0];
}
char StringView::Back() const {
  return string_[length_-1];
}
size_t StringView::Size() const {
  return length_;
}
size_t StringView::Length() const {
  return Size();
}
bool StringView::Empty() const {
  return length_ == 0;
}
const char* StringView::Data() const {
  return string_;
}
void StringView::Swap(StringView& other) {
  std::swap(string_, other.string_);
  std::swap(length_, other.length_);
}
void StringView::RemovePrefix(size_t prefix_size) {
  string_ += prefix_size;
  length_ -= prefix_size;
}
void StringView::RemoveSuffix(size_t suffix_size) {
  length_ -= suffix_size;
}
StringView StringView::Substr(size_t pos, size_t count) const {
  return {Data() + pos, std::min(count, Size() - pos)};
}

std::ostream& operator<< (std::ostream& stream, const StringView& string) {
  for (size_t i = 0; i < string.Length(); ++i) {
    stream << string[i];
  }
  return stream;
}