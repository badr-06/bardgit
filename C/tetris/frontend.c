#include "frontend.h"

void func_ncurses() {
    initscr(); // инициализирует работу с экраном и подготавливает терминал для использования функций ncurses
    cbreak(); // после ввода не нужно нажимать Enter
    noecho(); // не показывает вводимые символы
    keypad(stdscr, TRUE); // включает режим работы с клавишами для заданного окна
    curs_set(0);
   
}

void init_colors() {
        start_color(); // Инициализация цветовой системы
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);     // Цвет для фигур
        init_pair(2, COLOR_WHITE, COLOR_BLACK);   // Цвет для игрового поля
        init_pair(3, COLOR_BLACK, COLOR_BLACK);  // Другой цвет для фигур
        // init_pair(4, )
}

void print_game(GameInfo_t game)
{      
  WINDOW *game_window = NULL;
  WINDOW *game_controls_window = NULL;
  WINDOW *game_info_window = NULL;

    


    game_controls_window = print_controls_game(game);
    wrefresh(game_controls_window);

    game_window = print_game_field(game);
    wrefresh(game_window);

    game_info_window = print_info_game(game);
    wrefresh(game_info_window);

    delwin(game_controls_window);
    delwin(game_window);
    delwin(game_info_window);

}

WINDOW *print_game_field(GameInfo_t gi) {
  WINDOW *game_window =
      newwin(GAME_FIELD_N, GAME_FIELD_M, 0, CONTROLS_M);

  box(game_window, 0, 0);
//   keypad(game_window, 1);
//   nodelay(game_window, 1);

  mvwprintw(game_window, 0, (GAME_FIELD_M - 6) / 2, "Tetris");

  for (int i = 0; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      if (gi.field[i][j] == 1) {
        wattron(game_window, COLOR_PAIR(1));
        mvwprintw(game_window, i+1, 2*j+1, "[]");
        wattroff(game_window, COLOR_PAIR(1));
      } else {
        wattron(game_window, COLOR_PAIR(2));
        mvwprintw(game_window, i+1, 2*j+1, " .");
        wattroff(game_window, COLOR_PAIR(2));
      }
    }
  }

  return game_window;
}

WINDOW *print_controls_game(GameInfo_t game)
{
    WINDOW *game_controls_window = newwin(GAME_FIELD_N, GAME_FIELD_M + FIELD_W, 0, 0);

    box(game_controls_window, 0, 0);


    mvwprintw(game_controls_window, 0, GAME_FIELD_M / 2, "Controls");

    mvwprintw(game_controls_window, 4, (GAME_FIELD_M - 16) / 2, "start the game: s, S");
    mvwprintw(game_controls_window, 6, (GAME_FIELD_M - 16) / 2, "Pause: p, P");
    mvwprintw(game_controls_window, 8, (GAME_FIELD_M - 16) / 2, "Left: left arrow");
    mvwprintw(game_controls_window, 10, (GAME_FIELD_M - 16) / 2, "Right: right arrow");
    mvwprintw(game_controls_window, 12, (GAME_FIELD_M - 16) / 2, "Rotate: space");
    mvwprintw(game_controls_window, 14, (GAME_FIELD_M - 16) / 2, "Down: down arrow");
    mvwprintw(game_controls_window, 16, (GAME_FIELD_M - 16) / 2, "Quit: q, Q");


    return game_controls_window;
}


WINDOW *print_info_game(GameInfo_t game)
{
  WINDOW *game_info_window = newwin(GAME_FIELD_N, GAME_FIELD_M, 0, CONTROLS_M + GAME_FIELD_M);

  box(game_info_window, 0, 0);

  mvwprintw(game_info_window, 0, (GAME_FIELD_M - 9)/2,  "info game");

  mvwprintw(game_info_window, 2, 3, "next figure");

  for(int i = 0; i < FIGURE_H; ++i){
    for(int j = 0; j < FIGURE_W; ++j){
      if(game.next[i][j] == 1){
      wattron(game_info_window, COLOR_PAIR(1));
      mvwprintw(game_info_window, i + 4, 2*j + 1, "[]");
      wattroff(game_info_window, COLOR_PAIR(1));
      }
    }
  }

  mvwprintw(game_info_window, 8, 3, "High score  %d", game.high_score);
  mvwprintw(game_info_window, 10, 3, "score  %d", game.score);
  mvwprintw(game_info_window, 12, 3, "level  %d", game.level);
  mvwprintw(game_info_window, 14, 3, "speed  %d", game.speed);

  return game_info_window;
}