#include "maze_widget.h"

#include <QInputDialog>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>

MazeWidget::MazeWidget(MazeModel* model, QWidget* parent)
    : QWidget(parent), model_(model) {
  setFocusPolicy(Qt::StrongFocus);
  setMinimumSize(640, 480);
}

void MazeWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.fillRect(rect(), QColor(0, 80, 0));

  if (model_->rows() == 0 || model_->columns() == 0) {
    return;
  }

  const int cell_w = 24;
  const int cell_h = 24;
  const int offset_x = 40;
  const int offset_y = 40;

  QPen wall_pen(Qt::black, 2);
  QPen path_pen(QColor(255, 215, 0), 2);
  painter.setPen(wall_pen);

  for (int j = 0; j < model_->columns(); ++j) {
    painter.drawText(offset_x + j * cell_w + cell_w / 2, offset_y - 10,
                     QString::number(j + 1));
  }

  for (int i = 0; i < model_->rows(); ++i) {
    painter.drawText(offset_x - 20, offset_y + i * cell_h + cell_h / 2 + 5,
                     QString::number(i + 1));
  }

  for (int i = 0; i <= model_->rows(); ++i) {
    for (int j = 0; j <= model_->columns(); ++j) {
      const int x = offset_x + j * cell_w;
      const int y = offset_y + i * cell_h;
      painter.drawPoint(x, y);
    }
  }

  for (int i = 0; i < model_->rows(); ++i) {
    for (int j = 0; j < model_->columns(); ++j) {
      const int x = offset_x + j * cell_w;
      const int y = offset_y + i * cell_h;

      if (model_->solution()[i][j]) {
        painter.setPen(path_pen);
        painter.drawEllipse(x + cell_w / 4, y + cell_h / 4, cell_w / 2,
                            cell_h / 2);
        painter.setPen(wall_pen);
      }

      if (model_->verticalWalls()[i][j]) {
        painter.drawLine(x + cell_w, y, x + cell_w, y + cell_h);
      } else if (j == model_->columns() - 1) {
        painter.drawLine(x + cell_w, y, x + cell_w, y + cell_h);
      }

      if (model_->horizontalWalls()[i][j]) {
        painter.drawLine(x, y + cell_h, x + cell_w, y + cell_h);
      } else if (i == model_->rows() - 1) {
        painter.drawLine(x, y + cell_h, x + cell_w, y + cell_h);
      }
    }
  }

  painter.setPen(QColor(255, 215, 0));
  const int hint_y = offset_y + model_->rows() * cell_h + 30;
  painter.drawText(10, hint_y, tr("Q — назад | F — найти путь | G — очистить"));
}

void MazeWidget::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Q:
      emit backRequested();
      break;
    case Qt::Key_F:
      solveMaze();
      break;
    case Qt::Key_G:
      clearSolution();
      break;
    default:
      QWidget::keyPressEvent(event);
      break;
  }
}

void MazeWidget::solveMaze() {
  bool ok = false;

  const int y1 =
      QInputDialog::getInt(this, tr("Начало маршрута"),
                           tr("Строка начала (1-%1):").arg(model_->rows()), 1,
                           1, model_->rows(), 1, &ok);
  if (!ok) return;

  const int x1 =
      QInputDialog::getInt(this, tr("Начало маршрута"),
                           tr("Столбец начала (1-%1):").arg(model_->columns()),
                           1, 1, model_->columns(), 1, &ok);
  if (!ok) return;

  const int y2 =
      QInputDialog::getInt(this, tr("Конец маршрута"),
                           tr("Строка конца (1-%1):").arg(model_->rows()), 1, 1,
                           model_->rows(), 1, &ok);
  if (!ok) return;

  const int x2 =
      QInputDialog::getInt(this, tr("Конец маршрута"),
                           tr("Столбец конца (1-%1):").arg(model_->columns()),
                           1, 1, model_->columns(), 1, &ok);
  if (!ok) return;

  model_->solve(y1 - 1, x1 - 1, y2 - 1, x2 - 1);
  update();
}

void MazeWidget::clearSolution() {
  model_->clearSolution();
  update();
}
