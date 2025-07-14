#include "controller.h"

/**
 * @brief основная функиця с которой все начинается вызывается в фронтенде.
 *
 * @param return возращает состояние игры
 */
GameInfo_t updateCurrentState() {
  State_t *state = s21::Snake::getState();
  GameInfo_t *game = s21::Snake::getGame();

  if (!state->is_playing) {
    s21::Snake::initialition();
    state->is_playing = true;
  }

  run();

  return *game;
}

/**
 * @brief Функция в октором описан КА(Конечный Автомат).
 *
 */
void run() {

  State_t *state = s21::Snake::getState();

  if (state->status_game == START) {
    s21::Snake::start_game();
  } else if (state->status_game == RESTART) {
    s21::Snake::restart_game();
  } else if (state->status_game == MOVING) {
    s21::Snake::moving_snake();
  } else if (state->status_game == SHIFTING) {
    s21::Snake::shifting_snake();
  } else if (state->status_game == GAMEOVER || state->status_game == WINNER) {
    s21::Snake::terminateGame();
  }
}

/**
 * @brief Функция которая взвращает Структуру состояния.
 */
State_t *getCurrentState() { return s21::Snake::getState(); }

/**
 * @brief Функция которая взвращает Инофрмацию об Игре.
 */
GameInfo_t *getCurrentGame() { return s21::Snake::getGame(); }

/**
 * @brief Функция которая принимает ввод от пользователя и обрабавтывает его.
 */
void userInput(UserAction_t action) {
  State_t *state = s21::Snake::getState();

  if (action == Start &&
      (state->status_game == GAMEOVER || state->status_game == INITIAL)) {
    state->status_game = START;
  } else if (action == Left && state->direction != goes_right &&
             state->action == false && state->status_game != PAUSE) {
    state->direction = goes_left;
    state->action = true;
  } else if (action == Right && state->direction != goes_left &&
             state->action == false && state->status_game != PAUSE) {
    state->direction = goes_right;
    state->action = true;
  } else if (action == Up && state->direction != goes_down &&
             state->action == false && state->status_game != PAUSE) {
    state->direction = goes_up;
    state->action = true;
  } else if (action == Down && state->direction != goes_up &&
             state->action == false && state->status_game != PAUSE) {
    state->direction = goes_down;
    state->action = true;
  } else if (action == Terminate) {
    state->status_game = GAMEOVER;
    state->game_play = false;
  } else if ((action == Pause && state->status_game != INITIAL) ||
             (action == Start && state->status_game == PAUSE)) {
    if (state->status_game == PAUSE)
      state->status_game = SHIFTING;
    else if (action == Pause)
      state->status_game = PAUSE;
  } else if (action == Action && state->status_game == GAMEOVER) {
    state->status_game = RESTART;
  }
}