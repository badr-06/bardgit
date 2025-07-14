#ifndef FRONTEND_H
#define FRONTEND_H

#define GAME_FIELD_N (FIELD_H + 2) /// < размеры поля в высоту
#define GAME_FIELD_M (FIELD_W * 2 + 2) /// < размеры поля в ширину
#define CONTROLS_M 32 /// < дистанция установки между окнами

#include "../../brick_game/lib.h"
#include <ncurses.h>

void init_colors();
void func_ncurses();
WINDOW *print_game_field(GameInfo_t game);
WINDOW *print_controls_game();
WINDOW *print_info_game(GameInfo_t game);
WINDOW *terminate_game_field(GameInfo_t game);
void print_game(GameInfo_t game);
void print_terminate_game(GameInfo_t game);

#endif