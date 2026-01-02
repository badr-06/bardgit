#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; ++i)
        std::cin >> A[i];

    std::vector<long long> dp(n + 1, 0);
    std::vector<int> prev(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        long long sum = 0;
        int minv = INT_MAX;
        for (int len = 1; len <= k && i - len + 1 > 0; ++len) {
            sum += A[i - len + 1];
            minv = std::min(minv, A[i - len + 1]);
            long long defense = sum * minv;
            if (dp[i - len] + defense > dp[i]) {
                dp[i] = dp[i - len] + defense;
                prev[i] = i - len;
            }
        }
    }

    // Восстановим башни
    std::vector<int> res;
    int i = n;
    while (i > 0) {
        res.push_back(prev[i] + 1);
        i = prev[i];
    }
    std::reverse(res.begin(), res.end());

    std::cout << res.size() << "\n";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
