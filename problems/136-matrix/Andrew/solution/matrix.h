#pragma once

#include <numeric>
#include <stdexcept>
#include <cinttypes>

#include <initializer_list>
#include <array>
#include <iostream>

class MatrixOutOfRange {};

template <class T, size_t Rows, size_t Columns>
class Matrix {
public:
  using M = double;
protected:
  bool IsInside(size_t row, size_t column) const {
    return row < Rows && column < Columns;
  }
  void TestOutOfRange(size_t row, size_t column) const {
    if (!IsInside(row, column)) {
      throw MatrixOutOfRange {};
    }
  }

public:
  static size_t RowsNumber() {return Rows;}
  static size_t ColumnsNumber() {return Columns;}

public:
  const T& operator() (size_t row, size_t column) const {
    return data_[row][column];
  }
  T& operator() (size_t row, size_t column) {
    return data_[row][column];
    // return data_[row*Rows + column];
  }
  const T& At (size_t row, size_t column) const {
    TestOutOfRange(row, column);
    return this->operator()(row, column); 
  }
  T& At (size_t row, size_t column) {
    TestOutOfRange(row, column);
    return this->operator()(row, column);
  }
  auto GetTransposed() const {
    Matrix<T, Columns, Rows> result;
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        result.At(column, row) = At(row, column);
      }
    }
    return result;
  }

public:
  
  // template <class M>
  friend Matrix operator* (const Matrix& m, const M& multiplier) {
    Matrix result;
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        result.At(row, column) = m.At(row, column) * multiplier;
      }
    }
    return result;
  }
  // template <class M>
  friend Matrix operator* (const M& multiplier, const Matrix& m) {
    return m * multiplier;
  }
  // template <class M>
  Matrix& operator*= (const M& multiplier) {
    for (T& value : *this) {
      value *= multiplier;
    }
    return *this;
  }
  
  // template <class M>
  Matrix operator/ (const M& divisor) const {
    Matrix result;
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        result.At(row, column) = At(row, column) / divisor;
      }
    }
    return result;
  }
  // template <class M>
  Matrix& operator/= (const M& divisor) {
    for (T& value : *this) {
      value /= divisor;
    }
    return *this;
  }

  Matrix operator+ () const {return *this;}
  Matrix operator- () const {return *this * (-1);}

  friend Matrix operator+ (const Matrix& m1, const Matrix& m2) {
    Matrix result;
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        result.At(row, column) = m1.At(row, column) + m2.At(row, column);
      }
    }
    return result;
  }
  friend Matrix operator- (const Matrix& m1, const Matrix& m2) {
    Matrix result;
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        result.At(row, column) = m1.At(row, column) - m2.At(row, column);
      }
    }
    return result;
  }
  template <class Q, size_t NewColumns>
  auto operator* (const Matrix<Q, Columns, NewColumns>& other) const {
    Matrix<T, Rows, NewColumns> result;
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < NewColumns; ++column) {
        result.At(row, column) = T();
        for (size_t k = 0; k < Columns; k++) {
          result.At(row, column) += At(row, k) * other.At(k, column);
    }}}
    return result;
  }
  // template <class Q, size_t NewColumns>
  // friend auto operator* (const Matrix& m1, const Matrix<Q, Columns, NewColumns>& m2) {
  //   Matrix<T, Rows, NewColumns> result;
  //   for (size_t row = 0; row < Rows; ++row) {
  //     for (size_t column = 0; column < NewColumns; ++column) {
  //       result.At(row, column) = T();
  //       for (size_t k = 0; k < Columns; k++) {
  //         result.At(row, column) += m1.At(row, k) * m2.At(k, column);
  //   }}}
  //   return result;
  // }
  Matrix& operator+= (const Matrix& other) {
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        At(row, column) += other.At(row, column);
      }
    }
    return *this;
  }
  Matrix& operator-= (const Matrix& other) {
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        At(row, column) -= other.At(row, column);
      }
    }
    return *this;
  }
  template <class Q>
  Matrix& operator*= (const Matrix<Q, Columns, Columns>& other) {
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        At(row, column) = T();
        for (size_t k = 0; k < Columns; k++) {
          At(row, column) += At(row, k) * other.At(k, column);
    }}}
    return *this;
  }

  template <class Q, size_t OtherRows, size_t OtherColumns>
  bool operator== (const Matrix<Q, OtherRows, OtherColumns>& other) const {
    if constexpr (Rows != OtherRows || Columns != OtherColumns) {
      return false;
    }
    for (size_t row = 0; row < Rows; ++row) {
      for (size_t column = 0; column < Columns; ++column) {
        if (At(row, column) != other.At(row, column)) {
          return false;
    }}}
    return true;
  }

  template <class Q, size_t OtherRows, size_t OtherColumns>
  bool operator!= (const Matrix<Q, OtherRows, OtherColumns>& other) const {
    return !this->operator== (other);
  }

  friend std::ostream& operator<< (std::ostream& stream, const Matrix& m) {
    for (size_t row = 0; row < m.RowsNumber(); ++row) {
      for (size_t column = 0 ;; ++column) {
        stream << m.At(row, column);
        if (column == m.ColumnsNumber()-1) {
          break;
        }
        stream << " ";
      }
      stream << std::endl;
    }
    return stream;
  }
  friend std::istream& operator>> (std::istream& stream, Matrix& m) {
    for (T& value : m) {
      stream >> value;
    }
    return stream;
  }

public:
  // const T* begin() const {return data_->begin()->begin();} // NOLINT
  // T* begin() {return data_->begin()->begin();} // NOLINT
  // const T* end() const {return data_->end()->end();} // NOLINT
  // T* end() {return data_->end()->end();} // NOLINT

  const T* begin() const {return &data_[0][0];} // NOLINT
  T* begin() {return &data_[0][0];} // NOLINT
  const T* end() const {return &data_[Rows-1][Columns];} // NOLINT
  T* end() {return &data_[Rows-1][Columns];} // NOLINT

public:
  // Array<Array<T, Columns>, Rows> data_;
  T data_[Rows][Columns];
};

template <class T, size_t Rows, size_t Columns>
auto GetTransposed(Matrix<T, Rows, Columns> m) {
  return m.GetTransposed();
}