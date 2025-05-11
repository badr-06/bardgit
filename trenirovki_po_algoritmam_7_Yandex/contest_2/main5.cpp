#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

int get_zeros_in_segment(const std::vector<int>& tree, int l, int r, int i, int left, int right) {
    if (r < left || l > right) return 0;
    if (l <= left && right <= r) return tree[i];
    int mid = (left + right) / 2;
    return get_zeros_in_segment(tree, l, r, 2*i+1, left, mid) + 
           get_zeros_in_segment(tree, l, r, 2*i+2, mid+1, right);
}

int find_k(std::vector<int>& tree, int l, int r, int k, int i, int left, int rigth){
    if(rigth < l || r < left){
        return -1;
    }
    if(l <= left && r >= rigth){
        if(k > tree[i]) return -1;
        if(left == rigth) return left + 1;
    }

    int mid = (left + rigth) / 2;
    int left_zeros = get_zeros_in_segment(tree, l, r, i * 2 + 1, left, mid);
    if(k <= left_zeros){
        return find_k(tree, l, r, k, i * 2 + 1, left, mid);
    } else {
        return find_k(tree, l, r, k - tree[i * 2 + 1], i * 2 + 2, mid + 1, rigth);
    }
}

int k_zero(std::vector<int>& tree, int l, int r, int k, int i, int left, int rigth){
    
    if(l > rigth || r < left){
        return -1;
    }

    if(l <= left && r >= rigth){
        return find_k(tree, l, r, k, i, left, rigth);
    }

    int mid = (left + rigth) / 2;
    int left_pos = k_zero(tree, l, r, k, i * 2 + 1, left, mid);
    if(left_pos != -1){
        return left_pos;
    }
    int left_zeros = get_zeros_in_segment(tree, l, r, i * 2 + 1, left, mid);
    return k_zero(tree, l, r, k - left_zeros, i * 2 + 2, mid + 1, rigth);
}

void update(std::vector<int>& tree, int idx, int val, int i, int left, int rigth){
    if(left == rigth){
        tree[i] = val == 0 ? 1 : 0;
        return;
    }

    int mid = (left + rigth) / 2;
    if(idx <= mid){
        update(tree, idx, val, i * 2 + 1, left, mid);
    } else {
        update(tree, idx, val, i * 2 + 2, mid + 1, rigth);
    }
    tree[i] = tree[i * 2 + 1] + tree[i * 2 + 2];
}

int main(){

    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    int size = 1;
    while(size < n) size <<= 1;
    std::vector<int> tree(2 * size);

    for(int i = 0; i < n; ++i){
        tree[size + i - 1] = numbers[i] == 0 ? 1 : 0;
    }

    for(int i = size - 2; i >= 0; --i){
        tree[i] = tree[i * 2 + 1] + tree[i * 2 + 2];
    }

    int m;
    std::cin >> m;

    while(m--){
        char ch;
        std::cin >> ch;
        
        if(ch == 's'){
            int l, r, k;
            std::cin >> l >> r >> k;
            l--, r--;
            std::cout << k_zero(tree, l, r, k, 0, 0, size - 1) << '\n';
        } else if(ch == 'u'){
            int idx, val;
            std::cin >> idx >> val;
            idx--;
            update(tree, idx, val, 0, 0, size - 1);
        }
    }

    return 0;
}