#include <iostream>
#include <vector>

int main() {


    int n;
    std::cin >> n;
    std::vector<int> mushrooms(n+1,0);

    for(int i = 1; i <= n; ++i){
        std::cin >> mushrooms[i];
    }

    int weightMushtoomsVasy = 0;
    int weightMushtoomsMashi = 0;
    int min_V = mushrooms[1];
    int max_M = mushrooms[2];

    for(int i = 1; i <= n; i+=2){
        
        weightMushtoomsVasy += mushrooms[i]; 
        min_V = std::min(min_V, mushrooms[i]);
        
        if(i+1 <= n) {
            weightMushtoomsMashi += mushrooms[i+1];
            max_M = std::max(max_M, mushrooms[i+1]);
        }
    }

    int delta = weightMushtoomsVasy - weightMushtoomsMashi;

    if(delta < delta + (max_M - min_V) * 2) delta =  delta + (max_M - min_V) * 2;

    std::cout << delta << '\n';


    return 0;
}