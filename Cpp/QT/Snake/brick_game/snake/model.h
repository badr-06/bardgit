#ifndef BECKEND_SNAKE_H
#define BECKEND_SNAKE_H

#include "../lib.h"
#include <ctime>
#include <fstream>
#include <list>
#include <memory>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define PAUSE_BUTTON_SMALL 112 ///< английская "p" для пауза игры
#define PAUSE_BUTTON_BIG 80 ///< большая английская "P" для пауза игры
#define START_BUTTON_SMALL 115     ///< "s" для старта игры
#define START_BUTTON_BIG 83        ///< большая "S"
#define TERMINATE_BUTTON_SMALL 113 ///< "q" для завершения иры
#define TERMINATE_BUTTON_BIG 81    ///< большая "Q"
#define RESTART_BUTTON_SMALL 114   ///< "r" для рестарта иры
#define RESTART_BUTTON_BIG 82      ///< большая "R"
#define INITIAL_SPEED 500          /// Начальная скорость
#define INITIAL_LEVEL 1            /// начальный уровень
#define PATH_TO_FILE                                                           \
  "../brick_game/snake/snake_highscore.txt" /// Путь до файла в котором лежит
                                            /// высший рекорд

/**
 * @brief Структура для хранения координат на поле.
 */
typedef struct {
  int y;
  int x;

} Point_t;

/** @brief структура состоянии иры
 */
typedef struct {
  int status_game;
  int direction;
  bool is_playing;
  bool game_play;
  bool action;
  long milliseconds;
  Point_t *ball;
} State_t;

/**
 * @brief Структура содержащая напрвления змеи.
 */
typedef enum { goes_up, goes_down, goes_left, goes_right } Route_snake;

/** @brief структура состояний КА
 */
typedef enum {
  INITIAL,
  START,
  RESTART,
  MOVING,
  SHIFTING,
  GAMEOVER,
  PAUSE,
  WINNER
} Status_KA;

/**
 * @brief Класс который содержит все методы и объекты логики игры.
 */
namespace s21 {
class Snake {
private:
  static std::unique_ptr<GameInfo_t> game_s;
  static std::unique_ptr<State_t> state_s;
  static std::list<Point_t> snake_;

public:
  Snake() = delete;

  static State_t *getState();
  static GameInfo_t *getGame();
  static std::list<Point_t> *getSnake();

  static void initialition();
  static void remove_snake_from_filed();
  static void create_field();
  static void clear_field();
  static void create_snake();
  static void moving_snake();
  static void snake_on_field();
  static void terminateGame();
  static void shifting_snake();
  static void restart_game();
  static void clean_field();
  static void create_ball();
  static void start_game();
  static void increase_score();
  static void check_size_snake();

  static int check_collision(std::list<Point_t> temp);
  static long current_time();
};
} // namespace s21

#endif
