// A.cpp

#include <stdexcept>

#include <iostream>

struct SomethingWentWrong {};
struct Undefined {};

template <class T>
class Notebook {
 public:
  Notebook() : rows_(0), columns_(0), data_(nullptr) {
  }
  Notebook(size_t rows, size_t columns) : rows_(rows), columns_(columns), data_(new T*[rows]) {
    int symbol = 0;
    for (size_t i = 0; i < rows_; i++) {
      data_[i] = new T[columns_];
      for (size_t j = 0; j < columns_; j++) {
        do {
          symbol = std::getchar();
        } while (symbol != '0' && symbol != '1');

        if (symbol == '0') {
          data_[i][j] = 0;
        } else if (symbol == '1') {
          data_[i][j] = 1;
        } else {
          throw SomethingWentWrong{};
        }
      }
    }
  }
  ~Notebook() {
    for (size_t i = 0; i < rows_; i++) {
      delete[] data_[i];
    }
    delete[] data_;
  }

 public:
  bool IsInside(size_t i, size_t j) const {
    return i < rows_ && j < columns_;
  }

  size_t Size(bool vertical) const {
    return (vertical ? rows_ : columns_);
  }

  bool IsInside(size_t index, bool vertical) const {
    return index < Size(vertical);
  }

  const T& At(size_t i, size_t j) const {
    if (IsInside(i, j)) {
      return data_[i][j];
    }
    throw std::out_of_range{"Notebook::At() const"};
  }
  T& At(size_t i, size_t j) {
    if (IsInside(i, j)) {
      return data_[i][j];
    }
    throw std::out_of_range{"Notebook::At()"};
  }

  bool IsLine(size_t index, bool vertical = false) const {
    if (!IsInside(index, !vertical)) {
      throw std::out_of_range{"Notebook::IsLine()"};
    }
    if (Size(vertical) < 2) {
      throw Undefined{};
    }
    if (vertical) {
      return At(0, index) == 1 && At(1, index) == 1;
    }
    return At(index, 0) == 1 && At(index, 1) == 1;
  }

  size_t CountLines(bool vertical = false) const {
    size_t count = 0;
    for (size_t index = 0; index < Size(!vertical); ++index) {
      if (IsLine(index, vertical)) {
        ++count;
      }
    }
    return count;
  }

  size_t LinesSpacing(bool vertical = false) const {
    size_t count = 0;
    size_t first_line_index = 0;
    for (size_t i = 0; i < Size(!vertical); ++i) {
      if (IsLine(i, vertical)) {
        if (count == 0) {
          first_line_index = i;
          ++count;
        } else {
          return i - first_line_index;
        }
      }
    }
    throw Undefined{};
  }

  auto Type() const {
    try {
      size_t hlines = CountLines();
      size_t vlines = CountLines(true);

      if (hlines > 0 && vlines > 0) {
        return "Square";
      }
      if (hlines + vlines < 2) {
        throw Undefined{};
      }
      if (hlines > 1 && vlines == 0) {
        if (columns_ < LinesSpacing()) {
          throw Undefined{};
        }
        return "Line";
      }
      if (hlines == 0 && vlines > 1) {
        if (rows_ < LinesSpacing(true)) {
          throw Undefined{};
        }
        return "Vertical line";
      }
    } catch (Undefined) {
      return "?";
    }
    throw SomethingWentWrong{};
  }

 protected:
  size_t rows_;
  size_t columns_;
  T** data_;
};

using SquaresType = int;

int main() {
  size_t n = 0;
  size_t m = 0;

  std::cin >> n >> m;

  Notebook<SquaresType> notebook(n, m);

  std::cout << notebook.Type();

  return 0;
}