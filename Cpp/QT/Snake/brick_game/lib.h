#ifndef LIB_H
#define LIB_H


#define FIELD_H 20  ///< высота поля
#define FIELD_W 10  ///< ширина поля

#define FIGURE_H 4  ///< высота матрицы для фигуры
#define FIGURE_W 4  ///< ширина матрицы для фигуры

/** @brief структура управления игрой
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;


/** @brief структура информации об игре
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

void userInput(UserAction_t);

GameInfo_t updateCurrentState();

#endif //LIB_H