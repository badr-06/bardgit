#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

int get_max(std::vector<int>& tree, int l, int r, int i, int left, int rigth){
    if(l <= left && r >= rigth){
        return tree[i];
    }

    if(rigth < l || left > r){
        return INT_MIN;
    }

    int mid = (rigth + left) / 2;
    return std::max(get_max(tree, l, r, i * 2 + 1, left, mid), 
                    get_max(tree, l, r, i * 2 + 2, mid + 1, rigth));
}

void update(std::vector<int>& tree, std::vector<int>& numbers, int idx, int val, int i, int left, int rigth){
    if(left == rigth){
        tree[i] = val;
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

    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    int size = 1;
    while (size < n ) size <<= 1;
    std::vector<int> tree(2 * size, INT_MIN);

    for(int i = 0; i < n; ++i){
        tree[size + i - 1] = numbers[i]; 
    }

    for(int i = size - 2; i >= 0; --i){
        tree[i] = std::max(tree[i * 2 + 1], tree[i * 2 + 2]);
    }

    int m;
    std::cin >> m;

    while(m--){
    char ch;
    int l, r;
    
    std::cin >> ch >> l >> r;
    if(ch == 's'){
        l--, r--;
        std::cout << get_max(tree, l, r, 0, 0, size - 1) << ' ';
    } else if(ch == 'u'){
        l--;
        update(tree, numbers, l, r, 0, 0, size - 1);
    }

    }
    return 0;
}