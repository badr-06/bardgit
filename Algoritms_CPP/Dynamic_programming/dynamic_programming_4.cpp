#include <iostream>
#include <vector>
#include <algorithm>

int min_operations(int n) {

    std::vector<int> dp(n + 1, n);
    dp[0] = 0;
    dp[1] = 0;

    for(int i = 1; i < n; ++i){
        dp[i + 1] = std::min(dp[i + 1], dp[i] + 1);

        if(i * 2 <= n) dp[i * 2] = std::min(dp[i * 2], dp[i] + 1);
        if(i * 3 <= n) dp[i * 3] = std::min(dp[i * 3], dp[i] + 1);
    }

    return dp[n];
}

int main() {
    int n;
    std::cin >> n;
    std::cout << min_operations(n) << '\n';
    return 0;
}
