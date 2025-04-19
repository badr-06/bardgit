#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

void build(std::vector<int>& tree, std::vector<int> numbers, int i, int left, int rigth)
{
    if(left == rigth){
        tree[i] = numbers[left];
    } else {
        int mid = (rigth + left) / 2;
        build(tree, numbers, i * 2 + 1, left, mid);  
		build(tree, numbers, i * 2 + 2, mid + 1, rigth);  
		tree[i] = std::max(tree[i * 2 + 1], tree[i * 2 + 2]);
    }

}

int main() {

    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    
    for(int i = 0; i < n; ++i) std::cin >> numbers[i];

    std::vector<int> tree(4*n);

    build(tree, numbers, 0, 0, n - 1);

    return 0;
}