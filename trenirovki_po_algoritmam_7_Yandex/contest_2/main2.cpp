#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {

    int n;
    std::cin >> n;
    int ln = (int)log2(n) + 1;
    std::vector<std::vector<std::pair<int, int>>> st(ln, std::vector<std::pair<int, int>>(n));

    int a, b;
    for(int i = 0; i < n; ++i){
        std::cin >> a;
        st[0][i].first = a;
        st[0][i].second = i + 1;
    }

    for(int i = 1; i < ln; ++i){
        for(int j = 0; j + (1 << i) <= n; ++j){
            if(st[i-1][j].first > st[i-1][j + (1 << (i-1))].first){
                st[i][j].first = st[i-1][j].first;
                st[i][j].second = st[i-1][j].second;
            } else {
                st[i][j].first = st[i-1][j + (1 << (i-1))].first;
                st[i][j].second = st[i-1][j + (1 << (i-1))].second;
            }
        }
    }

    std::vector<int> log_table(n+1);
    log_table[1] = 0;
    for(int i = 2; i <= n; ++i){
        log_table[i] = log_table[i/2] + 1;
    }
    
    int k;
    std::cin >> k;
    std::vector<int> res;

    while(k--){
        int l, r;
        std::cin >> l >> r;

        int len = r - l + 1;
        int pw = log_table[len];

        int num = std::max(st[pw][l-1].first, st[pw][r - (1 << pw)].first);
        
        int index;
        if(st[pw][l-1].first > st[pw][r - (1 << pw)].first){
            index = st[pw][l-1].second;
        } else {
            index = st[pw][r - (1 << pw)].second;
        }  

        res.push_back(index);
    }

    for(const auto& p : res) {
        std::cout << p << '\n';
    }

    return 0;
}
