#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>

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

    int max_sum = 0, max_i, max_j;    
    std::vector<std::vector<int>> dp(n + 1, std::vector(m + 1, 0));
    std::vector<std::vector<bool>> visited(n+1, std::vector<bool>(m+1, false));
    
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= m; ++j){
            if(j >= mas[i-1] && dp[i-1][j - mas[i-1]] + paid[i - 1] > dp[i-1][j]){
                visited[i][j] = true;
                dp[i][j] = dp[i-1][j-mas[i-1]] + paid[i-1];
            }
            else {
                dp[i][j] = dp[i-1][j];
            }
        }       
    }   

    std::list<int> res;
    int j = m;
    for(int i = n; i >= 0; --i){
        if(visited[i][j]){
            res.push_front(i);
            j -= mas[i-1];
        }
    }

    for(auto to : res){
        std::cout << to << '\n';
    }

    return 0;
}