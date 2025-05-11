#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<int> mas(n);
    std::vector<int> paid(n);
    
    for(int i = 0; i < n; ++i){
        std::cin >> mas[i];
    }
    for(int i = 0; i < n; ++i){
        std::cin >> paid[i];
    }

    int max_sum = 0;    
    std::vector<std::vector<int>> dp(n + 1, std::vector(m + 1, 0));
    std::vector<int> visited(m+1, false);
    visited[0] = true;
    for(int i = 1; i <= n; ++i){
        dp[i] = dp[i-1];
        for(int j = m; j >= mas[i-1]; --j){
            if(visited[j - mas[i-1]]){
                visited[j] = true;
                dp[i][j] = std::max(dp[i][j], dp[i][j-mas[i-1]] + paid[i-1]);
                max_sum = max_sum >= dp[i][j] ? max_sum : dp[i][j];
            }
        }       
    }   

    std::cout << max_sum << '\n';

    return 0;
}