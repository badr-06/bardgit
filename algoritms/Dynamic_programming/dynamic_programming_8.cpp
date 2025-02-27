#include <iostream>
#include <vector>

int main(){

    int N;
    std::cin >> N;
    std::vector<std::vector<int>> persons(N + 1, std::vector<int>(3));

    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < 3; ++j){
            std::cin >> persons[i][j];
        }
    }

    std::vector<int> dp(N + 1, 0);

    dp[1] = persons[1][0];
    if(N > 1){
        dp[2] = std::min(persons[1][0] + persons[2][0], persons[1][1]);
        int A, B, C;
        for(int i = 3; i <= N; ++i){
            C = persons[i - 2][2] + dp[i - 3];
            B = persons[i - 1][1] + dp[i - 2];
            A = persons[i][0] + dp[i - 1]; 
            dp[i] = std::min(std::min(A, B), C);
        }

    }
    
    std::cout << dp[N] << '\n';

    return 0;
}