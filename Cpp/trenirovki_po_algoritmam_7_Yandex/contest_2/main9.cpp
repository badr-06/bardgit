#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

void push(std::vector<long long>& tree, std::vector<long long>& mod, long i, long left, long right){
    if(mod[i] != 0 && i * 2 + 2 < tree.size()){

        mod[i * 2 + 1] = mod[i];
        mod[i * 2 + 2] = mod[i];
        tree[i * 2 + 1] = mod[i];
        tree[i * 2 + 2] = mod[i];
        mod[i] = 0;
    }
}

void assign(std::vector<long long>& tree, std::vector<long long>& mod, long l, long r, long val, long i, long left, long right){
    
    push(tree, mod, i ,left, right);
    
    if(right < l || left > r){
        return;
    }

    if(l <= left && right <= r){
        tree[i] = val;
        mod[i] = val;
        return;
    }

    long mid = (right + left) / 2;
    assign(tree, mod, l, r, val, i * 2 + 1, left, mid);
    assign(tree, mod, l, r, val, i * 2 + 2, mid + 1, right);
    tree[i] = tree[i * 2 + 1] + tree[i * 2 + 2];
}

long long get_sum(std::vector<long long>& tree, std::vector<long long>& mod, long l, long r, long i, long left, long right){
    
    push(tree, mod, i ,left, right);    

    if(l <= left && r >= right){
        return tree[i];
    }

    if(right < l || left > r){
        return 0;
    }

    int mid = (right + left) / 2;
    return get_sum(tree, mod, l, r, i * 2 + 1, left, mid) + get_sum(tree, mod, l, r, i * 2 + 2, mid + 1, right);
}

int main() {

    long n;
    std::cin >> n;

    std::vector<long long> numbers(n);
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    int size = 1;
    while(size < n) size <<= 1;
    std::vector<long long> tree(2 * size, INT_MIN);
    std::vector<long long> mod(2 * size, 0);

    for(int i = 0; i < n; ++i){
        tree[size + i - 1] = numbers[i];
    }

    for(int i = size - 2; i >= 0; --i){
        tree[i] = tree[i * 2 + 1] + tree[i * 2 + 2];
    }

    int m;
    std::cin >> m;

    while(m--){
        int ch;
        std::cin >> ch;

        if(ch == 0){
            long l, r, k;
            std::cin >> l >> r >> k;
            l--, r--;
            assign(tree, mod, l, r, k, 0, 0, size - 1);
        }
        else if(ch == 1){
            long l, r, k;
            std::cin >> l >> r >> k;
            l--, r--;
            int res1 = get_sum(tree, mod, l, l + k, 0, 0, size - 1);
            int res2 = get_sum(tree, mod, r, r + k, 0, 0, size - 1);
            std::cout << (res1 == res2 ? '+' : '-');
        }
    }

    return 0;
}