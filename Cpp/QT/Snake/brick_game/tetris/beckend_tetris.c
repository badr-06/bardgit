#include "beckend_tetris.h"
/**
 * @brief для вызова структуры State_t объявлена статически.
 */
State_t *getCurrentState() {
  static State_t state;
  return &state;
}

/**
 * @brief для вызова структуры GameInfo_t объявлена статически.
 */
GameInfo_t *getCurrentGame() {
  static GameInfo_t game;
  return &game;
}

/**
 * @brief функция для инициализации игры.
 */
void initialization() {
  State_t *state = getCurrentState();

  createFieldBlock();

  state->status_game = Initial;
}

/**
 * @brief функция для выделения памяти полю, блоку для фигуры, следующему блоку
 * для фигуры и установки уровня, скорости и т.д.
 */
void createFieldBlock() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  game->field = (int **)calloc(FIELD_H, sizeof(int **));
  for (int i = 0; i < FIELD_H; i++) {
    game->field[i] = (int *)calloc(FIELD_W, sizeof(int **));
  }

  state->block = (int **)calloc(FIGURE_H, sizeof(int **));
  for (int i = 0; i < FIGURE_H; i++) {
    state->block[i] = (int *)calloc(FIGURE_W, sizeof(int **));
  }

  game->next = generateFigure();

  state->status_game = Initial;
  state->Y = 0;
  state->X = 3;
  state->is_playing = 0;
  state->acceleration = false;
  state->game_play = true;
  game->level = 1;
  game->score = 0;
  game->pause = false;
  game->speed = 10;
  game->high_score = 600;
}

/**
 * @brief функция создает двумерный массив с динамическим выделением памяти
 *
 * @param n количество строк
 * @param m количество столбцов
 * @param return возвращает массив
 */
int **createMatrix(int n, int m) {
  int **matrix;
  matrix = (int **)calloc(n, sizeof(int **));
  for (int i = 0; i < n; i++) {
    matrix[i] = (int *)calloc(m, sizeof(int **));
  }

  return matrix;
}

/**
 * @brief функция для очитски памяти
 *
 * @param matrix массив который нужно очистить
 * @param rows количество строк
 */
void freeMatrix(int **matrix, int rows) {
  for (int i = 0; i < rows; ++i) {
    free(matrix[i]);
  }
  free(matrix);
}

/**
 * @brief функция для генерации фигуры.
 * Возвращает рандомно сгенерированную фигуру
 *
 */
int **generateFigure() {
  State_t *state = getCurrentState();

  state->next_type_Figure = rand() % 7;

  int **matrix = createMatrix(FIGURE_H, FIGURE_W);

  if (state->next_type_Figure == I) {
    matrix[0][1] = 1;
    matrix[1][1] = 1;
    matrix[2][1] = 1;
    matrix[3][1] = 1;
  } else if (state->next_type_Figure == J) {
    matrix[0][2] = 1;
    matrix[1][2] = 1;
    matrix[2][2] = 1;
    matrix[2][1] = 1;
  } else if (state->next_type_Figure == L) {
    matrix[0][1] = 1;
    matrix[1][1] = 1;
    matrix[2][1] = 1;
    matrix[2][2] = 1;
  } else if (state->next_type_Figure == O) {
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[1][1] = 1;
    matrix[1][2] = 1;
  } else if (state->next_type_Figure == Z) {
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[1][2] = 1;
    matrix[1][3] = 1;
  } else if (state->next_type_Figure == T) {
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][1] = 1;
    matrix[1][2] = 1;
  } else if (state->next_type_Figure == S) {
    matrix[0][2] = 1;
    matrix[0][1] = 1;
    matrix[1][1] = 1;
    matrix[1][0] = 1;
  }

  return matrix;
}

/**
 * @brief функция для появления фигуры на поле
 *
 */
void spawnFigure() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  state->type_Figure = state->next_type_Figure;
  state->gradus = 0;

  copyMatrix(state->block, game->next, FIGURE_H, FIGURE_W);
  freeMatrix(game->next, FIGURE_H);
  game->next = generateFigure();

  state->milliseconds = currentTime();
  state->status_game = Moving;
}

/**
 * @brief основная функиця с которой все начинается вызывается в фронтенде.
 *
 * @param return возращает состояние игры
 */
GameInfo_t updateCurrentState() {
  State_t *state = getCurrentState();

  GameInfo_t *game_info = getCurrentGame();

  struct timeval tv;

  gettimeofday(&tv, NULL);
  long time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));

  srand(time);

  if (state->is_playing == 0) {
    initialization();
    state->is_playing = 1;
  }

  game();

  if (state->status_game != GAMEOVER)
    setFigure();

  return *game_info;
}

/**
 * @brief функция для конечного автомата
 *
 */
void game() {
  State_t *state = getCurrentState();

  if (state->status_game == Initial) {
    // updateCurrentAction();
  } else if (state->status_game == Spawn) {
    if (!checkoverflow()) {
      spawnFigure();
    } else {
      state->status_game = GAMEOVER;
    }
  } else if (state->status_game == Shifting) {
    shiftingBlock();
  } else if (state->status_game == Moving) {
    movingBlock();
  } else if (state->status_game == Attaching) {
    attachingBlock();
  } else if (state->status_game == GAMEOVER) {
    terminateGame();
  }
}

/**
 * @brief функция для копирования одной матрицы в другую
 *
 * @param matrix1 матрица в которой копируется данные из другой матрицы
 * @param matrix2 матрица из которой копируется данные
 * @param n Количество строк
 * @param m Количество столбцов
 */
void copyMatrix(int **matrix1, int **matrix2, int n, int m) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      matrix1[i][j] = 0;
      matrix1[i][j] = matrix2[i][j];
    }
  }
}

/**
 * @brief функция для обработки ввода клавиш пользователем
 *
 */
void userInput(UserAction_t action) {
  State_t *state = getCurrentState();

  if (action == Start && state->status_game == Initial) {
    state->status_game = Spawn;
  } else if ((action == Right || action == Left || action == Action) &&
             (state->status_game == Shifting || state->status_game == Moving) &&
             state->status_game != Initial) {
    state->action_move = action;
  } else if (action == Down && state->status_game != Initial &&
             (state->status_game == Shifting || state->status_game == Moving)) {
    state->status_game = Shifting;
  } else if (action == Terminate) {
    state->status_game = GAMEOVER;
  } else if ((action == Pause && state->status_game != Initial) ||
             (action == Start && state->status_game == PAUSE)) {
    if (state->status_game == PAUSE)
      state->status_game = Moving;
    else if (action == Pause)
      state->status_game = PAUSE;
  } else if (action == Up &&
             (state->status_game == Shifting || state->status_game == Moving)) {
    state->acceleration = true;
  }
}

/**
 * @brief функция для движения фигуры вниз без ввода пользователя
 *
 */
void shiftingBlock() {
  State_t *state = getCurrentState();

  unsetFigure();

  ++state->Y;
  if (checkStatusBlock()) {
    state->status_game = Attaching;
    --state->Y;
  } else if (!state->acceleration) {
    state->milliseconds = currentTime();
    state->status_game = Moving;
  }
}

/**
 * @brief функция для проверки столкновении фигуры
 *
 * @param true если фигура столкнулась
 * @param false в противном случае
 */
bool checkStatusBlock() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      if (state->block[i][j] && (i + state->Y) == FIELD_H) {
        return true;
      } else if (state->block[i][j] &&
                 ((j + state->X < 0) || (j + state->X >= FIELD_W))) {
        return true;
      } else if (state->block[i][j] &&
                 game->field[i + state->Y][j + state->X]) {
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief функция для проверки переполнения поля
 *
 * @param true если поле переполнено
 * @param false в противном случае
 */
bool checkoverflow() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      if (game->next[i][j] && game->field[i + state->Y][j + state->X]) {
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief функция для прикрепления фигура к поле
 *
 */
void attachingBlock() {
  State_t *state = getCurrentState();

  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      state->block[i][j] = 0;
    }
  }
  state->Y = 0;
  state->X = 3;

  del_line();

  state->status_game = Spawn;
  state->acceleration = false;
}

/**
 * @brief функция для проверки заполненных строк, если такие есть то удаляем и
 * прибавлеям очки
 *
 */
void del_line() {
  GameInfo_t *game = getCurrentGame();

  int index_i;
  int line = 0;
  bool i_flag = true;
  bool check_line = false;
  int sum = 0;
  int **matrix = createMatrix(FIELD_H, FIELD_W);

  for (int i = FIELD_H - 1; i >= 0; --i) {
    for (int j = 0; j < FIELD_W; ++j) {
      if (i_flag) {
        index_i = i;
      }
      sum += game->field[i][j];
      if (sum == 10) {
        check_line = true;
        i_flag = false;
        line++;
      }
    }
    sum = 0;
  }

  if (check_line) {
    if (index_i < 19) {
      for (int i = FIELD_H - 1; i > index_i; --i) {
        for (int j = 0; j < FIELD_W; ++j) {
          matrix[i][j] = game->field[i][j];
        }
      }
    }

    for (int i = index_i; i >= 0; --i) {
      for (int j = 0; j < FIELD_W; ++j) {
        if (i - line >= 0) {
          matrix[i][j] = game->field[i - line][j];
        } else {
          matrix[i][j] = 0;
        }
      }
    }
    switch (line) {
    case 1:
      game->score += 100;
      break;
    case 2:
      game->score += 300;
      break;
    case 3:
      game->score += 700;
      break;
    case 4:
      game->score += 1500;
    default:
      break;
    };

    int temp = game->score / game->high_score;

    if (temp >= game->level && temp + game->level + temp < 11) {
      game->level += temp;
      game->speed -= temp * 70;
    } else if (game->level + temp > 10) {
      game->level = 10;
      game->speed = 300;
    }

    copyMatrix(game->field, matrix, FIELD_H, FIELD_W);
  }
  freeMatrix(matrix, FIELD_H);
}

/**
 * @brief функция для обработки клавиши движения фигуры
 *
 */
void movingBlock() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  unsetFigure();

  if (state->action_move == Right) {
    moveRightBlock();
    state->action_move = 0;
  } else if (state->action_move == Left) {
    moveLeftBlock();
    state->action_move = 0;
  } else if (state->action_move == Action) {
    rotate();
    state->action_move = 0;
  }

  if (state->acceleration) {
    state->milliseconds = 0;
  }

  if ((currentTime() - state->milliseconds >= game->speed)) {
    state->status_game = Shifting;
  }
}

/**
 * @brief функция для фигуры с поля
 *
 */
void unsetFigure() {
  GameInfo_t *game = getCurrentGame();
  State_t *state = getCurrentState();

  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      if (state->block[i][j] && game->field[i + state->Y][j + state->X]) {
        game->field[i + state->Y][j + state->X] = 0;
      }
    }
  }
}

/**
 * @brief противополжна функции "unsetFigure"
 *
 */
void setFigure() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  int n = state->Y;
  int m = state->X;
  for (int i = n, i_f = 0; i < FIGURE_H + n; ++i, ++i_f) {
    for (int j = m, j_f = 0; j < FIGURE_W + m; ++j, ++j_f) {
      if (state->block[i_f][j_f]) {
        game->field[i][j] = state->block[i_f][j_f];
      }
    }
  }
}

/**
 * @brief функция для сдвига фигуры вправо
 *
 */
void moveRightBlock() {
  State_t *state = getCurrentState();

  state->X++;
  if (checkStatusBlock()) {
    state->X--;
  }
}

/**
 * @brief функция для сдвига фигуры влево
 *
 */
void moveLeftBlock() {
  State_t *state = getCurrentState();

  state->X--;
  if (checkStatusBlock()) {
    state->X++;
  }
}

/**
 * @brief функция для заполнения матрицу с фигуром нулями
 *
 * @param matrix матрица которую нужно заполнить
 */
void cleanMatrix(int **matrix) {
  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      matrix[i][j] = 0;
    }
  }
}

/**
 * @brief функция для переворота фигуры
 *
 */
void rotate() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();
  int x = state->X;
  int y = state->Y;
  int temp = state->gradus;

  int **matrix = createMatrix(FIGURE_H, FIGURE_W);
  bool check_status_block = true;

  if (state->type_Figure == I) {
    if (state->gradus == 0) {
      matrix[1][0] = 1;
      matrix[1][1] = 1;
      matrix[1][2] = 1;
      matrix[1][3] = 1;
      state->gradus = 90;
    } else if (state->gradus == 90) {
      matrix[0][1] = 1;
      matrix[1][1] = 1;
      matrix[2][1] = 1;
      matrix[3][1] = 1;
      state->gradus = 0;
    }
  } else if (state->type_Figure == J) {
    if (state->gradus == 0) {
      matrix[1][3] = 1;
      matrix[1][2] = 1;
      matrix[1][1] = 1;
      matrix[0][1] = 1;
      state->gradus = 90;
    } else if (state->gradus == 90) {
      matrix[2][2] = 1;
      matrix[1][2] = 1;
      matrix[0][2] = 1;
      matrix[0][3] = 1;
      state->gradus = 180;
    } else if (state->gradus == 180) {
      matrix[1][1] = 1;
      matrix[1][2] = 1;
      matrix[1][3] = 1;
      matrix[2][3] = 1;
      state->gradus = 270;
    } else {
      matrix[0][2] = 1;
      matrix[1][2] = 1;
      matrix[2][2] = 1;
      matrix[2][1] = 1;
      state->gradus = 0;
    }
  } else if (state->type_Figure == L) {
    if (state->gradus == 0) {
      matrix[1][2] = 1;
      matrix[1][1] = 1;
      matrix[1][0] = 1;
      matrix[2][0] = 1;
      state->gradus = 90;
    } else if (state->gradus == 90) {
      matrix[2][1] = 1;
      matrix[1][1] = 1;
      matrix[0][1] = 1;
      matrix[0][0] = 1;
      state->gradus = 180;
    } else if (state->gradus == 180) {
      matrix[1][0] = 1;
      matrix[1][1] = 1;
      matrix[1][2] = 1;
      matrix[0][2] = 1;
      state->gradus = 270;
    } else {
      matrix[0][1] = 1;
      matrix[1][1] = 1;
      matrix[2][1] = 1;
      matrix[2][2] = 1;
      state->gradus = 0;
    }
  } else if (state->type_Figure == Z) {
    if (state->gradus == 0) {
      matrix[0][2] = 1;
      matrix[1][2] = 1;
      matrix[1][1] = 1;
      matrix[2][1] = 1;
      state->gradus = 90;
    } else {
      matrix[0][1] = 1;
      matrix[0][2] = 1;
      matrix[1][2] = 1;
      matrix[1][3] = 1;
      state->gradus = 0;
    }
  } else if (state->type_Figure == T) {
    if (state->gradus == 0) {
      matrix[0][1] = 1;
      matrix[1][1] = 1;
      matrix[2][1] = 1;
      matrix[1][2] = 1;
      state->gradus = 90;
    } else if (state->gradus == 90) {
      matrix[1][0] = 1;
      matrix[1][1] = 1;
      matrix[1][2] = 1;
      matrix[2][1] = 1;
      state->gradus = 180;
    } else if (state->gradus == 180) {
      matrix[0][1] = 1;
      matrix[1][1] = 1;
      matrix[2][1] = 1;
      matrix[1][0] = 1;
      state->gradus = 270;
    } else {
      matrix[1][0] = 1;
      matrix[1][1] = 1;
      matrix[1][2] = 1;
      matrix[0][1] = 1;
      state->gradus = 0;
    }
  } else if (state->type_Figure == S) {
    if (state->gradus == 0) {
      matrix[0][1] = 1;
      matrix[1][1] = 1;
      matrix[1][2] = 1;
      matrix[2][2] = 1;
      state->gradus = 90;
    } else {
      matrix[0][2] = 1;
      matrix[0][1] = 1;
      matrix[1][1] = 1;
      matrix[1][0] = 1;
      state->gradus = 0;
    }
  }

  for (int i = 0; i < FIGURE_H; ++i) {
    for (int j = 0; j < FIGURE_W; ++j) {
      if (matrix[i][j] == 1 &&
          (i + y >= FIELD_H || i + y < 0 || j + x >= FIELD_W || j + x < 0 ||
           game->field[i + y][j + x] == 1))
        check_status_block = false;
    }
  }

  if (check_status_block && state->type_Figure != O) {
    cleanMatrix(state->block);
    copyMatrix(state->block, matrix, FIGURE_H, FIGURE_W);
    freeMatrix(matrix, FIGURE_H);
  } else {
    freeMatrix(matrix, FIGURE_H);
    state->gradus = temp;
    ;
  }
}

/**
 * @brief функция возвращает текущее вреямя + время задержки фигуры, в
 * миллисекундах
 *
 */
long currentTime() {
  GameInfo_t *game = getCurrentGame();
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) + game->speed;
}

/**
 * @brief функция для очистки всей выделенной памяти, по завершении игры
 *
 */
void terminateGame() {
  State_t *state = getCurrentState();
  GameInfo_t *game = getCurrentGame();

  freeMatrix(state->block, FIGURE_H);
  freeMatrix(game->field, FIELD_H);
  freeMatrix(game->next, FIGURE_H);

  state->game_play = false;
}