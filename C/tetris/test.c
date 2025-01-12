#include <check.h>
#include "backend.h"

START_TEST(s21_tetris_test1)
{
    GameInfo_t game = updateCurrentState();

    ck_assert_int_eq(game.score, 0);

    userInput(TERMINATE_BUTTON_SMALL);
    game = updateCurrentState();
}

START_TEST(s21_tetris_test2)
{
    State_t* state = getCurrentState();
    state->is_playing = 0;

    GameInfo_t game = updateCurrentState();

    ck_assert_int_eq(game.level, 1);

    userInput(TERMINATE_BUTTON_SMALL);
    game = updateCurrentState();
}

START_TEST(s21_tetris_test3)
{
    State_t* state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();

    ck_assert_int_eq(game.pause, false);

    userInput(TERMINATE_BUTTON_SMALL);
    game = updateCurrentState();
}

START_TEST(s21_tetris_test4)
{  
    State_t* state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();
    ck_assert_int_eq(game.score, 0);

    userInput(START_BUTTON_SMALL);
    ck_assert_int_eq(state->status, Spawn);

    userInput(TERMINATE_BUTTON_SMALL);
    game = updateCurrentState();

}

START_TEST(s21_tetris_test5)
{  
    State_t *state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();
    ck_assert_int_eq(game.score, 0);

    userInput(START_BUTTON_SMALL);
    ck_assert_int_eq(state->status, Spawn);
    game = updateCurrentState();
    ck_assert_int_eq(state->status, Moving);

    userInput(TERMINATE_BUTTON_SMALL);
    game = updateCurrentState();

}

START_TEST(s21_tetris_test6)
{  
    State_t *state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();
    ck_assert_int_eq(game.score, 0);

    userInput(START_BUTTON_SMALL);
    ck_assert_int_eq(state->game_play, true);

    userInput(TERMINATE_BUTTON_SMALL);
    game = updateCurrentState();
    ck_assert_int_eq(state->game_play, false);

}

START_TEST(s21_tetris_test7)
{  
    State_t *state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();
    ck_assert_int_eq(game.score, 0);

    userInput(START_BUTTON_SMALL);
    game = updateCurrentState();
    ck_assert_int_eq(state->X, 3);

    userInput(KEY_LEFT);
    game = updateCurrentState();
    ck_assert_int_eq(state->X, 2);

    userInput(TERMINATE_BUTTON_SMALL);
    terminateGame();
}

START_TEST(s21_tetris_test8)
{  
    State_t *state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();
    ck_assert_int_eq(game.score, 0);

    userInput(START_BUTTON_SMALL);
    game = updateCurrentState();
    ck_assert_int_eq(state->X, 3);

    userInput(KEY_RIGHT);
    game = updateCurrentState();
    ck_assert_int_eq(state->X, 4);

    userInput(TERMINATE_BUTTON_SMALL);
    terminateGame();
}

START_TEST(s21_tetris_test9)
{  
    State_t *state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();
    ck_assert_int_eq(game.score, 0); 

    userInput(START_BUTTON_SMALL);
    game = updateCurrentState();
    ck_assert_int_eq(state->Y, 0);

    userInput(KEY_DOWN);
    game = updateCurrentState();
    ck_assert_int_eq(state->Y, 1);

    userInput(TERMINATE_BUTTON_SMALL);
    terminateGame();
}


START_TEST(s21_tetris_test10)
{  
    State_t *state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();
    ck_assert_int_eq(game.score, 0);
    userInput(START_BUTTON_SMALL);

    bool result = true;
    int **matrix = createMatrix(FIGURE_H, FIGURE_W);
    game = updateCurrentState();
    copyMatrix(matrix, state->block, FIGURE_H, FIGURE_W);
    

    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            if(matrix[i][j] != state->block[i][j]) result = false;
        }
    }

    ck_assert_int_eq(result, true);

    userInput(ACTION_BUTTON);
    game = updateCurrentState();

    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            if(matrix[i][j] != state->block[i][j]) result = false;
        }
    }

    ck_assert_int_eq(result, false);

    freeMatrix(matrix, FIGURE_H);
    terminateGame();
}

Suite *s21_tetris_suite()
{   
    Suite *s = suite_create("s21_tetris_suite");
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