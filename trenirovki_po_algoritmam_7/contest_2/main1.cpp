#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    int ln = (int)log2(n) + 1;
    vector<vector<int>> st(ln, vector<int>(n));

    for(int i = 0; i < n; ++i) {
        cin >> st[0][i];
    }

    for(int i = 1; i < ln; ++i) {
        for(int j = 0; j + (1 << i) <= n; ++j) {
            st[i][j] = max(st[i-1][j], st[i-1][j + (1 << (i-1))]);
        }
    }

    vector<int> log_table(n+1);
    log_table[1] = 0;
    for(int i = 2; i <= n; ++i) {
        log_table[i] = log_table[i/2] + 1;
    }

    int k;
    cin >> k;
    vector<pair<int, int>> res;

    while(k--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        int len = r - l + 1;
        int pw = log_table[len];
        int num = max(st[pw][l], st[pw][r - (1 << pw) + 1]);

        int quantity = count(st[0].begin() + l, st[0].begin() + r + 1, num);
        
        res.emplace_back(num, quantity);
    }

    for(const auto& p : res) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}