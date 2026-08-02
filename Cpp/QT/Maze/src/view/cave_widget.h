#ifndef CAVE_WIDGET_H
#define CAVE_WIDGET_H

#include "../model/cave_model.h"

#include <QTimer>
#include <QWidget>

class CaveWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CaveWidget(CaveModel* model, QWidget* parent = nullptr);

 signals:
  void backRequested();

 protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void showEvent(QShowEvent* event) override;
  void hideEvent(QHideEvent* event) override;

 private slots:
  void nextStep();

 private:
  CaveModel* model_;
  QTimer timer_;
};

#endif
