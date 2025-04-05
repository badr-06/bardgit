#include <iostream>
#include <vector>

int F(int n, std::vector<int>& dp)
{

    if(n == 1 || n == 0) return dp[n];
    else if(n == 2) return dp[n];
    else if(dp[n] != -1) return dp[n];

    dp[n] = F(n - 1, dp) + F(n - 2, dp) + F(n - 3, dp);

    return dp[n];
}

int main(){

    int n;
    std::cin >> n;
    std::vector<int> dp(n+1, -1);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;

    int res = F(n, dp);

    std::cout << res << '\n';
   
    return 0;
}