#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

std::pair<int, int> get_min(std::vector<std::pair<int, int>>& tree, int l, int x, int i, int left, int rigth){
    if(l > rigth || tree[i].first < x){
        return {-1, -1};
    }

    if(left == rigth){
        return tree[i];
    }

    int mid = (rigth + left) / 2;
    std::pair<int, int> lp = get_min(tree, l, x, i * 2 + 1, left, mid); 
    if(lp.second != -1) return lp;

    return get_min(tree, l, x, i * 2 + 2, mid + 1, rigth);
}

void update(std::vector<std::pair<int, int>>& tree, std::vector<int>& numbers, int idx, int val, int i, int left, int rigth){
    if(left == rigth){
        tree[i].first = val;
        return;
    }

    int mid = (left + rigth) / 2;
    if(idx <= mid){
        update(tree, numbers, idx, val, i * 2 + 1, left, mid);
    } else {
        update(tree, numbers, idx, val, i * 2 + 2, mid + 1, rigth);
    }
    tree[i] = std::max(tree[i * 2 + 1], tree[i * 2 + 2]);
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> numbers(n);
    
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    int size = 1;
    while (size < n ) size <<= 1;
    std::vector<std::pair<int, int>> tree(2 * size, std::pair<int, int>(INT_MIN, 0));

    for(int i = 0; i < n; ++i){
        tree[size + i - 1].first = numbers[i];
        tree[size + i - 1].second = i; 
    }

    for(int i = size - 2; i >= 0; --i){
        tree[i] = std::max(tree[i * 2 + 1], tree[i * 2 + 2]);
    }

    while(m--){
    int ch;
    int l, x;
    
    std::cin >> ch >> l >> x;
    if(ch == 1){
        l--;
        std::pair<int, int> result = get_min(tree, l, x, 0, 0, size - 1);
        std::cout << (result.second == -1 ? -1 : result.second + 1) << '\n';
    } else if(ch == 0){
        l--;
        update(tree, numbers, l, x, 0, 0, size - 1);
    }
    }

    return 0;
}