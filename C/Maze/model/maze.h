#ifndef MAZE_H
#define MAZE_H

#include "model.h"

typedef struct {
  int y;
  int x;
} Point;

Date_Maze* get_date_maze();
void init_date_maze();
int load_maze(char* filename);
void print_date_maze();
void maze_generation();
void merge_sets(int* matrix, int a, int b, int columns);
void check_lower_bounds(int i, int r, int c, int matrix[r][c]);
void my_write();
void solving_the_maze(int y1, int x1, int y2, int x2);
int dfs(int rows, int columns, bool visit[rows][columns], Point current,
        Point end, Point* path, int* path_count);
void clear_solving_the_maze();
// void my_write_set(int n, int matrix[n]);

#endif  // HEADER_H