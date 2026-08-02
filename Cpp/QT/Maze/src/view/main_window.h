#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "../model/cave_model.h"
#include "../model/maze_model.h"
#include "cave_widget.h"
#include "maze_widget.h"

#include <QMainWindow>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);

 private slots:
  void showMainMenu();
  void loadMaze();
  void loadCave();
  void generateMaze();
  void generateCave();
  void openMazeView();
  void openCaveView();
  void showError(const QString& message);

 private:
  enum Page { MenuPage = 0, MazePage = 1, CavePage = 2 };

  MazeModel maze_model_;
  CaveModel cave_model_;
  QStackedWidget* stack_;
  MazeWidget* maze_widget_;
  CaveWidget* cave_widget_;

  bool askDimensions(int& rows, int& columns, const QString& title);
  bool askCaveLimits();
  bool askCaveUpdateMode();
  QString projectPath(const QString& relative) const;
};

#endif
