#include "../../brick_game/tetris/beckend_tetris.h"
#include "game_cli.h"

/**
 * @brief стартовая функци
 */
int main() {
  func_ncurses();
  init_colors();

  int ch;
  updateCurrentState();
  State_t *state = getCurrentState();

  while (state->game_play) {
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

/**
 * @brief Принимает ввод пользоваетеля и передает в userInput().
 */
void updateCurrentAction(int ch) {

  switch (ch) {
  case START_BUTTON_BIG:
  case START_BUTTON_SMALL:
    userInput(Start);
    break;
  case KEY_LEFT:
    userInput(Left);
    break;
  case KEY_RIGHT:
    userInput(Right);
    break;
  case KEY_DOWN:
    userInput(Down);
    break;
  case TERMINATE_BUTTON_BIG:
  case TERMINATE_BUTTON_SMALL:
    userInput(Terminate);
    break;
  case PAUSE_BUTTON_BIG:
  case PAUSE_BUTTON_SMALL:
    userInput(Pause);
    break;
  case ACCELERATION_BUTTON_BIG:
  case ACCELERATION_BUTTON:
    userInput(Up);
    break;
  case ACTION_BUTTON:
    userInput(Action);
  default:
    break;
  }
}
