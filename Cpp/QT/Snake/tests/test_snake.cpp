#include "../brick_game/snake/controller.h"
#include <chrono>
#include <gtest/gtest.h>
#include <thread>

TEST(snake, initialition_function) {
  updateCurrentState();
  State_t *state = getCurrentState();

  ASSERT_TRUE(state->is_playing);
  ASSERT_TRUE(state->status_game == INITIAL);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, remove_snake_filed) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();

  // начальные координаты змеи {10, 4}, {10, 5}, {10, 6}, {10, 7}
  ASSERT_EQ(game->field[10][4], 3); // голова поэтому 3
  ASSERT_EQ(game->field[10][5], 1);
  ASSERT_EQ(game->field[10][6], 1);
  ASSERT_EQ(game->field[10][7], 1);

  s21::Snake::remove_snake_from_filed();

  ASSERT_EQ(game->field[10][4], 0);
  ASSERT_EQ(game->field[10][5], 0);
  ASSERT_EQ(game->field[10][6], 0);
  ASSERT_EQ(game->field[10][7], 0);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, create_field) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();

  ASSERT_NE(game->field, nullptr);

  userInput(Terminate);
  updateCurrentState();

  ASSERT_EQ(game->field, nullptr);
}

TEST(snake, clear_field) {
  GameInfo_t *game = getCurrentGame();

  ASSERT_EQ(game->field, nullptr);

  updateCurrentState();

  ASSERT_NE(game->field, nullptr);

  s21::Snake::clear_field();

  ASSERT_EQ(game->field, nullptr);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, create_snake) {
  updateCurrentState();

  auto snake = s21::Snake::getSnake();
  snake->clear();

  ASSERT_EQ(snake->size(), 0);

  s21::Snake::create_snake();

  ASSERT_EQ(snake->size(), 4); // начальный размер змейки 4

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, moving_snake) {
  updateCurrentState();
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  state->direction = goes_left; // напрвление

  // начальные координаты змеи {10, 4}, {10, 5}, {10, 6}, {10, 7}
  EXPECT_EQ(game->field[10][4], 3); // голова поэтому 3
  EXPECT_EQ(game->field[10][5], 1);
  EXPECT_EQ(game->field[10][6], 1);
  EXPECT_EQ(game->field[10][7], 1);

  state->milliseconds = s21::Snake::current_time();
  game->speed = 1000;
  state->action = true;

  std::this_thread::sleep_for(std::chrono::milliseconds(600));

  s21::Snake::moving_snake();

  EXPECT_EQ(game->field[10][3], 3);
  EXPECT_EQ(game->field[10][4], 1);
  EXPECT_EQ(game->field[10][5], 1);
  EXPECT_EQ(game->field[10][6], 1);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, snake_on_field) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();

  s21::Snake::remove_snake_from_filed();

  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      EXPECT_EQ(game->field[i][j], 0);
    }
  }

  s21::Snake::snake_on_field();

  EXPECT_EQ(game->field[10][4], 3); // голова поэтому 3
  EXPECT_EQ(game->field[10][5], 1);
  EXPECT_EQ(game->field[10][6], 1);
  EXPECT_EQ(game->field[10][7], 1);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, terminateGame) {
  updateCurrentState();
  State_t *state = getCurrentState();

  ASSERT_EQ(state->game_play, true);
  ASSERT_EQ(state->is_playing, true);

  userInput(Terminate);
  s21::Snake::terminateGame();

  ASSERT_EQ(state->game_play, false);
  ASSERT_EQ(state->is_playing, false);
}

TEST(snake, shifting_snake) {
  updateCurrentState();
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  state->direction = goes_left; // напрвление

  // начальные координаты змеи {10, 4}, {10, 5}, {10, 6}, {10, 7}
  EXPECT_EQ(game->field[10][4], 3); // голова поэтому 3
  EXPECT_EQ(game->field[10][5], 1);
  EXPECT_EQ(game->field[10][6], 1);
  EXPECT_EQ(game->field[10][7], 1);

  s21::Snake::shifting_snake();

  EXPECT_EQ(game->field[10][3], 3);
  EXPECT_EQ(game->field[10][4], 1);
  EXPECT_EQ(game->field[10][5], 1);
  EXPECT_EQ(game->field[10][6], 1);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, restart_game) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();

  s21::Snake::terminateGame();

  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      EXPECT_EQ(game->field[i][j], 0);
    }
  }

  s21::Snake::restart_game();

  // начальные координаты змеи {10, 4}, {10, 5}, {10, 6}, {10, 7}
  EXPECT_EQ(game->field[10][4], 3); // голова поэтому 3
  EXPECT_EQ(game->field[10][5], 1);
  EXPECT_EQ(game->field[10][6], 1);
  EXPECT_EQ(game->field[10][7], 1);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, clean_field) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();
  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      game->field[i][j] = 1;
    }
  }

  s21::Snake::clean_field();

  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      EXPECT_EQ(game->field[i][j], 0);
    }
  }

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, create_ball) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();

  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      EXPECT_NE(game->field[i][j], 2);
    }
  }

  s21::Snake::create_ball();

  State_t *state = getCurrentState();

  EXPECT_EQ(game->field[state->ball->y][state->ball->x], 2);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, start_game) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();
  State_t *state = getCurrentState();

  s21::Snake::terminateGame();

  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      EXPECT_EQ(game->field[i][j], 0);
    }
  }

  s21::Snake::start_game();

  EXPECT_EQ(game->level, INITIAL_LEVEL);
  EXPECT_EQ(game->speed, INITIAL_SPEED);
  EXPECT_EQ(state->status_game, SHIFTING);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, increase_score) {
  updateCurrentState();
  GameInfo_t *game = getCurrentGame();

  EXPECT_EQ(game->score, 0);

  s21::Snake::increase_score();

  EXPECT_EQ(game->score, 1);

  game->score = 5;

  EXPECT_EQ(game->level, 1);

  s21::Snake::increase_score();

  EXPECT_EQ(game->level, 2);
  EXPECT_EQ(game->score, 6);

  game->score = 55;
  game->level = 10;

  s21::Snake::increase_score();

  EXPECT_EQ(game->level, 10);
  EXPECT_EQ(game->score, 56);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, check_collision) {
  updateCurrentState();
  State_t *state = getCurrentState();

  auto snake = s21::Snake::getSnake();

  snake->clear();

  snake->push_back({10, -1});
  snake->push_back({10, 0});
  snake->push_back({10, 1});
  snake->push_back({10, 2});

  int res = s21::Snake::check_collision(*snake);

  ASSERT_EQ(res, 1);

  snake->clear();

  snake->push_back({9, 5});
  snake->push_back({9, 4});
  snake->push_back({9, 3});
  snake->push_back({9, 2});
  snake->push_back({10, 2});
  snake->push_back({10, 3});
  snake->push_back({10, 4});
  snake->push_back({10, 5});
  snake->push_back({9, 5});
  snake->push_back({8, 5});

  res = s21::Snake::check_collision(*snake);

  ASSERT_EQ(res, 1);

  snake->clear();

  snake->push_back({10, 3});
  snake->push_back({10, 4});
  snake->push_back({10, 5});
  snake->push_back({10, 6});

  state->ball->y = 10;
  state->ball->x = 3;

  res = s21::Snake::check_collision(*snake);

  ASSERT_EQ(res, 2);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, userInput_pause_function) {
  updateCurrentState();
  State_t *state = getCurrentState();

  state->status_game = GAMEOVER;

  userInput(Action);

  ASSERT_EQ(state->status_game, RESTART);

  updateCurrentState();

  ASSERT_EQ(state->status_game, START);

  userInput(Pause);

  ASSERT_EQ(state->status_game, PAUSE);

  userInput(Start);

  ASSERT_EQ(state->status_game, SHIFTING);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, userInput_direction_function) {
  updateCurrentState();
  State_t *state = getCurrentState();

  userInput(Left);

  ASSERT_EQ(state->direction, goes_left);
  state->action = false;

  userInput(Up);

  ASSERT_EQ(state->direction, goes_up);
  state->action = false;

  userInput(Right);

  ASSERT_EQ(state->direction, goes_right);
  state->action = false;

  userInput(Down);

  ASSERT_EQ(state->direction, goes_down);

  userInput(Terminate);
  updateCurrentState();
}

TEST(snake, check_size_snake_function) {
  updateCurrentState();
  State_t *state = getCurrentState();
  auto snake = s21::Snake::getSnake();

  snake->clear();

  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      snake->push_back({i, j});
    }
  }

  s21::Snake::check_size_snake();

  ASSERT_EQ(state->status_game, WINNER);

  userInput(Terminate);
  updateCurrentState();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}