// A.h

#include <stdexcept>

#include <iostream>

struct SomethingWentWrong {};
struct Undefined {};

template <class T>
struct Square {

  T cur_value = T();
  T new_value = T();

  void Update() {
    cur_value = new_value;
  }
};

template <class T>
class Canvas {

  using S = Square<T>;

 public:
  Canvas() : rows_(0), columns_(0), data_(nullptr) {
  }
  Canvas(size_t rows, size_t columns) : rows_(rows), columns_(columns), data_(new S*[rows]) {
    for (size_t i = 0; i < rows; i++) {
      data_[i] = new S[columns];
      for (size_t j = 0; j < columns; j++) {
        std::cin >> At(i, j).cur_value;
      }
    }
  }
  ~Canvas() {
    for (size_t i = 0; i < rows_; i++) {
      delete[] data_[i];
    }
    delete[] data_;
  }

 public:
  bool IsInside(size_t i, size_t j) const {
    return i < rows_ && j < columns_;
  }
  const S& At(size_t i, size_t j) const {
    if (IsInside(i, j)) {
      return data_[i][j];
    }
    throw std::out_of_range{"Canvas::At() const"};
  }
  S& At(size_t i, size_t j) {
    if (IsInside(i, j)) {
      return data_[i][j];
    }
    throw std::out_of_range{"Canvas::At()"};
  }

 protected:
  size_t CountNeighbors(size_t i, size_t j) {
    size_t count = 0;
    for (size_t row = (i == 0 ? 0 : i - 1); row <= i + 1; ++row) {
      for (size_t column = (j == 0 ? 0 : j - 1); column <= j + 1; ++column) {
        if (IsInside(row, column) && (row != i || column != j)) {
          if (At(row, column).cur_value) {
            ++count;
          }
        }
      }
    }
    return count;
  }
  void Update(size_t i, size_t j) {
    auto count_neighbors = CountNeighbors(i, j);
    T& cur_value = At(i, j).cur_value;
    T& new_value = At(i, j).new_value;

    if (cur_value) {
      if (count_neighbors == 2 || count_neighbors == 3) {
        new_value = 1;
      } else {
        new_value = 0;
      }
    } else if (!cur_value) {
      if (count_neighbors == 3) {
        new_value = 1;
      } else {
        new_value = 0;
      }
    }
    std::cout << "";
  }
  void Update() {
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < columns_; ++j) {
        Update(i, j);
      }
    }
  }
  void Increment() {
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < columns_; ++j) {
        At(i, j).Update();
      }
    }
  }

 public:
  void Increment(size_t time) {
    for (size_t t = 0; t < time; ++t) {
      Update();
      Increment();
    }
  }
  template <class Os = std::ostream&>
  void Output(Os stream = std::cout) {
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < columns_; ++j) {
        stream << At(i, j).cur_value << " ";
      }
      stream << std::endl;
    }
  }

 protected:
  size_t rows_;
  size_t columns_;
  S** data_;
};

using SquaresType = int;

int main() {
  size_t n = 0;
  size_t t = 0;

  std::cin >> n >> t;

  Canvas<SquaresType> canvas(n, n);

  canvas.Increment(t);

  canvas.Output();

  return 0;
}