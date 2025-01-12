#ifndef FRONTEND_H
#define FRONTEND_H

#define GAME_FIELD_N (FIELD_H + 2)
#define GAME_FIELD_M (FIELD_W * 2 + 2)
#define START_MENU_N 8
#define START_MENU_M 24
#define PAUSE_MENU_N 5
#define PAUSE_MENU_M 24
#define FINISH_GAME_N 10
#define FINISH_GAME_M 24
#define GAME_INFO_M 25
#define CONTROLS_M 32

#define TOP_MARGIN 0
#define LEFT_MARGIN 0

#include "backend.h" 

void print_game(GameInfo_t game);
void init_colors();
void func_ncurses();
WINDOW *print_game_field(GameInfo_t game);
WINDOW *print_controls_game(GameInfo_t game);
WINDOW *print_info_game(GameInfo_t game);

#endif