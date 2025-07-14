#include <iostream>
#include <bits/stdc++.h>

long long sum(std::vector<long>& t, int x) {
    long long result = 0;

    for (; x >= 0; x = (x & (x + 1)) - 1) {
        result += t[x];
    }

    return result;
}

long long sum(std::vector<long>& t, int l, int r) {
    if (l > 0) {
        return sum(t, r) - sum(t, l - 1);
    } else {
        return sum(t, r);
    }
}

void update(std::vector<int>& a, std::vector<long long>& t, int idx, int val, int n){
    int d = val - a[idx];
    a[idx] += d; 

    for(; idx < n; idx |= idx + 1){
        t[idx] += d;
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n, 0);
    std::vector<long long> t(n, 0);

    std::vector<long long> res;
    while(k--){
        char ch;
        std::cin >> ch;

        if(ch == 'A'){
            int idx, val;
            std::cin >> idx >> val;
            idx--;
            update(a, t, idx, val, n);
        } else if(ch == 'Q'){
            int l, r;
            std::cin >> l >> r;
            l--, r--;
            res.push_back(sum(t, l, r));
        }
    } 

    for(auto to : res){
        std::cout << to << '\n';
    }

    return 0;   
}