#include "main_window.h"

#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  setWindowTitle(tr("Maze & Cave"));
  resize(800, 600);

  stack_ = new QStackedWidget(this);
  setCentralWidget(stack_);

  auto* menu_page = new QWidget(this);
  auto* menu_layout = new QVBoxLayout(menu_page);

  auto* title = new QLabel(tr("Maze & Cave Generator"), menu_page);
  title->setAlignment(Qt::AlignCenter);
  QFont title_font = title->font();
  title_font.setPointSize(16);
  title_font.setBold(true);
  title->setFont(title_font);
  menu_layout->addWidget(title);

  auto* menu_list = new QListWidget(menu_page);
  menu_list->addItems({tr("Load maze"), tr("Load cave"), tr("Maze Generation"),
                       tr("Cave Generation"), tr("Exit")});
  menu_list->setCurrentRow(0);
  menu_layout->addWidget(menu_list);

  auto* select_btn = new QPushButton(tr("Select"), menu_page);
  menu_layout->addWidget(select_btn);
  select_btn->setDefault(true);

  connect(menu_list, &QListWidget::itemActivated, select_btn, &QPushButton::click);

  stack_->addWidget(menu_page);

  maze_widget_ = new MazeWidget(&maze_model_, this);
  cave_widget_ = new CaveWidget(&cave_model_, this);
  stack_->addWidget(maze_widget_);
  stack_->addWidget(cave_widget_);

  connect(select_btn, &QPushButton::clicked, this, [this, menu_list]() {
    switch (menu_list->currentRow()) {
      case 0:
        loadMaze();
        break;
      case 1:
        loadCave();
        break;
      case 2:
        generateMaze();
        break;
      case 3:
        generateCave();
        break;
      default:
        QApplication::quit();
        break;
    }
  });

  connect(menu_list, &QListWidget::itemDoubleClicked, select_btn,
          &QPushButton::click);

  connect(maze_widget_, &MazeWidget::backRequested, this, &MainWindow::showMainMenu);
  connect(cave_widget_, &CaveWidget::backRequested, this, &MainWindow::showMainMenu);
}

void MainWindow::showMainMenu() {
  stack_->setCurrentIndex(MenuPage);
}

QString MainWindow::projectPath(const QString& relative) const {
  return QDir(PROJECT_ROOT).filePath(relative);
}

bool MainWindow::askDimensions(int& rows, int& columns, const QString& title) {
  bool ok = false;

  rows = QInputDialog::getInt(this, title, tr("Количество строк (1-%1):")
                                           .arg(MazeModel::kMaxSize),
                              10, 1, MazeModel::kMaxSize, 1, &ok);
  if (!ok) return false;

  columns = QInputDialog::getInt(this, title, tr("Количество столбцов (1-%1):")
                                                 .arg(MazeModel::kMaxSize),
                                 10, 1, MazeModel::kMaxSize, 1, &ok);
  return ok;
}

bool MainWindow::askCaveLimits() {
  bool ok = false;

  const int birth = QInputDialog::getInt(
      this, tr("Предел рождения"), tr("Birth limit (0-7):"), 4, 0, 7, 1, &ok);
  if (!ok) return false;

  const int death = QInputDialog::getInt(
      this, tr("Предел смерти"), tr("Death limit (0-7):"), 4, 0, 7, 1, &ok);
  if (!ok) return false;

  cave_model_.setBirthLimit(birth);
  cave_model_.setDeathLimit(death);
  return true;
}

bool MainWindow::askCaveUpdateMode() {
  const QStringList modes = {tr("Automatic"), tr("Step by step")};
  bool ok = false;
  const QString choice = QInputDialog::getItem(
      this, tr("Режим обновления"), tr("Выберите режим:"), modes, 0, false, &ok);
  if (!ok) return false;

  if (choice == modes[0]) {
    cave_model_.setUpdateMode(CaveUpdateMode::Automatic);
    const int delay = QInputDialog::getInt(
        this, tr("Задержка"), tr("Time delay (ms, 0-1000):"), 100, 0, 1000, 10,
        &ok);
    if (!ok) return false;
    cave_model_.setTimeDelay(delay);
  } else {
    cave_model_.setUpdateMode(CaveUpdateMode::StepByStep);
  }

  return true;
}

void MainWindow::loadMaze() {
  QString path = QFileDialog::getOpenFileName(
      this, tr("Load maze"), projectPath("files_maze"),
      tr("Text files (*.txt);;All files (*)"));

  if (path.isEmpty()) {
    const QStringList items = {tr("data_maze_1.txt"), tr("data_maze_2.txt")};
    bool ok = false;
    const QString selected = QInputDialog::getItem(
        this, tr("Load maze"), tr("Выберите файл:"), items, 0, false, &ok);
    if (!ok) return;

    path = projectPath(QString("files_maze/%1").arg(selected));
  }

  if (!maze_model_.loadFromFile(path)) {
    showError(tr("Не удалось загрузить лабиринт из файла."));
    return;
  }

  openMazeView();
}

void MainWindow::loadCave() {
  QString path = QFileDialog::getOpenFileName(
      this, tr("Load cave"), projectPath("files_cave"),
      tr("Text files (*.txt);;All files (*)"));

  if (path.isEmpty()) {
    const QStringList items = {tr("data_cave_1.txt"), tr("data_cave_2.txt")};
    bool ok = false;
    const QString selected = QInputDialog::getItem(
        this, tr("Load cave"), tr("Выберите файл:"), items, 0, false, &ok);
    if (!ok) return;

    path = projectPath(QString("files_cave/%1").arg(selected));
  }

  if (!cave_model_.loadFromFile(path)) {
    showError(tr("Не удалось загрузить пещеру из файла."));
    return;
  }

  if (!askCaveLimits()) return;
  if (!askCaveUpdateMode()) return;
  openCaveView();
}

void MainWindow::generateMaze() {
  int rows = 0;
  int columns = 0;
  if (!askDimensions(rows, columns, tr("Генерация лабиринта"))) {
    return;
  }

  maze_model_.generate(rows, columns);
  maze_model_.saveToFile(projectPath("files_maze/out_maze.txt"));
  openMazeView();
}

void MainWindow::generateCave() {
  int rows = 0;
  int columns = 0;
  if (!askDimensions(rows, columns, tr("Генерация пещеры"))) {
    return;
  }

  cave_model_.generate(rows, columns);
  if (!askCaveLimits()) return;
  if (!askCaveUpdateMode()) return;
  openCaveView();
}

void MainWindow::openMazeView() {
  stack_->setCurrentIndex(MazePage);
  maze_widget_->setFocus();
  maze_widget_->update();
}

void MainWindow::openCaveView() {
  stack_->setCurrentIndex(CavePage);
  cave_widget_->setFocus();
  cave_widget_->update();
}

void MainWindow::showError(const QString& message) {
  QMessageBox::warning(this, tr("Ошибка"), message);
}
