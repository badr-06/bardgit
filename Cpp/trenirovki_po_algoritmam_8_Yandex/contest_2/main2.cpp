#include <iostream>
#include <vector>
#include <string>

int main() {

    std::string str;
    std::cin >> str;
    int n = str.length();

    std::vector<std::vector<int>> dp(n+1, std::vector<int>(2, INT32_MAX));

    dp[0][0] = 0;
    dp[0][1] = 1;
 
    int b = 0;
    for(int i = 0; i < str.length(); ++i){
        if(str[i] == 'L'){
            dp[i+1][0] = std::min(dp[i+1][0], dp[i][0] + 1);
            dp[i+1][1] = std::min(dp[i+1][1], dp[i+1][0] + 1);
            dp[i+1][1] = std::min(dp[i+1][1], dp[i][1]);
            dp[i+1][0] = std::min(dp[i+1][0], dp[i+1][1] + 1);
        } else if(str[i] == 'R'){
            dp[i+1][1] = std::min(dp[i+1][1], dp[i][1] + 1);
            dp[i+1][0] = std::min(dp[i+1][0], dp[i+1][1] + 1);
            dp[i+1][0] = std::min(dp[i+1][0], dp[i][0]);
            dp[i+1][1] = std::min(dp[i+1][1], dp[i+1][0] + 1);
        }   else {
            dp[i+1][0] = dp[i][0] + 1;
            dp[i+1][1] = dp[i][1] + 1;
        }
    }

    std::cout << dp[n][1];

    return 0;
}