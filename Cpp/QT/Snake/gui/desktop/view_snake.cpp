#include "../../brick_game/snake/controller.h"
#include "view.h"

/**
 * @brief Конструктор виджета игры
 *
 * @details Инициализирует графический интерфейс игры, создавая:
 * - Основной виджет-контейнер
 * - Метку с описанием управления
 */
s21::GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {

  controlslabel = new QLabel(this);

  controlslabel->setText("constrols game:<br><br>"
                         "To start the game: S, s<br><br>"
                         "To pause the game: P, p<br><br>"
                         "▲ Вверх: Стрелка вверх<br><br>"
                         "▼ Вниз: Стрелка вниз<br><br>"
                         "◄ Влево: Стрелка влево<br><br>"
                         "► Вправо: Стрелка вправо");
  controlslabel->move(25, 150);
}

/**
 * @brief Обработчик событий отрисовки виджета
 *
 * @details Основной цикл рендеринга игрового интерфейса, выполняющий:
 * 1. Проверку состояния игры
 * 2. Отрисовку трех основных компонентов:
 *    - Панели управления (printcontrols)
 *    - Игрового поля (printgame)
 *    - Информационной панели (printInformationGame)
 * 3. Обновление состояния (updateCurent)
 */
void s21::GameWidget::paintEvent(QPaintEvent *) {

  State_t *state = getCurrentState();

  updateCurrentState();

  if (!state->game_play) {
    this->close();
    return;
  }

  QPainter qp(this);
  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp.setPen(pen);

  QFont boldFont("Arial", 12, QFont::Bold);
  qp.setFont(boldFont);

  printcontrols(&qp);

  if (state->status_game == GAMEOVER || state->status_game == WINNER)
    terminateGame(&qp);
  else
    printgame(&qp);

  printInformationGame(&qp);

  updateCurent();
}

/**
 * @brief Функиция для вывода панели упраления.
 *
 * @details Так как в конструкторе уже создана метка, тут мы просто создаем
 * рамки для этого окна
 */
void s21::GameWidget::printcontrols(QPainter *qp) {

  qp->drawRect(10, 38, 304, 604);
}

/**
 * @brief Отрисовка Игрового поля.
 */
void s21::GameWidget::printgame(QPainter *qp) {

  qp->drawRect(320, 38, 304, 604);

  GameInfo_t *game = getCurrentGame();

  QBrush brush1(Qt::black, Qt::SolidPattern);
  QBrush brush2(Qt::green, Qt::SolidPattern);
  QBrush brush3(Qt::red, Qt::SolidPattern);
  for (int y = 0; y < FIELD_H; y++) {
    for (int x = 0; x < FIELD_W; x++) {
      if (game->field[y][x] == 1) {
        qp->fillRect((x * 30) + 322, (y * 30) + 40, 30, 30, brush1);
      } else if (game->field[y][x] == 2) {
        qp->fillRect((x * 30) + 322, (y * 30) + 40, 30, 30, brush2);
      } else if (game->field[y][x] == 3) {
        qp->fillRect((x * 30) + 322, (y * 30) + 40, 30, 30, brush3);
      }
    }
  }
}

/**
 * @brief Для обработки ввода.
 *
 * @details Вызывается при нажатии клавиши пользователем и принимает введеный
 * параметр.
 */
void s21::GameWidget::keyPressEvent(QKeyEvent *ke) {

  switch (ke->key()) {
  case Qt::Key_S:
    userInput(Start);
    break;
  case Qt::Key_P:
    userInput(Pause);
    break;
  case Qt::Key_Left:
    userInput(Left);
    break;
  case Qt::Key_Right:
    userInput(Right);
    break;
  case Qt::Key_Down:
    userInput(Down);
    break;
  case Qt::Key_Up:
    userInput(Up);
    break;
  case Qt::Key_Q:
    userInput(Terminate);
    break;
  case Qt::Key_R:
    userInput(Action);
    break;
  default:
    break;
  }
}

/**
 * @brief Для отрисовки информации об игре.
 */
void s21::GameWidget::printInformationGame(QPainter *qp) {
  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp->setPen(pen);
  qp->drawRect(630, 38, 304, 604);

  GameInfo_t *game = getCurrentGame();

  qp->drawText(QPoint(640, 300),
               "High score " + QString::number(game->high_score));
  qp->drawText(QPoint(640, 330), "score: " + QString::number(game->score));
  qp->drawText(QPoint(640, 360), "level: " + QString::number(game->level));
  qp->drawText(QPoint(640, 390), "speed: " + QString::number(game->speed));
}

/**
 * @brief Для обновления состояние.
 *
 * @details При вызове функции update() заново вызывается функция paintEvent().
 *
 * @note без функции update() игра не обновлялясь бы.
 */
void s21::GameWidget::updateCurent() {
  State_t *state = getCurrentState();
  if (state->status_game != PAUSE && state->game_play) {
    update();
  }
}

void s21::GameWidget::terminateGame(QPainter *qp) {
  qp->drawRect(320, 38, 304, 604);

  GameInfo_t *game = getCurrentGame();
  State_t *state = getCurrentState();

  QBrush brush1(Qt::black, Qt::SolidPattern);
  QBrush brush3(Qt::red, Qt::SolidPattern);
  for (int y = 0; y < FIELD_H; y++) {
    for (int x = 0; x < FIELD_W; x++) {
      if (game->field[y][x] == 1) {
        qp->fillRect((x * 30) + 322, (y * 30) + 40, 30, 30, brush1);
      } else if (game->field[y][x] == 3) {
        qp->fillRect((x * 30) + 322, (y * 30) + 40, 30, 30, brush3);
      }
    }
  }

  if (state->status_game == WINNER) {
    qp->drawText(QPoint(350, 300), "You Winner!");
    qp->drawText(QPoint(350, 330), " Press 'R' to restart");
  } else {
    qp->drawText(QPoint(350, 300), "Game over!");
    qp->drawText(QPoint(350, 330), " Press 'R' to restart");
  }
}