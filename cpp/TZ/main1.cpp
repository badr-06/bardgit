#include <iostream>
#include <vector>

int main(){

    int n, m, x, y;

    std::cin >> n >> m >> x >> y;

    std::vector<std::string> windows(n * x);
    for(int i = 0; i < n * x; ++i){
        std::cin >> windows[i];
    }

    int result = 0;
    for(int floor = 0; floor < n; ++floor){
        for(int apartament = 0; apartament < m; ++apartament){

            int count_X = 0;
            for(int i = 0; i < x; ++i){
                for(int j = 0; j < y; ++j){
                    
                    int rows = floor * x + i;
                    int column = apartament * y + j;
                    if(windows[rows][column] == 'X') count_X++;
                }
            }

            if(count_X >= (x * y + 1) / 2) result++; 
        }
    }


    std::cout << result << '\n';
    
    return 0;
}