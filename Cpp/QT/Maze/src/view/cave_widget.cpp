#include "cave_widget.h"

#include <QKeyEvent>
#include <QPainter>
#include <QShowEvent>

CaveWidget::CaveWidget(CaveModel* model, QWidget* parent)
    : QWidget(parent), model_(model) {
  setFocusPolicy(Qt::StrongFocus);
  setMinimumSize(640, 480);
  connect(&timer_, &QTimer::timeout, this, &CaveWidget::nextStep);
}

void CaveWidget::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  if (model_->updateMode() == CaveUpdateMode::Automatic) {
    timer_.start(model_->timeDelay());
  }
}

void CaveWidget::hideEvent(QHideEvent* event) {
  timer_.stop();
  QWidget::hideEvent(event);
}

void CaveWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.fillRect(rect(), QColor(0, 80, 0));

  if (model_->rows() == 0 || model_->columns() == 0) {
    return;
  }

  const int cell_size = 16;
  const int offset_x = 20;
  const int offset_y = 20;

  for (int i = 0; i < model_->rows(); ++i) {
    for (int j = 0; j < model_->columns(); ++j) {
      const int x = offset_x + j * cell_size;
      const int y = offset_y + i * cell_size;

      if (model_->matrix()[i][j]) {
        painter.fillRect(x, y, cell_size, cell_size, QColor(255, 215, 0));
      } else {
        painter.fillRect(x, y, cell_size, cell_size, QColor(0, 80, 0));
      }
      painter.setPen(Qt::black);
      painter.drawRect(x, y, cell_size, cell_size);
    }
  }

  painter.setPen(QColor(255, 215, 0));
  const int hint_y = offset_y + model_->rows() * cell_size + 30;
  painter.drawText(10, hint_y, tr("Q — назад"));

  if (model_->updateMode() == CaveUpdateMode::StepByStep) {
    painter.drawText(10, hint_y + 20, tr("Пробел — следующий шаг"));
  }
}

void CaveWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Q) {
    emit backRequested();
    return;
  }

  if (event->key() == Qt::Key_Space &&
      model_->updateMode() == CaveUpdateMode::StepByStep) {
    nextStep();
    return;
  }

  QWidget::keyPressEvent(event);
}

void CaveWidget::nextStep() {
  model_->updateState();
  update();
}
