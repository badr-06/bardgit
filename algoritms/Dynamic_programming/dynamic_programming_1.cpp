#include <iostream>
#include <vector>


int Fibonachi(int n, std::vector<int>& dp)
{
    if(dp[n] != -1) return dp[n];

    if(n < 2) return n;

    return dp[n] = Fibonachi(n - 1, dp) + Fibonachi(n - 2, dp);
}

int main() {

    int n;
    std::cin >> n;
    std::vector<int> dp(n + 1, -1);
    std::cout << Fibonachi(n, dp) << '\n';

    return 0;
}