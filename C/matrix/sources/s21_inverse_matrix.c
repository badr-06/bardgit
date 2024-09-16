#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL) {
    res = INCORRECT_MATRIX;
  }

  else if (A->rows != A->columns) {
    res = CALCULATION_ERROR;
  }

  else if (A->rows < 1) {
    res = INCORRECT_MATRIX;
  }

  else {
    if (A->rows == 1 && A->columns == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = pow(A->matrix[0][0], -1);
    }

    else {
      double detrminant = 0;
      if ((res = s21_determinant(A, &detrminant)) == OK) {
        if (fabs(detrminant) < 1e-10)
          res = CALCULATION_ERROR;
        else {
          matrix_t B = {0};
          res = s21_calc_complements(A, &B);
          if (res == OK) {
            matrix_t C = {0};

            if ((res = s21_transpose(&B, &C)) != OK) {
              s21_remove_matrix(&C);
            } else {
              detrminant = 1 / detrminant;
              s21_mult_number(&C, detrminant, result);

              s21_remove_matrix(&B);
              s21_remove_matrix(&C);
            }
          }
          if (res != OK) s21_remove_matrix(&B);
        }
      }
    }
  }
  return res;
}

int main()
{
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  // A.matrix[0][0] = 7;
  // A.matrix[0][1] = 3;
  // A.matrix[0][2] = 1;
  // A.matrix[1][0] = 7;
  // A.matrix[1][1] = 6;
  // A.matrix[1][2] = 4;
  // A.matrix[2][0] = 12;
  // A.matrix[2][1] = 3;
  // A.matrix[2][2] = 6;

  A.matrix[0][0] = 7;
  // A.matrix[0][1] = 3;
  // A.matrix[1][0] = 7;
  // A.matrix[1][1] = 6;

  s21_inverse_matrix(&A, &result);

  print_matrix(result);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}