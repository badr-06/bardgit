#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    int N;
    std::cin >> N;

    std::vector<int> s(N);
    std::vector<int> dp(N + 1, 0);

    for(int i = 0; i < N; ++i){
        std::cin >> s[i];
    }

    std::sort(dp.begin(), dp.end());
    
    dp[1] = s[1] - s[0];
    if(N > 2){
        dp[2] = s[2] - s[0];
        for(int i = 3; i < N; ++i){
            dp[i] = std::min(dp[i - 1], dp[i - 2]) + s[i] - s[i - 1];
        }
    }

    std::cout << dp[N - 1] << '\n';

    return 0;
}