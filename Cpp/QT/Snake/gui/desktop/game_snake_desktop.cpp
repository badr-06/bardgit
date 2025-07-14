#include "../../brick_game/snake/controller.h"
#include "view.h"

/**
 * @brief Стартовая функция в котором создается класс для отрисовки десктопа.
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  updateCurrentState();

  s21::GameWidget widget; // Главный виджет
  widget.resize(1000, 700); // Размер окна (подберите под вашу игру)
  widget.show();

  return app.exec(); // Главный цикл Qt
}