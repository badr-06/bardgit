#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<int> mas(n);

    for(int i = 0; i < n; ++i){
        std::cin >> mas[i];
    }

    std::vector<int> dp(m+1, false);
    dp[0] = true;
    for(auto to : mas){
        for(int j = m; j >= to; --j){
            if(dp[j - to]){
                dp[j] = true;
            }
        }
    }
    
    int max_mas = 0;
    for(int i = m; i>=0; --i){
        if(dp[i]){
            max_mas = i;
            break;
        }
    }

    std::cout << max_mas << '\n';

    return 0;
}