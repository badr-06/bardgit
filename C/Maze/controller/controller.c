#include "controller.h"

void draw_menu(void) {
  init_ncurses();
  init_colors();

  bool flag = true;
  int indicates = 0;
  char *items[] = {"Load maze", "Load cave", "Maze Generation",
                   "Cave Generation", "Exit"};
  while (flag) {
    draw_selected(indicates, NUMBER_OF_ITEMS, items);

    int ch = getch();

    switch (ch) {
      case KEY_UP:
        indicates = (indicates + (NUMBER_OF_ITEMS - 1)) % NUMBER_OF_ITEMS;
        break;

      case KEY_DOWN:
        indicates = (indicates + 1) % NUMBER_OF_ITEMS;
        break;

      case '\n':
        flag = selec(indicates);
        break;
    }
  }

  endwin();
}

void select_example_maze() {
  bool flag = true;
  int indicates = 0;
  char *items[] = {"data_maze_1.txt", "data_maze_2.txt", "data_maze_3.txt",
                   "Return"};
  while (flag) {
    draw_selected(indicates, NUMBER_OF_EXAMPLES, items);

    int ch = getch();

    switch (ch) {
      case KEY_UP:
        indicates = (indicates + (NUMBER_OF_EXAMPLES - 1)) % NUMBER_OF_EXAMPLES;
        break;

      case KEY_DOWN:
        indicates = (indicates + 1) % NUMBER_OF_EXAMPLES;
        break;

      case '\n':
        if (indicates == 3)
          flag = false;
        else
          loading_maze(indicates);
        break;
    }
  }
}

void loading_maze(int selected) {
  char *filename = NULL;
  switch (selected) {
    case 0:
      filename = "files_maze/date_maze_1.txt";
      break;
    case 1:
      filename = "files_maze/date_maze_2.txt";
      break;
    case 2:
      filename = "files_maze/date_maze_3.txt";
      break;
    default:
      break;
  }

  if (load_maze(filename)) return;
  run_maze();
}

void select_example_cave() {
  bool flag = true;
  int indicates = 0;
  char *items[] = {"data_cave_1.txt", "data_cave_2.txt", "data_cave_3.txt",
                   "Return"};
  while (flag) {
    draw_selected(indicates, NUMBER_OF_EXAMPLES, items);

    int ch = getch();

    switch (ch) {
      case KEY_UP:
        indicates = (indicates + (NUMBER_OF_EXAMPLES - 1)) % NUMBER_OF_EXAMPLES;
        break;

      case KEY_DOWN:
        indicates = (indicates + 1) % NUMBER_OF_EXAMPLES;
        break;

      case '\n':
        if (indicates == 3)
          flag = false;
        else
          loading_cave(indicates);
        break;
    }
  }
}

void loading_cave(int selected) {
  char *filename = NULL;
  switch (selected) {
    case 0:
      filename = "files_cave/date_cave_1.txt";
      break;
    case 1:
      filename = "files_cave/date_cave_2.txt";
      break;
    case 2:
      filename = "files_cave/date_cave_3.txt";
      break;
    default:
      break;
  }

  load_cave(filename);
  enter_limits();
  select_method_update_cave();
}

void select_method_update_cave() {
  Date_Cave *cv = get_date_cave();

  bool flag = true;
  int indicates = 0;
  char *items[] = {"automatic", "Step by step"};
  while (flag) {
    draw_selected(indicates, NUMBER_OF_MODES, items);

    int ch = getch();

    switch (ch) {
      case KEY_UP:
        indicates = (indicates + (NUMBER_OF_MODES - 1)) % NUMBER_OF_MODES;
        break;

      case KEY_DOWN:
        indicates = (indicates + 1) % NUMBER_OF_MODES;
        break;

      case '\n':
        cv->method_update = indicates;
        flag = false;
        break;
    }
  }

  function_call_for_update();
}

void function_call_for_update() {
  Date_Cave *cv = get_date_cave();

  if (cv->method_update == Automatic) {
    automatic_update();
  } else if (cv->method_update == StepByStep) {
    Step_By_Step_update();
  }
}

void automatic_update() {
  Date_Cave *cv = get_date_cave();

  draw_for_cin("Enter the time delay (in milliseconds 0-1000): ");
  if (scanw("%d", &cv->time_delay) != 1) return;
  noecho();
  while (1) {
    timeout(cv->time_delay);
    int c = draw_cave(cv);
    if (c == 'q') {
      clear();
      break;
    }
    update_state_cave();
  }
  echo();
  timeout(-1);
}

void Step_By_Step_update() {
  Date_Cave *cv = get_date_cave();
  noecho();
  while (1) {
    int c = draw_cave(cv);
    while (c != 'q' && c != ' ') {
      c = getch();
    }
    if (c == 'q') {
      clear();
      break;
    }
    update_state_cave();
  }
  echo();
}

void Generation_maze() {
  Date_Maze *dm = get_date_maze();
  draw_for_cin("Enter the number of rows and columns for the maze: ");

  if (scanw("%d %d", &dm->rows, &dm->columns) == 2) {
    maze_generation();
    run_maze();
    my_write();
  }
}

void Generation_cave() {
  Date_Cave *cv = get_date_cave();
  draw_for_cin("Enter the number of rows and columns for the cave: ");

  if (scanw("%d %d", &cv->rows, &cv->columns) == 2) {
    cave_generation();
    enter_limits();
    select_method_update_cave();
  }
}

int enter_limits() {
  Date_Cave *cv = get_date_cave();

  int error = 0;

  draw_for_cin("Enter the birth limit (0-7): ");
  if (scanw("%d", &cv->birth_limit) != 1 || cv->birth_limit > 7 ||
      cv->birth_limit < 0)
    error = 1;
  draw_for_cin("Enter the death limit (0-7): ");
  if (scanw("%d", &cv->death_limit) != 1 || cv->death_limit > 7 ||
      cv->death_limit < 0)
    error = 1;

  return error;
}

void run_maze() {
  Date_Maze *dm = get_date_maze();

  while (1) {
    int c = draw_maze(dm);
    if (c == 'q') {
      clear();
      break;
    } else if (c == 'f') {
      int x1, y1, x2, y2, error = 0;
      draw_for_cin("Enter the coordinates of the start of the route ");
      if (scanw("%d %d", &y1, &x1) != 2) error = 1;
      draw_for_cin("Enter the coordinates of the end point of the route ");
      if (scanw("%d %d", &y2, &x2) != 2) error = 1;

      if (y1 < 1 || y2 > dm->rows || x1 < 1 || x2 > dm->columns) error = 1;

      if (!error) solving_the_maze(y1 - 1, x1 - 1, y2 - 1, x2 - 1);

    } else if (c == 'g') {
      clear_solving_the_maze();
    }
  }
}

bool selec(int selected) {
  bool flag = true;
  switch (selected) {
    case LoadMaze:
      select_example_maze();
      break;
    case LoadCave:
      select_example_cave();
      break;
    case MazeGeneration:
      Generation_maze();
      break;
    case CaveGeneration:
      Generation_cave();
      break;
    case Exit:
      flag = false;
      break;
    default:
      break;
  }

  return flag;
}
