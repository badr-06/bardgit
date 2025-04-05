#include <iostream>
#include <vector>

int main() {

    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> dp(n + 1, std::vector(2, 0));
    dp[1][0] = 1;
    dp[1][1] = k - 1;

    for(int i = 2; i <= n; ++i){
        dp[i][0] = dp[i-1][1];

        dp[i][1] = (k - 1) * (dp[i - 1][0] + dp[i-1][1]);
    }

    std::cout << dp[n][1] + dp[n][0] << '\n';

    return 0;
}