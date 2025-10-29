/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Matrix
*/

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include "Vector.hpp"
#include <concepts>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>

namespace Math {
class MatrixException : public std::exception {
public:
  MatrixException(const std::string message) : msg_(message) {}
  const char *what() const noexcept override { return msg_.c_str(); }

private:
  const std::string msg_;
};

class MatrixDimensionException : public MatrixException {
public:
  MatrixDimensionException() : MatrixException("Matrix dimension mismatch") {}
};

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number T> class Matrix {
public:
  Matrix(size_t rows, size_t cols, T value = 0);
  ~Matrix();
  size_t rows;
  size_t cols;
  std::vector<std::vector<T>> data_;

  Matrix<T> operator+(const Matrix<T> &other) const;
  Matrix<T> operator-(const Matrix<T> &other) const;
  Matrix<T> operator*(const Matrix<T> &other) const;
  Matrix<T> operator*(T scalar) const;

  Matrix<T> identity(void) const;
  Matrix<T> translate(const Math::Vector3D &vec) const;
  Matrix<T> scale(const Math::Vector3D &vec) const;
  Matrix<T> rotate(const Math::Vector3D &axes) const;
  Matrix<T> lookAt(const Math::Vector3D &eye, const Math::Vector3D &center,
                   const Math::Vector3D &up) const;
  Matrix<T> viewPortMatrix(int x, int y, int width, int height) const;
};

template <Number T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
  if (this->cols != other.rows) {
    throw MatrixDimensionException();
  }
  Matrix<T> result(this->rows, other.cols, 0);
  for (size_t i = 0; i < this->rows; ++i) {
    for (size_t j = 0; j < other.cols; ++j) {
      for (size_t k = 0; k < this->cols; ++k) {
        result.data_[i][j] += this->data_[i][k] * other.data_[k][j];
      }
    }
  }
  return result;
}

template <Number T> Matrix<T> Matrix<T>::operator*(T scalar) const {
  Matrix<T> result(this->rows, this->cols, 0);
  for (size_t i = 0; i < this->rows; ++i) {
    for (size_t j = 0; j < this->cols; ++j) {
      result.data_[i][j] = this->data_[i][j] * scalar;
    }
  }
  return result;
}

template <Number T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const {
  if (this->rows != other.rows || this->cols != other.cols) {
    throw MatrixDimensionException();
  }
  Matrix<T> result(this->rows, this->cols, 0);
  for (size_t i = 0; i < this->rows; ++i) {
    for (size_t j = 0; j < this->cols; ++j) {
      result.data_[i][j] = this->data_[i][j] - other.data_[i][j];
    }
  }
  return result;
}

template <Number T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const {
  if (this->rows != other.rows || this->cols != other.cols) {
    throw MatrixDimensionException();
  }
  Matrix<T> result(this->rows, this->cols, 0);
  for (size_t i = 0; i < this->rows; ++i) {
    for (size_t j = 0; j < this->cols; ++j) {
      result.data_[i][j] = this->data_[i][j] + other.data_[i][j];
    }
  }
  return result;
}

template <Number T>
Matrix<T>::Matrix(size_t rows, size_t cols, T value) : rows(rows), cols(cols) {
  this->data_.resize(rows);
  for (size_t i = 0; i < rows; ++i) {
    this->data_[i].resize(cols);
    for (size_t j = 0; j < cols; ++j) {
      this->data_[i][j] = value;
    }
  }
}

template <Number T> Matrix<T> Matrix<T>::identity(void) const {
  if (this->rows != this->cols) {
    throw MatrixDimensionException();
  }
  Matrix<T> result(this->rows, this->cols, 0);
  for (size_t i = 0; i < this->rows; ++i) {
    for (size_t j = 0; j < this->cols; ++j) {
      result.data_[i][j] = (i == j);
    }
  }
  return result;
}

template <Number T>
Matrix<T> Matrix<T>::translate(const Math::Vector3D &vec) const {
  if (this->rows != 4 || this->cols != 4) {
    throw MatrixDimensionException();
  }
  Matrix<T> result(4, 4);
  result = result.identity();
  result.data_[0][3] = -vec.x;
  result.data_[1][3] = -vec.y;
  result.data_[2][3] = -vec.z;
  return result;
}

template <Number T>
Matrix<T> Matrix<T>::scale(const Math::Vector3D &vec) const {
  if (this->rows != 4 || this->cols != 4) {
    throw MatrixDimensionException();
  }
  Matrix<T> result(4, 4);

  result = result.identity();
  result.data_[0][0] = vec.x;
  result.data_[1][1] = vec.y;
  result.data_[2][2] = vec.z;
  return result;
}

template <Number T>
Matrix<T> Matrix<T>::rotate(const Math::Vector3D &axes) const {
  float sinAlpha = std::sin(axes.x);
  float cosAlpha = std::cos(axes.x);

  float sinBeta = std::sin(axes.y);
  float cosBeta = std::cos(axes.y);

  float sinGamma = std::sin(axes.z);
  float cosGamma = std::cos(axes.z);

  Matrix<T> r = this->identity();

  r.data_[0][0] = cosAlpha * cosBeta;
  r.data_[0][1] = cosAlpha * sinBeta * sinGamma - sinAlpha * cosGamma;
  r.data_[0][2] = cosAlpha * sinBeta * cosGamma + sinAlpha * sinGamma;

  r.data_[1][0] = sinAlpha * cosBeta;
  r.data_[1][1] = sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma;
  r.data_[1][2] = sinAlpha * sinBeta * cosGamma - cosAlpha * sinGamma;

  r.data_[2][0] = -sinBeta;
  r.data_[2][1] = cosBeta * sinGamma;
  r.data_[2][2] = cosBeta * cosGamma;

  return r;
}

template <Number T>
Matrix<T> Matrix<T>::lookAt(const Math::Vector3D &eye,
                            const Math::Vector3D &center,
                            const Math::Vector3D &up) const {
  Vector3D n = (center - eye).normalized();
  Vector3D u = n.cross(up).normalized();
  Vector3D v = u.cross(n).normalized();

  Matrix<T> c(4, 4), t(4, 4);
  c = c.identity();
  t = t.identity();

  for (size_t i = 0; i < 3; ++i) {
    c.data_[0][i] = u.getAxis(i);
    c.data_[1][i] = v.getAxis(i);
    c.data_[2][i] = -n.getAxis(i);
    t.data_[i][3] = -eye.getAxis(i);
  }
  return c * t;
}

template<Number T>
Matrix<T> Matrix<T>::viewPortMatrix(int x, int y, int width, int height) const {
  Matrix<T> vp(4, 4);
  vp = vp.identity();
  vp.data_[0][3] = x + width / 2.0;
  vp.data_[1][3] = y + height / 2.0;
  vp.data_[2][3] = 1;
  vp.data_[0][0] = width / 2.0;
  vp.data_[1][1] = height / 2.0;
  vp.data_[2][2] = 0;
  return vp;
}

template <Number T> Matrix<T>::~Matrix() = default;

template <Number T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
  for (size_t i = 0; i < matrix.rows; ++i) {
    for (size_t j = 0; j < matrix.cols; ++j) {
      os << matrix.data_[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}

} // namespace Math

#endif /* !MATRIX_HPP_ */