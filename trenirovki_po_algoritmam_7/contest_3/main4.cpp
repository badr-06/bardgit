#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

int main() {

    int n;
    std::cin >> n;

    size_t idx;
    for(size_t i = 16, j = 32768; i > 0; --i, j >>= 1){
        if((j & n) != 0){ 
            idx = i - 1;
            break;
        }
    }
    
    int max_num = n;
    std::bitset<16> a = n;
    for(int i = 0; i <= idx; ++i){
        
        int temp = a[0];
        n >>= 1;
        if(temp == 1){
            n |= (1 << idx);
            max_num = std::max(n, max_num);
        }
        a = n;
    }

    std::cout << max_num << '\n';

    return 0;

}