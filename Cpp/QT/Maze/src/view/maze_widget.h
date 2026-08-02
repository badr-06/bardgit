#ifndef MAZE_WIDGET_H
#define MAZE_WIDGET_H

#include "../model/maze_model.h"

#include <QWidget>

class MazeWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MazeWidget(MazeModel* model, QWidget* parent = nullptr);

 signals:
  void backRequested();

 protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

 private slots:
  void solveMaze();
  void clearSolution();

 private:
  MazeModel* model_;
};

#endif
