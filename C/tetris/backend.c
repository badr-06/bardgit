#include "backend.h"

State_t *getCurrentState() 
{
    static State_t state;
    return &state;

}

GameInfo_t *getCurrentGame() 
{
    static GameInfo_t game;
    return &game;

}

void initialization() 
{
    State_t *state = getCurrentState();

    createFieldBlock();

    state->status = Initial;

}

void createFieldBlock() 
{
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    game->field = (int **)calloc(FIELD_H, sizeof(int **));
    for(int i = 0; i < FIELD_H; i++){
        game->field[i] = (int*)calloc(FIELD_W, sizeof(int**));
    }

    state->block = (int **)calloc(FIGURE_H, sizeof(int **));
    for(int i = 0; i < FIGURE_H; i++){
        state->block[i] = (int*)calloc(FIGURE_W, sizeof(int**));
    }

    game->next = generateFigure();


    state->status = Initial;
    state->Y = 0;
    state->X = 3;
    state->is_playing = 0;
    state->acceleration = false;
    state->game_play = true;
    game->level = 1;
    game->score = 0;
    game->pause = false;
    game->speed = 1000;
    game->high_score = 600;

}

int **createMatrix(int n, int m)
{
    int **matrix;
    matrix = (int **)calloc(n, sizeof(int **));
    for(int i = 0; i < n; i++){
        matrix[i] = (int*)calloc(m, sizeof(int**));
    }

    return matrix;
}

void freeMatrix(int **matrix, int rows)
{
    for(int i = 0; i < rows; ++i){
    free(matrix[i]);
    } 
    free(matrix);

}

int **generateFigure()
{
    State_t *state = getCurrentState();

    state->next_type_Figure = rand() % 7;

    int **matrix = createMatrix(FIGURE_H, FIGURE_W);

    if( state->next_type_Figure == I ) {
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[3][1] = 1;
    } else if ( state->next_type_Figure == J ) {
        matrix[0][2] = 1;
        matrix[1][2] = 1;
        matrix[2][2] = 1;
        matrix[2][1] = 1;
    } else if( state->next_type_Figure == L ) {
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 1;
    } else if ( state->next_type_Figure == O ) {
        matrix[0][1] = 1;
        matrix[0][2] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
    } else if ( state->next_type_Figure == Z ) {
        matrix[0][1] = 1;
        matrix[0][2] = 1;
        matrix[1][2] = 1;
        matrix[1][3] = 1;
    } else if ( state->next_type_Figure == T ) {
        matrix[0][1] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
    } else if ( state->next_type_Figure == S ) {
        matrix[0][2] = 1;
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[1][0] = 1;
    }

    return matrix;
}

void spawnFigure()
{
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    state->type_Figure = state->next_type_Figure;
    state->gradus = 0;
    
    copyMatrix(state->block, game->next, FIGURE_H, FIGURE_W);
    freeMatrix(game->next, FIGURE_H);
    game->next = generateFigure();

    state->milliseconds = currentTime();
    state->status = Moving;

}



GameInfo_t updateCurrentState()
{ 
    State_t *state = getCurrentState();

    GameInfo_t *game_info = getCurrentGame();

    srand(time(0));
    
    if(state->is_playing == 0){
    initialization();
    state->is_playing = 1;
    }

    game();
    
    if(state->status != Gameover) setFigure();

    return *game_info;
    
}

void copyMatrix(int **matrix1, int **matrix2, int n, int m)
{
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j) {
            matrix1[i][j] = 0;
            matrix1[i][j] = matrix2[i][j];
        }
    }
}

void userInput(UserAction_t ch)
{
    if(ch == KEY_LEFT){
        process_button(Left);
    } else if (ch == KEY_RIGHT) {
        process_button(Right);
    } else if (ch == KEY_DOWN) {
        process_button(Down);
    } else if (ch == ACTION_BUTTON){
        process_button(Action);
    } else if (ch == PAUSE_BUTTON_BIG || ch == PAUSE_BUTTON_SMALL){
        process_button(Pause);
    } else if (ch == START_BUTTON_BIG || ch == START_BUTTON_SMALL){
        process_button(Start);
    } else if (ch == TERMINATE_BUTTON_BIG || ch == TERMINATE_BUTTON_SMALL) {
        process_button(Terminate);
    } else if(ch == ACCELERATION_BUTTON || ch == ACCELERATION_BUTTON_BIG){
        process_button(ACCELERATION_BUTTON);
    }
}

void process_button(UserAction_t action_button)
{
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    if(action_button == Start && state->status == Initial){
        state->status = Spawn;
    } else if((action_button == Right || action_button == Left || action_button == Action) && (state->status == Shifting || state->status == Moving)){
        state->action_move = action_button;
    } else if(action_button == Down && state->status != Initial){
        state->status = Shifting;
    } else if(action_button == Terminate){
        state->status = Gameover;
    } else if(action_button == Pause && state->status != Initial){
        char s = getch();
        while(s != 80 && s != 112){
            game->pause = true;
            s = getch();
        }
        game->pause = false;
    } else if(action_button == ACCELERATION_BUTTON && (state->status == Shifting || state->status == Moving)){
        state->acceleration = true;
    }
}

void shiftingBlock()
{
    State_t *state = getCurrentState();

    unsetFigure(); // функция для того чтобы удалить нынешнюю фигуру с поля

    ++state->Y;
    if(checkStatusBlock()){
        state->status = Attaching;
        --state->Y;
    } else if(!state->acceleration) {
    state->milliseconds = currentTime();
    state->status = Moving;
    }
}

bool checkStatusBlock()
{
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            if((state->block[i][j] && (i + state->Y) == FIELD_H)){
                return true;
            }
            else if (state->block[i][j] && game->field[i+state->Y][j+state->X]){
                return true;
            }
            else if ((state->block[i][j] && ((j + state->X >= FIELD_W) || (j + state->X < 0)))){
                    return true;
            
            }
        }
    }
    return false;
}

bool checkoverflow()
{
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            if(game->next[i][j] && game->field[i + state->Y][j + state->X]){
                    return true;
            }
        }
    }
    return false;

}

void attachingBlock() 
{
    State_t *state = getCurrentState();

    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            state->block[i][j] = 0;
        }
    }
    state->Y = 0;
    state->X = 3;

    del_line();

    state->status = Spawn;
    state->acceleration = false;

}

void del_line()
{
    GameInfo_t *game = getCurrentGame();
    
    int index_i;
    int line = 0;
    bool i_flag = true;
    bool check_line = false;
    int sum = 0;
    int **matrix = createMatrix(FIELD_H, FIELD_W);

    for(int i = FIELD_H - 1; i >= 0; --i){
        for(int j = 0; j < FIELD_W; ++j){   
        if(i_flag){
            index_i = i;
        }
            sum += game->field[i][j];
            if(sum == 10){
                check_line = true;
                i_flag = false;
                line++;
            }
        }
        sum = 0;
    }

    if(check_line){

        if(index_i < 19){
         for(int i = FIELD_H - 1; i > index_i; --i){
            for(int j = 0; j < FIELD_W; ++j){
                matrix[i][j] = game->field[i][j];
            }
        }           
        }

        for(int i = index_i; i >= 0; --i){
            for(int j = 0; j < FIELD_W; ++j){
                if(i - line >= 0){
                matrix[i][j] = game->field[i - line][j];
                } else {
                    matrix[i][j] = 0;
                }
            }
        }
        switch (line)
        {
        case 1:
            game->score += 100;
        break; case 2:
            game->score += 300;
        break; case 3:
            game->score += 700;
        break; case 4:
            game->score += 1500;
        default:
            break;
        };

        int temp = game->score / game->high_score;
        
        if(temp >= game->level && temp + game->level + temp < 11){
            game->level += temp;
            game->speed -= temp * 70;
        } else if(game->level + temp > 10){
            game->level = 10;
            game->speed = 300;
        }

       copyMatrix(game->field, matrix, FIELD_H, FIELD_W);
       freeMatrix(matrix, FIELD_H);
    }


}

void unsetFigure()
{
    GameInfo_t *game = getCurrentGame();
    State_t *state = getCurrentState();

    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            if(state->block[i][j] && game->field[i+state->Y][j+state->X]){
                game->field[i+state->Y][j+state->X] = 0;
            }
        }
    }

}

void setFigure()
{   
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    int n = state->Y;
    int m = state->X;
    for(int i = n, i_f = 0; i < FIGURE_H + n; ++i, ++i_f){
        for(int j = m, j_f = 0; j < FIGURE_W + m; ++j, ++j_f){
            if(state->block[i_f][j_f]){
            game->field[i][j] = state->block[i_f][j_f];
            }
        }
    }
}

void moveRightBlock()
{
    State_t *state = getCurrentState();

    state->X++;
    if(checkStatusBlock()){
        state->X--;
    }

}

void moveLeftBlock()
{
    State_t *state = getCurrentState();

    state->X--;
    if(checkStatusBlock()){
        state->X++;
    }
 
}

void rotate()
{
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();
    int x = state->X;
    int y = state->Y;
    int temp = state->gradus;

    int **matrix = createMatrix(FIGURE_H, FIGURE_W);
    bool check_status_block = true;

    if( state->type_Figure == I ){
        if(state->gradus == 0){
            matrix[1][0] = 1;
            matrix[1][1] = 1;
            matrix[1][2] = 1;
            matrix[1][3] = 1;
            state->gradus = 90;
        } else if (state->gradus == 90) {
            matrix[0][1] = 1;
            matrix[1][1] = 1;
            matrix[2][1] = 1;
            matrix[3][1] = 1;
            state->gradus = 0;    
        } 
    } else if ( state->type_Figure == J ){
        if(state->gradus == 0){
             matrix[1][3] = 1;
             matrix[1][2] = 1;
             matrix[1][1] = 1;
             matrix[0][1] = 1;
             state->gradus = 90;
        } else if(state->gradus == 90){
             matrix[2][2] = 1;
             matrix[1][2] = 1;
             matrix[0][2] = 1;
             matrix[0][3] = 1;
             state->gradus = 180;
        } else if(state->gradus == 180){
             matrix[1][1] = 1;
             matrix[1][2] = 1;
             matrix[1][3] = 1;
             matrix[2][3] = 1;
             state->gradus = 270;
        } else {
             matrix[0][2] = 1;
             matrix[1][2] = 1;
             matrix[2][2] = 1;
             matrix[2][1] = 1;
             state->gradus = 0;
        }
    } else if(state->type_Figure == L ){
        if(state->gradus == 0) {
             matrix[1][2] = 1;
             matrix[1][1] = 1;
             matrix[1][0] = 1;
             matrix[2][0] = 1;
             state->gradus = 90;
        } else if(state->gradus == 90){
             matrix[2][1] = 1;
             matrix[1][1] = 1;
             matrix[0][1] = 1;
             matrix[0][0] = 1;
             state->gradus = 180;
        } else if(state->gradus == 180){
             matrix[1][0] = 1;
             matrix[1][1] = 1;
             matrix[1][2] = 1;
             matrix[0][2] = 1;
             state->gradus = 270;
        } else {
             matrix[0][1] = 1;
             matrix[1][1] = 1;
             matrix[2][1] = 1;
             matrix[2][2] = 1;
             state->gradus = 0;
        }
    }  else if( state->type_Figure == Z ){
        if(state->gradus == 0){
            matrix[0][2] = 1;
            matrix[1][2] = 1;
            matrix[1][1] = 1;
            matrix[2][1] = 1;
            state->gradus = 90;
        } else {
            matrix[0][1] = 1;
            matrix[0][2] = 1;
            matrix[1][2] = 1;
            matrix[1][3] = 1;
            state->gradus = 0;
        }        
    }  else if( state->type_Figure == T){
        if(state->gradus == 0) {
             matrix[0][1] = 1;
             matrix[1][1] = 1;
             matrix[2][1] = 1;
             matrix[1][2] = 1;
            state->gradus = 90;
        } else if(state->gradus == 90){
             matrix[1][0] = 1;
             matrix[1][1] = 1;
             matrix[1][2] = 1;
             matrix[2][1] = 1;
            state->gradus = 180;
        } else if( state->gradus == 180 ){
             matrix[0][1] = 1;
             matrix[1][1] = 1;
             matrix[2][1] = 1;
             matrix[1][0] = 1;
            state->gradus = 270;
        } else {
             matrix[1][0] = 1;
             matrix[1][1] = 1;
             matrix[1][2] = 1;
             matrix[0][1] = 1;
            state->gradus = 0;
        }
    } else if( state->type_Figure == S ){
        if(state->gradus == 0){
            matrix[0][1] = 1;
            matrix[1][1] = 1;
            matrix[1][2] = 1;
            matrix[2][2] = 1;
            state->gradus = 90;
        } else {
            matrix[0][2] = 1;
            matrix[0][1] = 1;
            matrix[1][1] = 1;
            matrix[1][0] = 1;
            state->gradus = 0;
        }        
    } 

    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            if(matrix[i][j] == 1 && (i + y >= FIELD_H || i + y < 0 || j + x >= FIELD_W || j + x < 0 || game->field[i + y][j + x] == 1 )) check_status_block = false;
        }
    }

    if(check_status_block && state->type_Figure != O){
        cleanMatrix(state->block);
        copyMatrix(state->block, matrix, FIGURE_H, FIGURE_W);
        freeMatrix(matrix, FIGURE_H);
    } else {
        freeMatrix(matrix, FIGURE_H);
        state->gradus = temp;;
    }

}

void cleanMatrix(int **matrix)
{
    for(int i = 0; i < FIGURE_H; ++i){
        for(int j = 0; j < FIGURE_W; ++j){
            matrix[i][j] = 0;
        }
    }

}

void movingBlock()
{
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    unsetFigure();

    if(state->action_move == Right){
        moveRightBlock();
        state->action_move = 0;
    } else if(state->action_move == Left){
        moveLeftBlock();
        state->action_move = 0;
    } else if(state->action_move == Action){
        rotate();
        state->action_move = 0;
    }

    if(state->acceleration){
        state->milliseconds = 0;
    }

    if((currentTime() - state->milliseconds >= game->speed)){
        state->status = Shifting;
    }

}

long currentTime()
{
    GameInfo_t *game = getCurrentGame();
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) + game->speed;

}

void game()
{
        State_t *state = getCurrentState();

        if(state->status == Initial){
            // updateCurrentAction();
        } else if (state->status == Spawn) {
            if(!checkoverflow()){
            spawnFigure();
            } else { 
            state->status = Gameover;
            }
        } else if (state->status == Shifting) {
            shiftingBlock();
        } else if (state->status == Moving) {
            movingBlock();
        } else if (state->status == Attaching) {
            attachingBlock();
        } else if (state->status == Gameover) {
            terminateGame();     
        }

}

void terminateGame()
{   
    State_t *state = getCurrentState();
    GameInfo_t *game = getCurrentGame();

    freeMatrix(state->block, FIGURE_H);
    freeMatrix(game->field, FIELD_H);
    freeMatrix(game->next, FIGURE_H);

    state->game_play = false;

}