#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

const long long P = 911382629;
const long long MOD = 1e9+7;
long long inv_P;
std::vector<long long> pows;

struct Node{
    long long hash;
    int len;
    long long val;
};

long long mod_inverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

void push(std::vector<Node>& tree, std::vector<long long>& mod, long i){
    if(mod[i] != 0){
        mod[2*i+1] = mod[2*i+2] = mod[i];
        tree[2*i+1].val = tree[2*i+2].val = mod[i];
        tree[2*i+1].hash = mod[i] * (pows[tree[2*i+1].len] - 1) % MOD * inv_P % MOD;
        tree[2*i+2].hash = mod[i] * (pows[tree[2*i+2].len] - 1) % MOD * inv_P % MOD;
        mod[i] = 0;
    }
}

void assign(std::vector<Node>& tree, std::vector<long long>& mod, long l, long r, long val, long i, long left, long right){
    
    if(right < l || left > r){
        return;
    }

    if(l <= left && right <= r){
        tree[i].val = val;
        mod[i] = val;
        tree[i].hash = val * (pows[tree[i].len] - 1) % MOD * inv_P % MOD;
        return;
    }

    push(tree, mod, i);

    long mid = (right + left) / 2;
    assign(tree, mod, l, r, val, i * 2 + 1, left, mid);
    assign(tree, mod, l, r, val, i * 2 + 2, mid + 1, right);
    tree[i].hash = (tree[i * 2 + 1].hash * pows[tree[i * 2 + 2].len] + tree[i * 2 + 2].hash) % MOD;
}

Node get_hash(std::vector<Node>& tree, std::vector<long long>& mod, long l, long r, long i, long left, long right){

   if(right < l || left > r){
        return {0, 0, 0};
    }
      
    if(l <= left && r >= right){
        return tree[i];
    }

    push(tree, mod, i);
    int mid = (right + left) / 2;
    Node lNode = get_hash(tree, mod, l, r, i * 2 + 1, left, mid);
    Node rNode = get_hash(tree, mod, l, r, i * 2 + 2, mid + 1, right);
    return {
        (lNode.hash * pows[rNode.len] + rNode.hash) % MOD,
        lNode.len + rNode.len, 
        0
    };

}

int main() {

    long n;
    std::cin >> n;

    std::vector<long long> numbers(n);
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    int size = 1;
    while(size < n) size <<= 1;
    std::vector<Node> tree(2 * size, {0, 1, 0});
    std::vector<long long> mod(2 * size, 0);

    for(int i = 0; i < n; ++i){
        tree[size + i - 1] = {numbers[i], 1, numbers[i]};
    }

    pows.resize(size + 1);
    pows[0] = 1;
    for(int i = 1; i < size+1; ++i){
        pows[i] = (pows[i - 1] * P) % MOD;
    }

    for(int i = size - 2; i >= 0; --i){
        tree[i].hash = (tree[i * 2 + 1].hash * pows[tree[i * 2 + 2].len] + tree[i * 2 + 2].hash) % MOD;
        tree[i].len = tree[i * 2 + 1].len + tree[i * 2 + 2].len;
    }
    inv_P = mod_inverse(P-1, MOD);

    int m;
    std::cin >> m;
    std::string res;
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
            l--, r--, k--;
            Node res1 = get_hash(tree, mod, l, l + k, 0, 0, size - 1);
            Node res2 = get_hash(tree, mod, r, r + k, 0, 0, size - 1);
            res.push_back((res1.hash == res2.hash ? '+' : '-'));
        }
    }

    for(auto to : res){
        std::cout << to;
    }

    return 0;
}