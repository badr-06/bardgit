#pragma once
#include <QApplication>
#include <QEvent>
#include <QLabel>
#include <QPainter>
#include <QtWidgets>

/**
 * @brief Класс для виджета.
 */
namespace s21 {
class GameWidget : public QWidget {
  Q_OBJECT
public:
  GameWidget(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *);
  void printcontrols(QPainter *qp);
  void printgame(QPainter *qp);
  void keyPressEvent(QKeyEvent *ke);
  void printInformationGame(QPainter *qp);
  void updateCurent();
  void terminateGame(QPainter *qp);

protected:
private:
  QLabel *infolabel;
  QLabel *nextFigurelabel;
  QLabel *controlslabel;
};
} // namespace s21