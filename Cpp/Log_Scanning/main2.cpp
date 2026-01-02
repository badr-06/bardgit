#include <iostream>
#include <vector>

int main(){

    int n, a, b;
    std::cin >> n;

    std::vector<long long> Q(n);
    std::vector<long long> C(n);
    std::vector<double long> D(n);

    for(int i = 0; i < n; ++i){
        std::cin >> Q[i];
    }

    for(int i = 0; i < n; ++i){
        std::cin >> C[i];
    }
    
    std::cin >> a >> b;

    for(int i = 0; i < n; ++i){
        D[i] = a + static_cast<long double>((C[i] * (b - a)) / 255.0);
    }

    double long result = 0;

    for(int i = 0; i < n; ++i){
        result += Q[i] * D[i]; 
    }

    std::cout << static_cast<long long>(result) << '\n';

    return 0;
}