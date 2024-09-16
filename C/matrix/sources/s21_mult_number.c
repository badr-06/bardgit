#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL)
    res = INCORRECT_MATRIX;
  else if (A->rows < 1 || A->columns < 1)
    res = INCORRECT_MATRIX;
  else {
    int rows = A->rows;
    int columns = A->columns;
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return res;
}
