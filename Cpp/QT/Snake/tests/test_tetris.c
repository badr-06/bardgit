#include <check.h>

#include "../brick_game/tetris/beckend_tetris.h"

START_TEST(s21_tetris_test1) {
  GameInfo_t game = updateCurrentState();

  ck_assert_int_eq(game.score, 0);

  userInput(Terminate);
  game = updateCurrentState();
}

START_TEST(s21_tetris_test2) {
  State_t *state = getCurrentState();
  state->is_playing = 0;

  GameInfo_t game = updateCurrentState();

  ck_assert_int_eq(game.level, 1);

  userInput(Terminate);
  game = updateCurrentState();
}

START_TEST(s21_tetris_test3) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();

  ck_assert_int_eq(game.pause, false);

  userInput(Terminate);
  game = updateCurrentState();
}

START_TEST(s21_tetris_test4) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);
  ck_assert_int_eq(state->status_game, Spawn);

  userInput(Terminate);
  game = updateCurrentState();
}

START_TEST(s21_tetris_test5) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);
  ck_assert_int_eq(state->status_game, Spawn);
  game = updateCurrentState();
  ck_assert_int_eq(state->status_game, Moving);

  userInput(Terminate);
  game = updateCurrentState();
}

START_TEST(s21_tetris_test6) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);
  ck_assert_int_eq(state->game_play, true);

  userInput(Terminate);
  game = updateCurrentState();
  ck_assert_int_eq(state->game_play, false);
}

START_TEST(s21_tetris_test7) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);
  game = updateCurrentState();
  ck_assert_int_eq(state->X, 3);

  userInput(Left);
  game = updateCurrentState();
  ck_assert_int_eq(state->X, 2);

  userInput(Terminate);
  terminateGame();
}

START_TEST(s21_tetris_test8) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);
  game = updateCurrentState();
  ck_assert_int_eq(state->X, 3);

  userInput(Right);
  game = updateCurrentState();
  ck_assert_int_eq(state->X, 4);

  userInput(Terminate);
  terminateGame();
}

START_TEST(s21_tetris_test9) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);
  game = updateCurrentState();
  ck_assert_int_eq(state->Y, 0);

  userInput(Down);
  game = updateCurrentState();
  ck_assert_int_eq(state->Y, 1);

  userInput(Terminate);
  terminateGame();
}

START_TEST(s21_tetris_test10) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);
  userInput(Start);

  bool result = true;
  int **matrix = createMatrix(FIGURE_H, FIGURE_W);
  game = updateCurrentState();
  copyMatrix(matrix, state->block, FIGURE_H, FIGURE_W);

  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      if (matrix[i][j] != state->block[i][j])
        result = false;
    }
  }

  ck_assert_int_eq(result, true);

  userInput(Action);
  game = updateCurrentState();

  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      if (matrix[i][j] != state->block[i][j])
        result = false;
    }
  }

  ck_assert_int_eq(result, false);

  freeMatrix(matrix, FIGURE_H);
  terminateGame();
}

START_TEST(s21_tetris_test11) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);

  while (state->status_game != Attaching) {
    game = updateCurrentState();
  }

  ck_assert_int_eq(state->status_game, Attaching);

  game = updateCurrentState();

  ck_assert_int_eq(state->status_game, Spawn);

  userInput(Terminate);
  terminateGame();
}

START_TEST(s21_tetris_test12) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);

  while (state->status_game != GAMEOVER) {
    game = updateCurrentState();
  }

  ck_assert_int_eq(state->status_game, GAMEOVER);

  terminateGame();
}

START_TEST(s21_tetris_test13) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);

  while (state->status_game != GAMEOVER) {
    game = updateCurrentState();
    userInput(Action);
  }

  ck_assert_int_eq(state->status_game, GAMEOVER);

  terminateGame();
}

START_TEST(s21_tetris_test14) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);

  while (state->status_game != GAMEOVER) {
    game = updateCurrentState();
    userInput(Right);
  }

  ck_assert_int_eq(state->status_game, GAMEOVER);

  terminateGame();
}

START_TEST(s21_tetris_test15) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);

  while (state->status_game != GAMEOVER) {
    game = updateCurrentState();
    userInput(Left);
  }

  ck_assert_int_eq(state->status_game, GAMEOVER);

  terminateGame();
}

START_TEST(s21_tetris_test16) {
  State_t *state = getCurrentState();
  state->is_playing = 0;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.score, 0);

  userInput(Start);

  while (state->status_game != GAMEOVER) {
    game = updateCurrentState();
    userInput(Up);
  }

  ck_assert_int_eq(state->status_game, GAMEOVER);

  userInput(Terminate);
  game = updateCurrentState();
}

Suite *s21_tetris_suite() {
  Suite *s = suite_create("s21_tetris_tests");
  TCase *tc = tcase_create("s21_tetris_tcase");

  tcase_add_test(tc, s21_tetris_test1);
  tcase_add_test(tc, s21_tetris_test2);
  tcase_add_test(tc, s21_tetris_test3);
  tcase_add_test(tc, s21_tetris_test4);
  tcase_add_test(tc, s21_tetris_test5);
  tcase_add_test(tc, s21_tetris_test6);
  tcase_add_test(tc, s21_tetris_test7);
  tcase_add_test(tc, s21_tetris_test8);
  tcase_add_test(tc, s21_tetris_test9);
  tcase_add_test(tc, s21_tetris_test10);
  tcase_add_test(tc, s21_tetris_test11);
  tcase_add_test(tc, s21_tetris_test12);
  tcase_add_test(tc, s21_tetris_test13);
  tcase_add_test(tc, s21_tetris_test14);
  tcase_add_test(tc, s21_tetris_test15);
  tcase_add_test(tc, s21_tetris_test16);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  Suite *s;
  SRunner *sr;

  s = s21_tetris_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int failed_count = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}