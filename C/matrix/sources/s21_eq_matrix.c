#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;

  if (A == NULL || B == NULL) {
    res = FAILURE;
  }

  else if (A->rows != B->rows || A->columns != B->columns) {
    res = FAILURE;
  }

  else if (A->rows < 1) {
    res = FAILURE;
  }

  else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (A->matrix[i][j] != B->matrix[i][j]) {
          res = FAILURE;
          break;
        }
      }
    }
  }
  return res;
}

int main()
{
    matrix_t A, B;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);

    A.matrix[0][0] = 1.123456;
    A.matrix[0][1] = 2.123456;
    A.matrix[1][0] = 3.123456;
    A.matrix[1][1] = 4.123456;

    B.matrix[0][0] = 1.123457; // Изменение на 0.000001
    B.matrix[0][1] = 2.123456;
    B.matrix[1][0] = 3.123456;
    B.matrix[1][1] = 4.123456;

    int result = s21_eq_matrix(&A, &B);
  print_matrix(A);
  print_matrix(B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  printf("%d\n", result);

}