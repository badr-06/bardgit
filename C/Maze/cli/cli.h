#ifndef CLI_H
#define CLI_H

#include <locale.h>
#include <ncurses.h>

#include "../lib/lib.h"

void init_ncurses();
void init_colors();
void draw_selected(int selected, int n, char *items[]);
int draw_maze(Date_Maze *dm);
int draw_cave(Date_Cave *cv);
void draw_for_cin(char *str);

#endif