#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <stdexcept>

class MatrixOutOfRange : public std::out_of_range {
public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

class MatrixIsDegenerateError : public std::runtime_error {
public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

template <class T, size_t W, size_t H>
class Matrix {
public:
  T mass[W][H];

  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T& operator()(size_t rows, size_t columns);
  const T& operator()(size_t rows, size_t columns) const;

  T& At(size_t rows, size_t columns) {
    if (rows >= W || columns >= H) {
      throw MatrixOutOfRange{};
    }
    return mass[rows][columns];
  }

  const T& At(size_t rows, size_t columns) const {
    if (rows >= W || columns >= H) {
      throw MatrixOutOfRange{};
    }
    return mass[rows][columns];
  }
};

template <class T, size_t W, size_t H>
inline size_t Matrix<T, W, H>::RowsNumber() const {
  return W;
}

template <class T, size_t W, size_t H>
inline size_t Matrix<T, W, H>::ColumnsNumber() const {
  return H;
}

template <class T, size_t W, size_t H>
inline T& Matrix<T, W, H>::operator()(size_t rows, size_t columns) {
  return mass[rows][columns];
}

template <class T, size_t W, size_t H>
inline const T& Matrix<T, W, H>::operator()(size_t rows, size_t columns) const {
  return mass[rows][columns];
}

template <class T, size_t W, size_t H>
Matrix<T, H, W> GetTransposed(Matrix<T, W, H>& matrix) {
  Matrix<T, H, W> new_matrix;
  for (size_t i = 0; i < H; ++i) {
    for (size_t j = 0; j < W; ++j) {
      new_matrix.mass[i][j] = matrix.mass[j][i];
    }
  }
  return new_matrix;
}

template <class T, size_t R, size_t Y>
const Matrix<T, R, Y> operator+(const Matrix<T, R, Y>& left, const Matrix<T, R, Y>& right) {
  Matrix<T, R, Y> new_matrix;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      new_matrix.mass[i][j] = left.mass[i][j] + right.mass[i][j];
    }
  }
  return new_matrix;
}

template <class T, size_t W, size_t H>
Matrix<T, W, H>& operator+=(Matrix<T, W, H>& left, const Matrix<T, W, H>& right) {
  left = left + right;
  return left;
}

template <class T, size_t W, size_t H>
Matrix<T, W, H> operator-(const Matrix<T, W, H>& left, const Matrix<T, W, H>& right) {
  Matrix<T, W, H> new_matrix;
  for (size_t i = 0; i < W; ++i) {
    for (size_t j = 0; j < H; ++j) {
      new_matrix.mass[i][j] = left.mass[i][j] - right.mass[i][j];
    }
  }
  return new_matrix;
}

template <class T, size_t W, size_t H>
Matrix<T, W, H>& operator-=(Matrix<T, W, H>& left, const Matrix<T, W, H>& right) {
  left = left - right;
  return left;
}

template <class T, size_t W, size_t H>
Matrix<T, W, H> operator*(const Matrix<T, W, H>& matrix, double fact) {
  Matrix<T, W, H> new_matrix;
  for (size_t i = 0; i < W; ++i) {
    for (size_t j = 0; j < H; ++j) {
      new_matrix.mass[i][j] = matrix.mass[i][j] * fact;
    }
  }
  return new_matrix;
}

template <class T, size_t W1, size_t H, size_t W2>
Matrix<T, W1, W2> operator*(const Matrix<T, W1, H>& left, const Matrix<T, H, W2>& right) {
  Matrix<T, W1, W2> new_matrix;
  for (size_t i = 0; i < W1; ++i) {
    for (size_t j = 0; j < W2; ++j) {
      new_matrix.mass[i][j] = 0;
    }
  }
  for (size_t i = 0; i < W1; ++i) {
    for (size_t j = 0; j < W2; ++j) {
      for (size_t k = 0; k < H; ++k) {
        new_matrix.mass[i][j] += left.mass[i][k] * right.mass[k][j];
      }
    }
  }
  return new_matrix;
}

template <class T, size_t W, size_t H>
Matrix<T, W, H>& operator*=(Matrix<T, W, H>& left, Matrix<T, H, H>& right) {
  left = left * right;
  return left;
}

template <class T, class U, size_t W, size_t H>
Matrix<T, W, H> operator*(U fact, const Matrix<T, W, H>& matrix) {
  Matrix<T, W, H> new_matrix = matrix * fact;
  return new_matrix;
}

template <class T, class U, size_t W, size_t H>
Matrix<T, W, H>& operator*=(Matrix<T, W, H>& matrix, U fact) {
  matrix = matrix * fact;
  return matrix;
}

template <class T, class U, size_t W, size_t H>
Matrix<T, W, H>& operator*=(U fact, Matrix<T, W, H>& matrix) {
  matrix = matrix * fact;
  return matrix;
}

template <class T, size_t W, size_t H>
const Matrix<T, W, H> operator/(const Matrix<T, W, H>& matrix, double fact) {
  Matrix<T, W, H> new_matrix;
  for (size_t i = 0; i < W; ++i) {
    for (size_t j = 0; j < H; ++j) {
      new_matrix.mass[i][j] = matrix.mass[i][j] / fact;
    }
  }
  return new_matrix;
}

template <class T, size_t W, size_t H>
Matrix<T, W, H>& operator/=(Matrix<T, W, H>& matrix, double fact) {
  matrix = matrix / fact;
  return matrix;
}

template <class T, class U, size_t W1, size_t H1, size_t W2, size_t H2>
bool operator==(const Matrix<T, W1, H1>& left, const Matrix<U, W2, H2>& right) {
  if (W1 != W2 || H1 != H2) {
    return false;
  }
  for (size_t i = 0; i < W1; ++i) {
    for (size_t j = 0; j < H1; ++j) {
      if (left.mass[i][j] != right.mass[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <class T, class U, size_t W1, size_t H1, size_t W2, size_t H2>
bool operator!=(const Matrix<T, W1, H1>& left, const Matrix<U, W2, H2>& right) {
  return !(left == right);
}
template <class T, size_t W, size_t H>
std::ostream& operator<<(std::ostream& os, const Matrix<T, W, H>& matrix) {
  for (size_t i = 0; i < W; ++i) {
    for (size_t j = 0; j < H; ++j) {
      if (j == H - 1) {
        os << matrix.mass[i][j];
      } else {
        os << matrix.mass[i][j] << ' ';
      }
    }
    os << std::endl;
  }
  return os;
}

template <class T, size_t W, size_t H>
std::istream& operator>>(std::istream& in, Matrix<T, W, H>& matrix) {
  for (size_t i = 0; i < W; ++i) {
    for (size_t j = 0; j < H; ++j) {
      in >> matrix.mass[i][j];
    }
  }
  return in;
}

#endif