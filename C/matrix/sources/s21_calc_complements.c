#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;

  if (A == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALCULATION_ERROR;
  }

  else if (A->rows < 1) {
    res = INCORRECT_MATRIX;
  }

  else {
    s21_create_matrix(A->rows, A->columns, result);

    if (A->rows == 1 && A->columns == 1) {
      result->matrix[0][0] = 1;
    } else {
      matrix_t minor;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          minor_complement(A, &minor, i, j);
          double determinant;
          if ((res = s21_determinant(&minor, &determinant)) == OK) {
            result->matrix[i][j] = pow(-1, i + j) * determinant;
          }
        }
      }
      s21_remove_matrix(&minor);
    }
  }

  return res;
}