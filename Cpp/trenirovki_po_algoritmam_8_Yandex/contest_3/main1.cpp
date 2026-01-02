#include <iostream>
#include <cmath>

int main() {

    int a, b, S;
    std::cin >> a >> b >> S;

    long long D = (long long)(a-b)*(a-b) + 4 * S;

    int rootD = sqrt(D);

    int x1 = (a + b - rootD) / 2;
    if(((a + b - rootD) % 2 == 0) && x1 > a && x1 > b && ((x1 - a) * (x1 - b) == S)){
        std::cout << x1 << std::endl;
        return 0;
    }

    int x2 = (a + b - rootD) / 2;
    if(((a + b + rootD) % 2 == 0) && x1 > a && x1 > b && ((x2 - a) * (x2 - b) == S)){
        std::cout << x2 << std::endl;
        return 0;
    }

    std::cout << -1 << std::endl;

    return 0;
}    

// if(rootD * rootD != D){
//         std::cout << -1 << std::endl;
//     }