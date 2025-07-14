#include "s21_matrix.hpp"

bool S21Matrix::check_matrix() const {
  bool res = true;

  if (this->matrix_ == nullptr) res = false;

  return res;
}

void S21Matrix::remove_matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::create_matrix() {
  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{0};
  }
}

void S21Matrix::print_matrix() const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << '\n';
  }
  std::cout << "rows = " << rows_ << std::endl
            << "cols = " << cols_ << std::endl;
}

void S21Matrix::init(int s) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = s;
      s++;
    }
  }
}

void S21Matrix::minor_complement(S21Matrix *minor, int row, int column) {
  if (minor == NULL)
    return;
  else {
    for (int i = 0, k = 0; i < rows_; i++) {
      if (i != row) {
        for (int j = 0, z = 0; j < cols_; j++) {
          if (column != j) {
            minor->matrix_[k][z] = matrix_[i][j];
            z++;
          }
          if (z == rows_ - 1) {
            z = 0;
            k++;
          }
        }
      }
    }
    // minor->print_matrix();
  }
}