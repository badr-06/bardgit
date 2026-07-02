#include <check.h>

#include "../controller/controller.h"
#include "../model/model.h"

START_TEST(test_init_date_maze) {
  Date_Maze *dm = get_date_maze();

  dm->rows = 10;
  dm->columns = 10;

  init_date_maze();

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix1[i][j], 0);
      ck_assert_int_eq(dm->matrix2[i][j], 0);
      ck_assert_int_eq(dm->matrix3[i][j], 0);
    }
  }
}
END_TEST

START_TEST(test_load_maze) {
  Date_Maze *dm = get_date_maze();

  load_maze("files_maze/date_maze_1.txt");

  int check_matrix1[4][4] = {
      {0, 0, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {0, 0, 0, 1}};
  int check_matrix2[4][4] = {
      {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 1, 0, 1}, {1, 1, 1, 1}};
  ck_assert_int_eq(dm->rows, 4);
  ck_assert_int_eq(dm->columns, 4);

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix1[i][j], check_matrix1[i][j]);
      ck_assert_int_eq(dm->matrix2[i][j], check_matrix2[i][j]);
    }
  }
}
END_TEST

START_TEST(test_maze_generation) {
  Date_Maze *dm = get_date_maze();

  dm->rows = 10;
  dm->columns = 10;

  init_date_maze();

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix1[i][j], 0);
      ck_assert_int_eq(dm->matrix2[i][j], 0);
      ck_assert_int_eq(dm->matrix3[i][j], 0);
    }
  }

  maze_generation();

  int Quantity_1_matrix1 = 0,
      Quantity_1_matrix2 = 0;  // проверяем что теперь не все нули в матрицах

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      if (dm->matrix1[i][j]) Quantity_1_matrix1++;
      if (dm->matrix2[i][j]) Quantity_1_matrix2++;
    }
  }

  ck_assert_int_gt(Quantity_1_matrix1, 0);
  ck_assert_int_gt(Quantity_1_matrix2, 0);
}
END_TEST

START_TEST(test_my_write) {
  Date_Maze *dm = get_date_maze();

  dm->rows = 10;
  dm->columns = 10;

  init_date_maze();

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix1[i][j], 0);
      ck_assert_int_eq(dm->matrix2[i][j], 0);
      ck_assert_int_eq(dm->matrix3[i][j], 0);
    }
  }

  maze_generation();

  my_write();

  int rows = dm->rows;
  int columns = dm->columns;
  int matrix1[rows][columns], matrix2[rows][columns];

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix1[i][j] = dm->matrix1[i][j];
      matrix2[i][j] = dm->matrix2[i][j];
    }
  }

  init_date_maze();

  load_maze("files_maze/out_maze.txt");

  ck_assert_int_eq(rows, dm->rows);
  ck_assert_int_eq(columns, dm->columns);

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix1[i][j], matrix1[i][j]);
      ck_assert_int_eq(dm->matrix2[i][j], matrix2[i][j]);
    }
  }
}
END_TEST

START_TEST(test_solving_the_maze) {
  Date_Maze *dm = get_date_maze();

  load_maze("files_maze/date_maze_1.txt");

  solving_the_maze(0, 0, 3, 3);

  int matrix3_1[4][4] = {
      {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}, {0, 0, 1, 1}};

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix3[i][j], matrix3_1[i][j]);
    }
  }

  solving_the_maze(0, 0, 1, 0);

  int matrix3_2[4][4] = {
      {1, 1, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix3[i][j], matrix3_2[i][j]);
    }
  }
}
END_TEST

START_TEST(test_clear_solving_the_maze) {
  Date_Maze *dm = get_date_maze();

  load_maze("files_maze/date_maze_1.txt");

  solving_the_maze(0, 0, 3, 3);

  int matrix3[4][4] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}, {0, 0, 1, 1}};

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix3[i][j], matrix3[i][j]);
    }
  }

  clear_solving_the_maze();

  for (int i = 0; i < dm->rows; ++i) {
    for (int j = 0; j < dm->columns; ++j) {
      ck_assert_int_eq(dm->matrix3[i][j], 0);
    }
  }
}
END_TEST


// =============================================

START_TEST(test_init_date_cave) {
  Date_Cave *cv = get_date_cave();

  cv->rows = 10;
  cv->columns = 10;

  init_date_cave();

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      ck_assert_int_eq(cv->matrix[i][j], 0);
    }
  }
}
END_TEST

START_TEST(test_load_cave) {
  Date_Cave *cv = get_date_cave();

  load_cave("files_cave/date_cave_1.txt");

  int matrix[5][5] = {{0, 1, 1, 1, 0},
                      {0, 1, 0, 1, 0},
                      {0, 1, 1, 1, 0},
                      {0, 1, 0, 0, 0},
                      {0, 1, 0, 0, 0}};

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      ck_assert_int_eq(cv->matrix[i][j], matrix[i][j]);
    }
  }
}
END_TEST

START_TEST(test_update_cave) {
  Date_Cave *cv = get_date_cave();

  load_cave("files_cave/date_cave_1.txt");

  int matrix1[5][5] = {{0, 1, 1, 1, 0},
                       {0, 1, 0, 1, 0},
                       {0, 1, 1, 1, 0},
                       {0, 1, 0, 0, 0},
                       {0, 1, 0, 0, 0}};

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      ck_assert_int_eq(cv->matrix[i][j], matrix1[i][j]);
    }
  }

  cv->birth_limit = 4;
  cv->death_limit = 4;

  update_state_cave();

  int matrix2[5][5] = {{1, 1, 1, 1, 1},
                       {1, 1, 1, 1, 1},
                       {1, 0, 1, 0, 1},
                       {1, 0, 1, 0, 0},
                       {1, 1, 1, 0, 1}};

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      ck_assert_int_eq(cv->matrix[i][j], matrix2[i][j]);
    }
  }
}
END_TEST

START_TEST(test_cave_generation) {
  Date_Cave *cv = get_date_cave();

  cv->rows = 10;
  cv->columns = 10;

  init_date_cave();

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      ck_assert_int_eq(cv->matrix[i][j], 0);
    }
  }

  cave_generation();

  int Quantity_1 = 0;  // проверяем что теперь не все нули в матрицах

  for (int i = 0; i < cv->rows; ++i) {
    for (int j = 0; j < cv->columns; ++j) {
      if (cv->matrix[i][j]) Quantity_1++;
    }
  }

  ck_assert_int_gt(Quantity_1, 0);
}
END_TEST

Suite *s21_maze_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_maze_suite");
  tc = tcase_create("s21_maze_case");

  tcase_add_test(tc, test_init_date_maze);
  tcase_add_test(tc, test_load_maze);
  tcase_add_test(tc, test_maze_generation);
  tcase_add_test(tc, test_my_write);
  tcase_add_test(tc, test_solving_the_maze);
  tcase_add_test(tc, test_clear_solving_the_maze);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_cave_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_cave_suite");
  tc = tcase_create("s21_cave_case");

  tcase_add_test(tc, test_init_date_cave);
  tcase_add_test(tc, test_load_cave);
  tcase_add_test(tc, test_cave_generation);
  tcase_add_test(tc, test_update_cave);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  int failed_count = 0;

  Suite *s;
  SRunner *sr;

  s = s21_maze_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed_count = srunner_ntests_failed(sr);
  srunner_free(sr);
  sr = NULL;

  s = s21_cave_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  failed_count += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}