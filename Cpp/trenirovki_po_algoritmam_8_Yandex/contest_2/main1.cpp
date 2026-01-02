#include <iostream>
#include <vector>

int main() {

    int n;
    std::cin >> n;
    std::vector<int> dp;

    if(n < 4) dp.reserve(4);
    else dp.reserve(n + 1);

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for(int i = 4; i <= n; ++i){
        dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
    }
    
    std::cout << dp[n];

    return 0;
}