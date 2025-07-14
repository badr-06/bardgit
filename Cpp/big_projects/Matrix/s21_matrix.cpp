#include "s21_matrix.hpp"

S21Matrix::S21Matrix() : rows_(3), cols_(3) { create_matrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("incorrect size");
  }

  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  create_matrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  remove_matrix();
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
          res = false;
          break;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("different matrix dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("different matrix dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }

  S21Matrix date(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < other.cols_; k++) {
      for (int j = 0; j < cols_; j++) {
        date.matrix_[i][k] += matrix_[i][j] * other.matrix_[j][k];
      }
    }
  }
  rows_ = date.rows_;
  cols_ = date.cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = date.matrix_[i][j];
    }
  }
  // date.remove_matrix();
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }

  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square");
  }
  double result = 0;
  S21Matrix temp(*this);

  double det = 1.0;
  for (int i = 0; i < temp.rows_; i++) {
    int max_row = i;
    for (int j = i + 1; j < temp.rows_; j++) {
      if (temp.matrix_[j][i] > temp.matrix_[max_row][i]) max_row = j;
    }

    if (fabs(temp.matrix_[max_row][i]) < 1e-10) {
      return 0;
    } else {
      if (max_row != i) {
        double* tmp = temp.matrix_[i];
        temp.matrix_[i] = temp.matrix_[max_row];
        temp.matrix_[max_row] = tmp;
        det = -det;
      }

      for (int k = i + 1; k < temp.rows_; k++) {
        double factor = temp.matrix_[k][i] / temp.matrix_[i][i];
        for (int j = 0; j < temp.rows_; j++) {
          temp.matrix_[k][j] -= factor * temp.matrix_[i][j];
        }
      }
      det *= temp.matrix_[i][i];
    }
  }

  result = det;

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        minor_complement(&minor, i, j);
        double determinant;
        determinant = minor.Determinant();
        result.matrix_[i][j] = pow(-1, i + j) * determinant;
      }
    }
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = result.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix C;
  if (rows_ == 1 && cols_ == 1) {
    S21Matrix result(1, 1);
    result.matrix_[0][0] = pow(matrix_[0][0], -1);
    return result;
  }

  else {
    double detrminant = Determinant();
    if (fabs(detrminant) < 1e-10) {
      throw std::invalid_argument("Matrix determinant is 0");
    } else {
      S21Matrix B = CalcComplements();
      C = B.Transpose();

      detrminant = 1 / detrminant;
      C.MulNumber(detrminant);
    }
  }

  return C;
}

S21Matrix& S21Matrix::operator=(const S21Matrix other) {
  this->remove_matrix();

  rows_ = other.rows_;
  cols_ = other.cols_;
  this->create_matrix();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix other) const {
  S21Matrix res(*this);
  // res.print_matrix();
  // other.print_matrix();
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix other) const {
  S21Matrix res(*this);
  // res.print_matrix();
  // other.print_matrix();
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix other) const {
  S21Matrix res(*this);
  // res.print_matrix();
  // other.print_matrix();
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double s) {
  S21Matrix res(*this);
  res.MulNumber(s);
  return res;
}

bool S21Matrix::operator==(const S21Matrix other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator+=(const S21Matrix other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double s) {
  MulNumber(s);
  return *this;
}

double& S21Matrix::operator()(const int rows, const int cols) {
  if (rows > rows_ || cols > cols_) {
    std::length_error("Index is outside the matrix");
  }
  return matrix_[rows][cols];
}

// int main() {

//     S21Matrix tp(2, 2);
//     S21Matrix pt(3, 3);
//     pt.init(1);

//     if(tp == pt) std::cout << "Yes" << '\n';
//     else std::cout << "No" << '\n';

//     return 0;
// }