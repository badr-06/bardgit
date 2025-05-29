#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <stddef.h>


class Game {
 private:
    std::vector<std::vector<int>> field;
    SDL_Window *window;
    SDL_Renderer *render;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int Cell_size;
    int Grid_size;
    int speed;
    bool start;
    bool pause;

 public:
    Game(int cell_s = 30, int grid_s = 20, int speed_mls = 500) : window(nullptr), render(nullptr), SCREEN_WIDTH(cell_s * grid_s), 
    SCREEN_HEIGHT(cell_s * grid_s), Cell_size(cell_s), Grid_size(grid_s), speed(speed_mls), 
    start(false), pause(false) { 
        field.resize(Grid_size, std::vector<int>(Grid_size)); 
        initSdl();    
    }
    ~Game() {
        if(window) SDL_DestroyWindow(window);
        if(render) SDL_DestroyRenderer(render);
        SDL_Quit();
    }
    void initSdl();
    void init(); 
    void print();
    void swap_places();
    int check_neighbours(int i, int j, std::vector<std::vector<int>> temp_field);
    int get_x(int i);
    int get_y(int j);
    void Run();
    void renderInput();
};

void Game::init()
{
    for(int i = 0; i < Grid_size; ++i){
        for(int j = 0; j < Grid_size; ++j){
            field[i][j] = 0;
        }
    }
}

void Game::initSdl()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "ошибка в SDL_Init " << SDL_GetError() << '\n';
        exit(1); 
    }

    window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(!window){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }  

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!render){
        std::cout << "SDL_CreateRender Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

void Game::print()
{
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    for(int i = 0; i < Grid_size; ++i){
        SDL_RenderDrawLine(render, Cell_size * i, 0, Cell_size * i, Cell_size * Grid_size);
        SDL_RenderDrawLine(render, 0, Cell_size * i, Cell_size * Grid_size, Cell_size * i);
    }

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    for(int i = 0; i < Grid_size; ++i){
        for(int j = 0; j < Grid_size; ++j){
            if(field[i][j] == 1){
                SDL_Rect rectangle = {j * Cell_size, i *Cell_size, Cell_size, Cell_size};
                SDL_RenderFillRect(render, &rectangle);
            }
        }
    }

    SDL_RenderPresent(render);
    
}

void Game::swap_places()
{
    std::vector<std::vector<int>> temp_field(field);

    for(int i = 0; i < Grid_size; ++i){
        for(int j = 0; j < Grid_size; ++j){
            int count = check_neighbours(i, j, temp_field);

            if(temp_field[i][j] == 0 && count == 3){
                field[i][j] = 1;
            } else if(temp_field[i][j] == 1 && (count < 2 || count > 3)){
                field[i][j] = 0;
            }
        }
    }
}

int Game::get_y(int i)
{
    return (Grid_size + i) % Grid_size;
}

int Game::get_x(int j)
{
    return (Grid_size + j) % Grid_size;
}

int Game::check_neighbours(int i, int j, std::vector<std::vector<int>> temp_field)
{
    int count = 0;

    count += temp_field[get_x(i-1)][get_y(j-1)];
    count += temp_field[get_x(i)][get_y(j-1)];
    count += temp_field[get_x(i+1)][get_y(j-1)];
    count += temp_field[get_x(i-1)][get_y(j)];
    count += temp_field[get_x(i+1)][get_y(j)];
    count += temp_field[get_x(i-1)][get_y(j+1)];
    count += temp_field[get_x(i)][get_y(j+1)];
    count += temp_field[get_x(i+1)][get_y(j+1)];

    return count;
}

void Game::Run()
{

    bool run = true;
    SDL_Event e;

    while (run)
    {    
        while (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) run = false;

            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_SPACE){
                    pause = !pause;
                }

                if(e.key.keysym.sym == SDLK_s){
                    start = true;
                }
            }

            if(e.type == SDL_MOUSEBUTTONDOWN && !start){
                if(e.button.button == SDL_BUTTON_LEFT){
                    int cellx = e.button.x / Cell_size;
                    int celly = e.button.y / Cell_size;

                    field[celly][cellx] = !field[celly][cellx];
                }
            }
        }

        print();
        if(!pause && start){ swap_places(); 
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));       
        }
    }
    
}


int main () {

    int cell_size, grid_size, speed;
    std::cout << "Введите размер сетки : ";
    std::cin >> grid_size;
    std::cout << "\nВведите размер ячейки : ";
    std::cin >> cell_size;
    std::cout << "\nВведите скорость игры в миллисекундах : ";
    std::cin >> speed;

    Game g(cell_size, grid_size, speed);

    g.init();
    g.Run();

    return 0;
};