#include <iostream>
#include <vector>

int find(int x, std::vector<int>& parent){
    if(parent[x] != x){
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}


int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<int> parent(n + 1);
    int components = n;
    for(int i = 1; i <= n; ++i){
        parent[i] = i;
    }

    int x, y;
    for(int i = 0; i < m; ++i) std::cin >> x >> y;

    std::vector<std::vector<int>> comp(3, std::vector<int>(k, 0));
    for(int i = 0; i < k; ++i){
        std::string a;
        std::cin >> a >> comp[1][i] >> comp[2][i];
        if(a[0] == 'a'){
            comp[0][i] = 1;
        } else {
            comp[0][i] = 0;
        }
    }
    std::vector<int> result(k, 0);
    for(int i = k - 1; i >= 0; --i){
        if(comp[0][i]){
            result[i] = (find(comp[1][i], parent) == find(comp[2][i], parent));
        } else {
            int parx = find(comp[1][i], parent);
            int pary = find(comp[2][i], parent); 

            if(parx != pary) parent[parx] = pary;
        }   
    }

    for(int i = 0; i < k; ++i){
        if(comp[0][i]){
            if(result[i]) std::cout << "YES\n";
            else std::cout << "NO\n";
        }
    }

    return 0;
}