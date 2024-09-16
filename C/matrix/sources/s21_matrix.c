#include "../s21_matrix.h"

void print_matrix(matrix_t A){
  for(int i = 0; i < A.rows; i++){
    for(int j = 0; j < A.columns; j++){
      printf("%lf ", A.matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void init(matrix_t *A, double k, double c) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = k;
      k += c;
    }
  }
}

void minor_complement(matrix_t *A, matrix_t *minor, int row, int column) {
  if (A == NULL || minor == NULL)
    return;
  else {
    for (int i = 0, k = 0; i < A->rows; i++) {
      if (i != row) {
        for (int j = 0, z = 0; j < A->columns; j++) {
          if (column != j) {
            minor->matrix[k][z] = A->matrix[i][j];
            z++;
          }
          if (z == A->rows - 1) {
            z = 0;
            k++;
          }
        }
      }
    }
  }
}
