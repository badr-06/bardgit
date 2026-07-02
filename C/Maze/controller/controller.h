#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../cli/cli.h"
#include "../model/cave.h"
#include "../model/maze.h"

#define NUMBER_OF_ITEMS 5
#define NUMBER_OF_EXAMPLES 4
#define NUMBER_OF_MODES 2

enum { LoadMaze, LoadCave, MazeGeneration, CaveGeneration, Exit };

void draw_menu();
bool selec(int selected);
void select_example_maze();
void loading_maze(int selected);
void select_example_cave();
void loading_cave(int selected);
void select_method_update_cave();
void function_call_for_update();
void automatic_update();
void Step_By_Step_update();
void Generation_maze();
void Generation_cave();
void run_maze();
int enter_limits();

#endif