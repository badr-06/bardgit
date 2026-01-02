#include <iostream>

int main() {

    long long n, k;
    std::cin >> n >> k;
    
    while(k > 0){
        int temp = n % 10;
        if(temp == 0){
            break;
        }
        else if((temp == 2 || temp == 4 || temp == 6 || temp == 8) && k >= 4){
            long long s = k / 4;
            n += s * 20;
            k = k % 4;
        } else {
            n += temp;
            k--;
        }
        
    }

    std::cout << n << std::endl;

    return 0;
}
