#include <iostream>
#include <vector>

int main() {

    int n, m;

    std::cin >> n >> m;

    std::vector<int> h(n);
    std::vector<int> p(n + 1);

    for(int i = 0; i < n; i++){
        std::cin >> h[i];
    }

    int counter = 0;
    p[0] = counter;
    for(int i = 1; i < n; ++i){
        if(h[i] > h[i-1]) counter++;
        p[i] = counter;
    }
    std::vector<int> res(m);

    int L, R;
    for(int i = 0; i < m; ++i){
        std::cin >> L >> R;
        res[i] = p[R - 1] - p[L - 1];
    }


    for(int i = 0; i < m; ++i){
        std::cout << res[i] << std::endl;
    }

    return 0;
}