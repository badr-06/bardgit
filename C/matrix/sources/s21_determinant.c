#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (A == NULL)
    res = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    res = CALCULATION_ERROR;
  else if (A->rows < 1 || A->columns < 1)
    res = INCORRECT_MATRIX;
  else {
    matrix_t temp = {0};
    s21_create_matrix(A->rows, A->columns, &temp);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        temp.matrix[i][j] = A->matrix[i][j];
      }
    }
    temp.columns = A->columns;
    temp.rows = A->rows;

    double det = 1.0;
    for (int i = 0; i < temp.rows; i++) {
      int max_row = i;
      for (int j = i + 1; j < temp.rows; j++) {
        if (temp.matrix[j][i] > temp.matrix[max_row][i]) max_row = j;
      }

      if (fabs(temp.matrix[max_row][i]) < 1e-10) {
        s21_remove_matrix(&temp);
        *result = 0;
        return 0;
      } else {
        if (max_row != i) {
          double *tmp = temp.matrix[i];
          temp.matrix[i] = temp.matrix[max_row];
          temp.matrix[max_row] = tmp;
          det = -det;
        }

        for (int k = i + 1; k < temp.rows; k++) {
          double factor = temp.matrix[k][i] / temp.matrix[i][i];
          for (int j = 0; j < temp.rows; j++) {
            temp.matrix[k][j] -= factor * temp.matrix[i][j];
          }
        }
        det *= temp.matrix[i][i];
      }
    }

    s21_remove_matrix(&temp);
    *result = det;
  }
  return res;
}
