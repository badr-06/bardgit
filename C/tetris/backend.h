#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>

#define PAUSE_BUTTON_SMALL 112
#define PAUSE_BUTTON_BIG 80
#define START_BUTTON_SMALL 115
#define START_BUTTON_BIG 83
#define ACTION_BUTTON 32
#define TERMINATE_BUTTON_SMALL 113
#define TERMINATE_BUTTON_BIG 81
#define ACCELERATION_BUTTON 122
#define ACCELERATION_BUTTON_BIG 90

#define FIELD_H 20
#define FIELD_W 10

#define FIGURE_H 4
#define FIGURE_W 4

#define ACCELERATION_BUTTON 122

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef enum { I, O, J, L, Z, T, S } Block_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

typedef struct {
    int status;
    int **field;
    int **block;
    int **nextBlock;
    int Y;
    int X;
    int is_playing;
    int action_move;
    long milliseconds;
    int type_Figure;
    int next_type_Figure;
    int gradus;
    bool acceleration; 
    bool game_play;
} State_t;

typedef enum { Initial, Spawn, Moving, Attaching, Shifting, Move_block, Gameover } Status_t;

void userInput(UserAction_t);

GameInfo_t updateCurrentState();

State_t *getCurrentState();
GameInfo_t *getCurrentGame();
void initialization();
void createFieldBlock();
int **generateFigure();
int **createMatrix(int n, int m);
void freeMatrix(int **matrix, int rows);
void spawnFigure();
void copyMatrix(int **matrix1, int **matrix2, int n, int m);
void shiftingBlock();
bool checkStatusBlock();
bool checkoverflow();
void moveRightBlock();
void moveLeftBlock();
void rotate();
void attachingBlock();
void terminateGame();
void unsetFigure();
void setFigure();
void game();
void movingBlock();
long currentTime();
void cleanMatrix(int **matrix);
void del_line();
void process_button(UserAction_t action_button);


#endif