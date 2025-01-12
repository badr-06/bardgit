#include "backend.h"
#include "game.h"

#define NULL_BUTTON 0

int main() 
{
    State_t *state = getCurrentState();
    state->is_playing = 0;
    GameInfo_t game = updateCurrentState();

    userInput(START_BUTTON_SMALL);
    game = updateCurrentState();
    printf("%d\n", state->X);

    userInput(KEY_LEFT);
    game = updateCurrentState();
    printf("%d\n", state->X);

    userInput(TERMINATE_BUTTON_SMALL);
    terminateGame();
}

