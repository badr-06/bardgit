#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

struct Node {
    int max_len;    // Максимальная длина последовательности нулей
    int left_len;   // Длина последовательности нулей слева
    int right_len;  // Длина последовательности нулей справа
    int full_len;   // Длина отрезка
};

Node zeroes(std::vector<Node>& tree, int l, int r, int i, int left, int rigth){
    
    if(l > rigth || r < left){
        return {0, 0, 0, 0};
    }

    if(l <= left && r >= rigth){
        return tree[i];
    }

    int mid = (left + rigth) / 2;
    Node left_node = zeroes(tree, l, r, i * 2 + 1, left, mid);
    Node rigth_node = zeroes(tree, l, r, i * 2 + 2, mid + 1, rigth);

    Node res;

    res.full_len = left_node.full_len + rigth_node.full_len;

    res.left_len = left_node.left_len;
    if(left_node.left_len == left_node.full_len){
        res.left_len += rigth_node.left_len;
    }

    res.right_len = rigth_node.right_len;
    if(rigth_node.right_len == rigth_node.full_len){
        res.right_len += left_node.right_len;
    }

    res.max_len = std::max({left_node.max_len, rigth_node.max_len, 
                            left_node.right_len + rigth_node.left_len});

    return res;
}

void update(std::vector<Node>& tree, int idx, int val, int i, int left, int rigth){
    if(left == rigth){
        int is_zero = val == 0 ? 1 : 0;
        tree[i].max_len = tree[i].left_len = tree[i].right_len = is_zero;
        return;
    }

    int mid = (left + rigth) / 2;
    if(idx <= mid){
        update(tree, idx, val, i * 2 + 1, left, mid);
    } else {
        update(tree, idx, val, i * 2 + 2, mid + 1, rigth);
    }

    tree[i].left_len = tree[i * 2 + 1].left_len;
    if(tree[i * 2 + 1].full_len == tree[i * 2 + 1].left_len){
        tree[i].left_len += tree[i * 2 + 2].left_len;
    }

    tree[i].right_len = tree[i * 2 + 2].right_len;
    if(tree[i * 2 + 2].full_len == tree[i * 2 + 2].right_len){
        tree[i].right_len += tree[i*2+1].right_len;
    }

    tree[i].max_len = std::max({tree[i * 2 + 1].max_len, tree[i * 2 + 2].max_len, 
                                tree[i * 2 + 1].right_len + tree[i * 2 + 2].left_len});
}

int main(){

    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    int size = 1;
    while(size < n) size <<= 1;
    std::vector<Node> tree(2 * size);

    for(int i = 0; i < n; ++i){
        tree[size + i - 1].full_len = 1;
        tree[size + i - 1].left_len = tree[size + i - 1].right_len = tree[size + i - 1].max_len = numbers[i] == 0 ? 1 : 0;
    }

    for(int i = size - 2; i >= 0; --i){
        tree[i].full_len = tree[i * 2 + 1].full_len + tree[i * 2 + 2].full_len;
        
        tree[i].left_len = tree[i * 2 + 1].left_len;
        if(tree[i * 2 + 1].full_len == tree[i * 2 + 1].left_len){
            tree[i].left_len += tree[i * 2 + 2].left_len;
        }

        tree[i].right_len = tree[i * 2 + 2].right_len;
        if(tree[i * 2 + 2].full_len == tree[i * 2 + 2].right_len){
            tree[i].right_len += tree[i*2+1].right_len;
        }

        tree[i].max_len = std::max({tree[i * 2 + 1].max_len, tree[i * 2 + 2].max_len, 
                                    tree[i * 2 + 1].right_len + tree[i * 2 + 2].left_len});
    }

    int m;
    std::cin >> m;
    std::vector<int> res;
    while(m--){
        std::string str;
        std::cin >> str;
        
        if(str[0] == 'Q'){
            int l, r;
            std::cin >> l >> r;
            l--, r--;
            Node s = zeroes(tree, l, r, 0, 0, size - 1);
            res.push_back(s.max_len);
        } else if(str[0] == 'U'){
            int idx, val;
            std::cin >> idx >> val;
            idx--;
            update(tree, idx, val, 0, 0, size - 1);
        }
    }

    for(auto to : res){
        std::cout << to << '\n';
    }

    return 0;
}