#ifndef LIB_H
#define LIB_H

#define MAX_RC 50

enum {Automatic, StepByStep};

typedef struct
{
    int rows;
    int columns;
    int matrix1[MAX_RC][MAX_RC];
    int matrix2[MAX_RC][MAX_RC];
    int matrix3[MAX_RC][MAX_RC];
}Date_Maze;

typedef struct
{
    int rows;
    int columns;
    int matrix[MAX_RC][MAX_RC];
    int birth_limit;
    int death_limit;
    int time_delay;
    int method_update;
}Date_Cave;

#endif