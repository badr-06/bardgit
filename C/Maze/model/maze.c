#include "maze.h"

Date_Maze* get_date_maze() {
  static Date_Maze dm;
  return &dm;
}

void init_date_maze() {
  Date_Maze* dm = get_date_maze();

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      dm->matrix1[i][j] = 0;
      dm->matrix2[i][j] = 0;
      dm->matrix3[i][j] = 0;
    }
  }
}

int load_maze(char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Нет такого файла\n");
    exit(1);
  }

  init_date_maze();

  Date_Maze* dm = get_date_maze();

  if (fscanf(fp, "%d %d", &dm->rows, &dm->columns) != 2) {
    fprintf(stderr, "Не правильный формат данных в файле: %s\n", filename);
    exit(1);
  }

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      if (fscanf(fp, "%d", &dm->matrix1[i][j]) != 1) {
        fprintf(stderr, "Не правильный формат данных в файле: %s\n", filename);
        exit(1);
      }
    }
  }

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      if (fscanf(fp, "%d", &dm->matrix2[i][j]) != 1) {
        fprintf(stderr, "Не правильный формат данных в файле: %s\n", filename);
        exit(1);
      }
    }
  }

  fclose(fp);

  return 0;
}

void print_date_maze() {
  Date_Maze* dm = get_date_maze();

  printf("%d %d\n", dm->rows, dm->columns);
  putchar('\n');
  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      printf("%d ", dm->matrix1[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      printf("%d ", dm->matrix2[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
  // верхняя рамка
  printf("+");
  for (int j = 0; j < dm->columns; j++) {
    printf("---+");
  }
  putchar('\n');
  for (int i = 0; i < dm->rows; i++) {
    // строка с вертикальными стенами
    printf("|");
    for (int j = 0; j < dm->columns; j++) {
      if (dm->matrix3[i][j]) {
        printf(" # ");
      } else {
        printf("   ");
      }

      if (dm->matrix1[i][j])
        printf("|");
      else
        printf(" ");
    }
    putchar('\n');

    // строка с нижними стенами
    printf("+");
    for (int j = 0; j < dm->columns; j++) {
      if (dm->matrix2[i][j])
        printf("---+");
      else
        printf("   +");
    }
    putchar('\n');
  }
}

void my_write() {
  FILE* fp = fopen("files_maze/out_maze.txt", "w");
  if (fp == NULL) {
    fprintf(stderr, "Нет такого файла out_maze.txt\n");
    exit(1);
  }

  Date_Maze* dm = get_date_maze();

  fprintf(fp, "%d %d\n", dm->rows, dm->columns);

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      fprintf(fp, "%d ", dm->matrix1[i][j]);
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");
  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      fprintf(fp, "%d ", dm->matrix2[i][j]);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
}

void solving_the_maze(int y1, int x1, int y2, int x2) {
  clear_solving_the_maze();

  Date_Maze* dm = get_date_maze();

  bool visit[dm->rows][dm->columns];
  memset(visit, 0, sizeof(visit));

  Point current = {y1, x1};
  Point end = {y2, x2};
  Point path[dm->rows * dm->columns];
  memset(path, -1, sizeof(path));
  int path_count = 0;

  if (dfs(dm->rows, dm->columns, visit, current, end, path, &path_count)) {
    for (int i = 0; i < path_count; i++) {
      dm->matrix3[path[i].y][path[i].x] = 1;
    }
  }
}

int dfs(int rows, int columns, bool visit[rows][columns], Point current,
        Point end, Point* path, int* path_count) {
  if (visit[current.y][current.x] == true) return false;

  Date_Maze* dm = get_date_maze();

  visit[current.y][current.x] = true;
  path[(*path_count)++] = current;

  bool error = false;
  if (current.x == end.x && current.y == end.y) {
    error = true;
  } else if (error == false) {
    int x[] = {1, 0, -1, 0};
    int y[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; ++i) {
      if (current.y + y[i] < 0 || current.y + y[i] >= rows ||
          current.x + x[i] < 0 || current.x + x[i] >= columns)
        continue;

      if (dm->matrix1[current.y][current.x] && x[i] == 1) continue;

      if (dm->matrix2[current.y][current.x] && y[i] == 1) continue;

      if (dm->matrix1[current.y][current.x - 1] && x[i] == -1) continue;

      if (dm->matrix2[current.y - 1][current.x] && y[i] == -1) continue;

      Point next = {current.y + y[i], current.x + x[i]};

      error = dfs(rows, columns, visit, next, end, path, path_count);

      if (error == true) break;
    }
  }

  if (error == false) {
    (*path_count)--;
  }

  return error;
}

void clear_solving_the_maze() {
  Date_Maze* dm = get_date_maze();

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      dm->matrix3[i][j] = 0;
    }
  }
}

// void my_write_set(int n, int matrix[n])
// {
//     FILE *fp = fopen("Test2.txt", "w");
//     if(fp == NULL){
//         fprintf(stderr, "Нет такого файла Test.txt\n");
//         exit(1);
//     }

//     for(int i = 0; i < n; ++i){
//         fprintf(fp, "%d ", matrix[i]);
//     }
//     fprintf(fp, "\n");
//     fclose(fp);
// }

void check_lower_bounds(int i, int r, int c, int matrix[r][c]) {
  Date_Maze* dm = get_date_maze();

  for (int j = 0; j < dm->columns;) {
    bool flag = true, check_low_b = false;
    int num = matrix[i][j], end = 0, start = j;

    while (flag) {
      if ((j >= dm->columns - 1) ||
          ((j < dm->columns - 1) && matrix[i][j + 1] != num)) {
        flag = false;
        end = j;
      }
      if (dm->matrix2[i][j] == 0) {
        check_low_b = true;
      }
      ++j;
    }

    if (!check_low_b) {
      if ((end - start) == 0)
        dm->matrix2[i][end] = 0;
      else {
        int idx = (rand() % (end - start + 1)) + start;
        dm->matrix2[i][idx] = 0;
      }
    }
  }
}

void merge_sets(int* matrix, int a, int b, int columns) {
  int from = matrix[b];
  int to = matrix[a];
  for (int i = 0; i < columns; ++i) {
    if (matrix[i] == from) {
      matrix[i] = to;
    }
  }
}

void maze_generation() {
  Date_Maze* dm = get_date_maze();

  init_date_maze();

  srand(time(NULL));

  int matrix[dm->rows][dm->columns];
  memset(matrix, 0, sizeof(matrix));
  int counter = 1;
  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      if (!matrix[i][j]) matrix[i][j] = counter++;
    }

    for (int j = 0; j < dm->columns; ++j) {
      if (j < (dm->columns - 1) && matrix[i][j] == matrix[i][j + 1]) {
        dm->matrix1[i][j] = 1;
      } else {
        if (generation_bool()) {
          dm->matrix1[i][j] = 1;
        } else if (j < (dm->columns - 1)) {
          merge_sets(matrix[i], j, j + 1, dm->columns);
        }
      }
    }

    for (int j = 0; j < dm->columns; ++j) {
      if ((j == 0 && matrix[i][j] != matrix[i][j + 1]) ||
          (j == dm->columns - 1 && matrix[i][j] != matrix[i][j - 1]) ||
          ((j > 0 && j < dm->columns - 1) &&
           (matrix[i][j - 1] != matrix[i][j] &&
            matrix[i][j] != matrix[i][j + 1]))) {
        dm->matrix2[i][j] = 0;
      } else {
        if (generation_bool()) {
          dm->matrix2[i][j] = 1;
        }
      }
    }

    if (i < (dm->rows - 1)) {
      check_lower_bounds(i, dm->rows, dm->columns, matrix);
      for (int j = 0; j < dm->columns; ++j) {
        if (dm->matrix2[i][j] == 1)
          matrix[i + 1][j] = 0;
        else
          matrix[i + 1][j] = matrix[i][j];
      }
    } else {
      for (int j = 0; j < dm->columns - 1; ++j) {
        if (matrix[i][j] != matrix[i][j + 1]) {
          dm->matrix1[i][j] = 0;
          merge_sets(matrix[i], j, j + 1, dm->columns);
        }
      }
    }
  }
}
