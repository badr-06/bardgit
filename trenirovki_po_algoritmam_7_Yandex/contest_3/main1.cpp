#include <iostream>
#include <bitset>

int main() {

    
    unsigned long long num;
    std::cin >> num;

    int res = 0;
    
    for(unsigned long long i = 0, j = 1; i < 64; ++i, j <<= 1){
        if((num & j) != 0){
            res++;
        }
    }

    std::cout << res << '\n';
    return 0;
}