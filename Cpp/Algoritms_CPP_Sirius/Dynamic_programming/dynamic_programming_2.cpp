#include <iostream>
#include <vector>

int main() {

    int n;

    std::cin >> n;

    std::vector<int> numbers(n + 1, 0);

    for(int i = 1; i <= n; ++i){
        std::cin >> numbers[i];
    }

    std::vector<long long> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = numbers[1];
    long long sum = numbers[1];
    for(int i = 2; i <= n; ++i){
        dp[i] = std::max(dp[i - 1], dp[i - 2]) + numbers[i];
    }

    std::cout << dp[n] << std::endl;

    return 0;
}