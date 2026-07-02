#include "cave.h"

Date_Cave *get_date_cave() {
  static Date_Cave cv;
  return &cv;
}

void cave_generation() {
  Date_Cave *cv = get_date_cave();

  init_date_cave();

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      if (generation_bool()) cv->matrix[i][j] = 1;
    }
  }
}

void init_date_cave() {
  Date_Cave *cv = get_date_cave();

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      cv->matrix[i][j] = 0;
    }
  }
}

int checking_neighbors(int x, int y) {
  Date_Cave *cv = get_date_cave();
  int count = 0;

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int xi = x + i;
      int yj = y + j;
      if (x == xi && y == yj) continue;

      if (xi >= 0 && yj >= 0 && xi < cv->rows && yj < cv->columns) {
        if (cv->matrix[xi][yj]) count++;
      } else {
        count++;
      }
    }
  }

  return count;
}

int update_state_cave() {
  Date_Cave *cv = get_date_cave();

  int matrix[cv->rows][cv->columns];
  memset(matrix, 0, sizeof(matrix));

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      int count = checking_neighbors(i, j);
      if (cv->matrix[i][j]) {
        matrix[i][j] = count < cv->death_limit ? 0 : 1;
      } else {
        matrix[i][j] = count > cv->birth_limit ? 1 : 0;
      }
    }
  }

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      cv->matrix[i][j] = matrix[i][j];
    }
  }

  return 0;
}

void load_cave(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "ERROR: Нет такого файла /'%s/'", filename);
    exit(1);
  }

  Date_Cave *cv = get_date_cave();

  init_date_cave();

  if (fscanf(fp, "%d %d", &cv->rows, &cv->columns) != 2) {
    fprintf(stderr, "Не правильный формат данных в файле: %s\n", filename);
    exit(1);
  }

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      if (fscanf(fp, "%d", &cv->matrix[i][j]) != 1) {
        fprintf(stderr, "Не правильный формат данных в файле: %s\n", filename);
        exit(1);
      }
    }
  }

  fclose(fp);
}