#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();  // Destructor

  void print_matrix() const;
  void init(int s);
  void remove_matrix();
  void create_matrix();
  bool check_matrix() const;
  void minor_complement(S21Matrix* minor, int row, int column);
  int GetRows() { return rows_; }
  int GetCols() { return cols_; }
  void SetRowsCols(int i, int j, double x) { matrix_[i][j] = x; }

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix other) const;
  S21Matrix operator-(const S21Matrix other) const;
  S21Matrix operator*(const S21Matrix other) const;
  S21Matrix operator*(const double s);
  bool operator==(const S21Matrix other);
  S21Matrix& operator=(const S21Matrix other);
  S21Matrix& operator+=(const S21Matrix other);
  S21Matrix& operator-=(const S21Matrix other);
  S21Matrix& operator*=(const S21Matrix other);
  S21Matrix& operator*=(const double s);
  double& operator()(const int rows, const int cols);
};

#endif /* MATRIX_H*/