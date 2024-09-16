#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL)
    return INCORRECT_MATRIX;
  else if (A->rows < 1 || A->columns < 1)
    return INCORRECT_MATRIX;
  else {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return OK;
}

// int main()
// {
//   matrix_t A = {0}, result = {0}, check = {0};
//   s21_create_matrix(3, 3, &A);
//   s21_create_matrix(3, 3, &check);
//   for (int i = 0; i < A.rows; i++) {
//     for (int j = 0; j < A.columns; j++) {
//       A.matrix[i][j] = 1;
//       check.matrix[i][j] = 1;
//     }
//   }
//   s21_transpose(&A, &result);

//   print_matrix(result);
//   print_matrix(check);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&result);
//   s21_remove_matrix(&check);
// }