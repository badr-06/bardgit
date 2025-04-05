#include <iostream>
#include <vector>
#include <algorithm>

int main()
{

    int n, m;
    std::cin >> n >> m;

    if(n == 0 || m == 0) return 0;

    std::vector<std::vector<int>> field(n + 1, std::vector<int>(m + 1, 0));

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            std::cin >> field[i][j];
        }
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            dp[i][j] = field[i][j] + std::max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int sum = dp[n][m];

    std::string s;
    int i = n, j = m;

    while( i != 1 || j != 1){
            if(sum - field[i][j] == dp[i-1][j]){
            s.push_back('D');
            sum -= field[i--][j];
            }
            else if(sum - field[i][j] == dp[i][j-1]){
            s.push_back('R');
            sum -= field[i][j--];
            }
    }

    std::reverse(s.begin(), s.end());

    std::cout << dp[n][m] << '\n';
    for(auto to : s){
        std::cout << to << ' ';
    }
    std::cout << std::endl;

    return 0;
}