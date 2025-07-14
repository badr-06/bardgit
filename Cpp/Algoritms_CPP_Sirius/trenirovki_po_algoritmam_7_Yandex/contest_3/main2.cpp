#include <iostream>
#include <vector>

int main() {

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            std::cin >> m[i][j];
        }
    }
    std::vector<int> a(n, 0);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            a[i] |= m[i][j];
        }
    }

    for(auto to : a){
        std::cout << to << ' ';
    }
    std::cout << '\n';

    return 0;
}