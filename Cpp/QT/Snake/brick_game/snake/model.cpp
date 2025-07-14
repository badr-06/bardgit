#include "model.h"

namespace s21 {
std::unique_ptr<State_t> Snake::state_s = std::make_unique<State_t>();
std::unique_ptr<GameInfo_t> Snake::game_s = std::make_unique<GameInfo_t>();
std::list<Point_t> Snake::snake_;
} // namespace s21

/**
 * @brief Функция которая инициализирует игру.
 */
void s21::Snake::initialition() {
  create_field();
  create_snake();

  snake_on_field();

  state_s->game_play = true;
  state_s->action = false;
  state_s->status_game = INITIAL;
}

/**
 * @brief Функция которая удаляет змею с поля игры.
 */
void s21::Snake::remove_snake_from_filed() {
  for (auto to : snake_) {
    if (game_s->field[to.y][to.x] == 1 || game_s->field[to.y][to.x] == 3)
      game_s->field[to.y][to.x] = 0;
  }
}

/**
 * @brief Создает поле выделяя для него память и инициализируя его нулями.
 * и выделяет память для пременной содержащая координаты мяча.
 */
void s21::Snake::create_field() {
  game_s->field = new int *[FIELD_H];
  for (int i = 0; i < FIELD_H; ++i) {
    game_s->field[i] = new int[FIELD_W];
  }

  clean_field();

  state_s->ball = new Point_t();
}

/**
 * @brief противоположна функции create_field().
 */
void s21::Snake::clear_field() {
  if (game_s->field != nullptr) {
    for (int i = 0; i < FIELD_H; ++i) {
      delete[] game_s->field[i];
    }
    delete[] game_s->field;
    game_s->field = nullptr;
  }

  if (state_s->ball != nullptr) {
    delete state_s->ball;
    state_s->ball = nullptr;
  }
}

/**
 * @brief создает змею.
 */
void s21::Snake::create_snake() {
  snake_.push_back({10, 4});
  snake_.push_back({10, 5});
  snake_.push_back({10, 6});
  snake_.push_back({10, 7});
}

/**
 * @brief Возвращает Структуру состояния.
 */
State_t *s21::Snake::getState() { return state_s.get(); }

/**
 * @brief Возвращает Информацию об игре.
 */
GameInfo_t *s21::Snake::getGame() { return game_s.get(); }

/**
 * @brief возвращает список содержащий координаты змеи на поле.
 */
std::list<Point_t> *s21::Snake::getSnake() { return &snake_; }

/**
 * @brief обрабатывает движения змеи по кнопке.
 */
void s21::Snake::moving_snake() {
  if ((current_time() - state_s->milliseconds) >= game_s->speed) {
    state_s->status_game = SHIFTING;
  } else {
    if (state_s->action &&
        (current_time() - state_s->milliseconds) >= (game_s->speed / 2)) {
      auto to = snake_.begin();
      if (state_s->direction == goes_up) {
        snake_.push_front({to->y - 1, to->x});
        state_s->milliseconds = current_time();
      } else if (state_s->direction == goes_down) {
        snake_.push_front({to->y + 1, to->x});
        state_s->milliseconds = current_time();
      } else if (state_s->direction == goes_left) {
        snake_.push_front({to->y, to->x - 1});
        state_s->milliseconds = current_time();
      } else if (state_s->direction == goes_right) {
        snake_.push_front({to->y, to->x + 1});
        state_s->milliseconds = current_time();
      }
      auto temp(snake_);
      temp.pop_back();
      int check = check_collision(temp);
      if (check == 1) {
        state_s->status_game = GAMEOVER;
      } else if (check == 2) {
        remove_snake_from_filed();
        game_s->field[state_s->ball->y][state_s->ball->x] = 0;
        snake_on_field();
        create_ball();
        increase_score();
        check_size_snake();
      } else {
        remove_snake_from_filed();
        snake_ = temp;
        snake_on_field();
      }
      state_s->action = false;
    }
  }
}

/**
 * @brief переносит змею на поле.
 */
void s21::Snake::snake_on_field() {
  auto to = snake_.begin();
  game_s->field[to->y][to->x] = 3;
  ++to;
  for (; to != snake_.end(); ++to) {
    game_s->field[to->y][to->x] = 1;
  }
}

/**
 * @brief  проверяет столкновения змеи.
 */
int s21::Snake::check_collision(std::list<Point_t> temp) {
  auto head = temp.begin();

  if ((head->y >= FIELD_H || head->y < 0) ||
      (head->x >= FIELD_W || head->x < 0)) {
    return 1;
  }

  for (auto it = ++temp.begin(); it != temp.end(); ++it) {
    if (head->y == it->y && head->x == it->x)
      return 1;
  }

  for (auto it = ++temp.begin(); it != temp.end(); ++it) {
    if (head->x == state_s->ball->x && head->y == state_s->ball->y)
      return 2;
  }

  return 0;
}

/**
 * @brief возвращает время с точностью в миллисекундах.
 */
long s21::Snake::current_time() {
  struct timeval tv;

  gettimeofday(&tv, nullptr);
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Функция которая вызывается при проигрше или по заврешении игры.
 */
void s21::Snake::terminateGame() {
  clean_field();
  snake_.clear();
  if (game_s->high_score < game_s->score) {
    std::ofstream file(PATH_TO_FILE);
    if (file.is_open()) {
      file << game_s->score;
      file.close();
    }
  }
  if (state_s->game_play == false) {
    clear_field();
    state_s->is_playing = false;
  }
}

/**
 * @brief Движение змеи по времени.
 */
void s21::Snake::shifting_snake() {
  auto to = snake_.begin();
  if (state_s->direction == goes_up) {
    snake_.push_front({to->y - 1, to->x});
  } else if (state_s->direction == goes_down) {
    snake_.push_front({to->y + 1, to->x});
  } else if (state_s->direction == goes_left) {
    snake_.push_front({to->y, to->x - 1});
  } else if (state_s->direction == goes_right) {
    snake_.push_front({to->y, to->x + 1});
  }
  auto temp(snake_);
  temp.pop_back();
  int check = check_collision(temp);
  if (check == 1) {
    state_s->status_game = GAMEOVER;
  } else if (check == 2) {
    remove_snake_from_filed();
    game_s->field[state_s->ball->y][state_s->ball->x] = 0;
    snake_on_field();
    create_ball();
    increase_score();
    check_size_snake();
  } else {
    remove_snake_from_filed();
    snake_ = temp;
    snake_on_field();
  }

  if (state_s->status_game != GAMEOVER) {
    state_s->milliseconds = current_time();
    state_s->status_game = MOVING;
  }
}

/**
 * @brief Для рестарта игры.
 */
void s21::Snake::restart_game() {
  create_snake();
  snake_on_field();
  state_s->status_game = START;
}

/**
 * @brief заполняет поле нулями.
 */
void s21::Snake::clean_field() {
  if (game_s->field == nullptr)
    return;

  for (int i = 0; i < FIELD_H; ++i) {
    for (int j = 0; j < FIELD_W; ++j) {
      game_s->field[i][j] = 0;
    }
  }
}

/**
 * @brief Создает мячик с рандомными координатами на поле.
 */
void s21::Snake::create_ball() {
  srand(time(0));

  bool flag = true;
  while (flag) {
    state_s->ball->y = rand() % FIELD_H;
    state_s->ball->x = rand() % FIELD_W;
    if (game_s->field[state_s->ball->y][state_s->ball->x] == 0)
      flag = false;
  }
  game_s->field[state_s->ball->y][state_s->ball->x] = 2;
}

/**
 * @brief Функция при старте игры.
 */
void s21::Snake::start_game() {
  state_s->status_game = SHIFTING;
  state_s->direction = goes_left; // изначальное направление
  create_ball();

  game_s->speed = INITIAL_SPEED;
  game_s->level = INITIAL_LEVEL;
  game_s->score = 0;

  std::ifstream file(PATH_TO_FILE);
  if (file.is_open()) {
    file >> game_s->high_score;
    file.close();
  }
}

/**
 * @brief Вызывается если змея съела мячик чтобы увелилисть счет. В зависимости
 * от счета увеличивается уровень и уменьшаеться скорость.
 */
void s21::Snake::increase_score() {
  game_s->score += 1;
  if (game_s->score >= 5 * game_s->level) {
    if (game_s->level < 10) {
      game_s->level += 1;
      game_s->speed -= 30;
    }
  }
}

/**
 * @brief Функция котрая проверяет размер змеи.
 *
 * @details Если размер змеи больше или равно 200 то игрок выиграл.
 */
void s21::Snake::check_size_snake() {
  if (snake_.size() >= 200) {
    state_s->status_game = WINNER;
  }
}
