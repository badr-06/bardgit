#include "cli.h"

void init_ncurses() {
  setlocale(LC_ALL, "");
  initscr();  // инициализирует работу с экраном и подготавливает терминал для
              // использования функций ncurses
  // cbreak(); // после ввода не нужно нажимать Enter
  echo();  // не показывает вводимые символы
  keypad(stdscr, TRUE);  // включает режим работы с клавишами для заданного окна
  curs_set(0);
}

void init_colors() {
  start_color();  // Инициализация цветовой системы
  // use_default_colors();
  // init_pair(1, COLOR_YELLOW, COLOR_BLACK);     // Цвет для фигур
  init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Цвет для игрового поля
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // Другой цвет для фигу
  init_pair(4, COLOR_BLACK, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

int draw_maze(Date_Maze *dm) {
  clear();

  wbkgd(stdscr, COLOR_PAIR(2));

  int h = dm->rows + 1;

  int y = 2;
  int x = 4;

  // mvprintw(y-1, x, "%d ", 1);
  mvaddch(y, x++, '+');
  for (int j = 0; j < dm->columns; j++) {
    mvprintw(y - 1, x, "%d", j + 1);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, '+');
  }

  for (int i = 0; i < dm->rows; i++) {
    y++;
    x = 4;
    mvprintw(y, x - 2, "%d", i + 1);
    mvaddch(y, x++, ACS_VLINE);

    for (int j = 0; j < dm->columns; j++) {
      if (dm->matrix3[i][j]) {
        mvaddch(y, x++, ' ');
        attron(COLOR_PAIR(3));
        mvaddch(y, x++, ACS_DIAMOND);
        attroff(COLOR_PAIR(3));
        mvaddch(y, x++, ' ');
      } else {
        mvaddch(y, x++, ' ');
        mvaddch(y, x++, ' ');
        mvaddch(y, x++, ' ');
      }

      if (dm->matrix1[i][j])
        mvaddch(y, x++, ACS_VLINE);
      else if (j == dm->columns - 1)
        mvaddch(y, x++, ACS_VLINE);
      else
        mvaddch(y, x++, ' ');
    }

    y++;
    x = 4;
    mvaddch(y, x++, '+');

    for (int j = 0; j < dm->columns; j++) {
      if (dm->matrix2[i][j]) {
        mvaddch(y, x++, ACS_HLINE);
        mvaddch(y, x++, ACS_HLINE);
        mvaddch(y, x++, ACS_HLINE);
      } else if (i == dm->rows - 1) {
        mvaddch(y, x++, ACS_HLINE);
        mvaddch(y, x++, ACS_HLINE);
        mvaddch(y, x++, ACS_HLINE);
      } else {
        mvaddch(y, x++, ' ');
        mvaddch(y, x++, ' ');
        mvaddch(y, x++, ' ');
      }
      mvaddch(y, x++, '+');
    }
  }

  attron(COLOR_PAIR(3) | A_UNDERLINE);
  mvprintw(h * 2 + 3, 2, "Enter the q key to return");
  mvprintw(h * 2 + 6, 2, "Enter the f key to solving the maze");
  mvprintw(h * 2 + 9, 2, "Enter G to clear the maze solution");
  attroff(COLOR_PAIR(3) | A_UNDERLINE);

  refresh();
  // wrefresh(win);

  int c = getch();

  return c;
}

int draw_cave(Date_Cave *cv) {
  clear();

  int h = cv->rows;
  int w = cv->columns;

  wbkgd(stdscr, COLOR_PAIR(2));

  for (int i = 2; i < h + 2; ++i) {
    for (int j = 2; j < w + 2; ++j) {
      if (cv->matrix[i - 2][j - 2]) {
        attron(COLOR_PAIR(3));
        mvaddch(i, j * 2, ACS_CKBOARD);
        mvaddch(i, j * 2 + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(3));
      } else {
        mvaddch(i, j * 2, ' ');
        mvaddch(i, j * 2 + 1, ' ');
      }
    }
  }

  box(stdscr, 0, 0);

  attron(COLOR_PAIR(3) | A_UNDERLINE);
  mvaddstr(h + 3, 2, "Press the q key to return");
  if (cv->method_update == StepByStep)
    mvaddstr(h + 6, 2, "Press the Space key for the next step");
  attroff(COLOR_PAIR(3) | A_UNDERLINE);

  refresh();

  int c = getch();

  return c;
}

void draw_for_cin(char *str) {
  clear();

  wbkgd(stdscr, COLOR_PAIR(5));
  mvprintw(2, 3, "%s", str);

  refresh();
}

void draw_selected(int indicates, int n, char *items[]) {
  clear();

  for (int i = 0; i < n; ++i) {
    if (i == indicates) attron(COLOR_PAIR(3) | A_BLINK);

    mvprintw(i * 2 + 2, 3, "%s", items[i]);
    attroff(COLOR_PAIR(3) | A_BLINK);
  }

  refresh();
}
