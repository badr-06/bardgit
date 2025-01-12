#include "backend.h"
#include "frontend.h"
#include "game.h"



int main() 
{
    func_ncurses();
    init_colors();

    // initialization();
    // print_game(updateCurrentState());
    int ch;
    updateCurrentState();
    State_t *state = getCurrentState();

    while(state->game_play)
    {

        GameInfo_t *game = getCurrentGame();
        timeout(1);
        ch = getch();
        updateCurrentAction(ch);
        print_game(*game);
        updateCurrentState();
        refresh();

    }

    endwin();
    return 0;

}   


void updateCurrentAction(int ch)
{   

    userInput(ch);

}