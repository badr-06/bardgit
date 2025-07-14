#include <iostream>
#include <vector>

int find(int x, std::vector<int>& parent){
    if(parent[x] != x){
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> parent(n + 1);
    int components = n;
    for(int i = 1; i <= n; ++i){
        parent[i] = i;
    }

    int x, y;
    for(int i = 1; i <= m; ++i){
        std::cin >> x >> y;

        int parx = find(x, parent);
        int pary = find(y, parent);

        if(parx != pary){
            parent[parx] = pary;
            components--;
        }

        if(components == 1){
            std::cout << i << '\n';
            break;
        }
    }

    return 0;
}