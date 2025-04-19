#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

int k_zero(std::vector<std::pair<int, int>>& tree, int l, int r, int k, int i, int left, int rigth){
    if(tree[i].first != 0 || k > tree[i].second){
        return -1;
    }

    if(left == rigth){
        return i;
    }

    int mid = (left + rigth) / 2;
    if(tree[i * 2 + 1].second >= k){
        return k_zero(tree, l, r, k, i * 2 + 1, left, mid);
    } else {
        return k_zero(tree, l, r, k - tree[i * 2 + 1].second, i * 2 + 2, mid + 1, rigth);
    }
}

int main(){

    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    int size = 1;
    while(size < n) size <<= 1;
    std::vector<std::pair<int, int>> tree(2 * size, std::pair<int, int>(INT_MAX, 1));

    for(int i = 0; i < n; ++i){
        tree[size + i - 1].first = numbers[i];
    }

    for(int i = size - 2; i >= 0; --i){
        if(tree[i * 2 + 1].first == tree[i * 2 + 2].first){
            tree[i].first = tree[i * 2 + 1].first;
            tree[i].second = tree[i * 2 + 1].second + 1;
        } else {
            tree[i] = std::min(tree[i * 2 + 1], tree[i * 2 + 2]);
        }
    }

    int m;
    std::cin >> m;

    while(m--){
        int ch;
        std::cin >> ch;
        
        if(ch == 's'){
            int l, r, k;
            std::cin >> l >> r >> k;
            l--, r--;
            std::cout << k_zero(tree, l, r, k, 0, 0, size - 1) + 1 << 'yes\n';
        }
    }

    return 0;
}