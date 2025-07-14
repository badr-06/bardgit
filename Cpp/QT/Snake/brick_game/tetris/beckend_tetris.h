#ifndef BACKEND_H
#define BACKEND_H

#include "../lib.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define PAUSE_BUTTON_SMALL 112 ///< английская "p" для пауза игры
#define PAUSE_BUTTON_BIG 80 ///< большая английская "P" для пауза игры
#define START_BUTTON_SMALL 115     ///< "s" для старта игры
#define START_BUTTON_BIG 83        ///< большая "S"
#define TERMINATE_BUTTON_SMALL 113 ///< "q" для завершения иры
#define TERMINATE_BUTTON_BIG 81    ///< большая "Q"
#define ACTION_BUTTON 32 ///< space(пробел) для переворота фигуры
#define ACCELERATION_BUTTON 122    ///< "z" ускоряет фигуры
#define ACCELERATION_BUTTON_BIG 90 ///< большая "Z"

/** @brief структура состояний КА
 */
typedef enum {
  Initial,
  Spawn,
  Moving,
  Attaching,
  Shifting,
  Move_block,
  PAUSE,
  GAMEOVER
} Status_t;

/** @brief структура названия фигур
 */
typedef enum { I, O, J, L, Z, T, S } Block_t;

/** @brief структура состоянии иры
 */
typedef struct {
  int status_game;
  int **field;
  int **block;
  int **nextBlock;
  int Y;
  int X;
  int is_playing;
  int action_move;
  long milliseconds;
  int type_Figure;
  int next_type_Figure;
  int gradus;
  bool acceleration;
  bool game_play;
} State_t;

State_t *getCurrentState();
GameInfo_t *getCurrentGame();
void initialization();
void createFieldBlock();
int **generateFigure();
int **createMatrix(int n, int m);
void freeMatrix(int **matrix, int rows);
void spawnFigure();
void copyMatrix(int **matrix1, int **matrix2, int n, int m);
void shiftingBlock();
bool checkStatusBlock();
bool checkoverflow();
void moveRightBlock();
void moveLeftBlock();
void attachingBlock();
void terminateGame();
void unsetFigure();
void setFigure();
void game();
void movingBlock();
long currentTime();
void cleanMatrix(int **matrix);
void del_line();
void rotate();

#endif