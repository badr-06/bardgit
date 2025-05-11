#include <iostream>
#include <vector>
#include <climits>
#include <math.h>
#include <map>
#include <set>

int main() {

    int N, K, L = 100;
    std::cin >> N >> K;

    std::vector<int> lenghts(N+1);
    std::vector<int> colors(N+1);

    for(int i = 1; i <= N; ++i){
        std::cin >> lenghts[i];
        std::cin >> colors[i];
    }

    std::vector<std::vector<std::pair<int, int>>> dp(K + 1,  std::vector<std::pair<int, int>>(N + 1, {0, 0}));
    for(int i = 1; i <= K; ++i){
        for(int j = 1; j <= N; ++j){
            if(colors[j] == i){
            }
        }
    }

   

    return 0;
}