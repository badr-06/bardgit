#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (result == NULL)
    res = INCORRECT_MATRIX;
  else if (rows == 0 || columns == 0)
    res = INCORRECT_MATRIX;
  else {
    result->matrix = (double **)malloc(rows * sizeof(double *));

    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double *));
      }
      if (res == OK) {
        result->rows = rows;
        result->columns = columns;

        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = 0.0;
          }
        }
      }
    }
  }
  return res;
}

// int s21_create_matrix(int rows, int columns, matrix_t *result) {
//     // Проверка входных параметров
//     if (result == NULL || rows <= 0 || columns <= 0) {
//         return INCORRECT_MATRIX; // Возвращаем ошибку, если параметры
//         некорректны
//     }

//     // Выделение памяти для массива указателей на строки
//     result->matrix = (double **)malloc(rows * sizeof(double *));
//     if (result->matrix == NULL) {
//         return INCORRECT_MATRIX; // Проверка на успешное выделение памяти
//     }

//     // Выделение памяти для каждой строки
//     for (int i = 0; i < rows; i++) {
//         result->matrix[i] = (double *)malloc(columns * sizeof(double));
//         if (result->matrix[i] == NULL) {
//             // Если выделение памяти не удалось, освобождаем уже выделенные
//             строки for (int j = 0; j < i; j++) {
//                 free(result->matrix[j]);
//             }
//             free(result->matrix);
//             return INCORRECT_MATRIX; // Возвращаем ошибку
//         }
//     }

//     // Установка размеров матрицы
//     result->rows = rows;
//     result->columns = columns;

//     // Инициализация матрицы нулями (по желанию)
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < columns; j++) {
//             result->matrix[i][j] = 0.0; // Инициализируем элементы нулями
//         }
//     }

//     return OK; // Возвращаем статус успешного выполнения
// }