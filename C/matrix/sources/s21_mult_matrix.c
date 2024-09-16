#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A == NULL || B == NULL || result == NULL)
    res = INCORRECT_MATRIX;
  else if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1)
    res = INCORRECT_MATRIX;
  else if (A->columns != B->rows)
    res = CALCULATION_ERROR;
  else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < B->columns; k++) {
        result->matrix[i][k] = 0;
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][k] += A->matrix[i][j] * B->matrix[j][k];
        }
      }
    }
  }
  return res;
}
