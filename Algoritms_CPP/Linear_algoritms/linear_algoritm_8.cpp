#include <iostream>
#include <vector>

int main() {

    long n, r;
    std::cin >> n >> r;

    std::vector<int> monuments(n);

    for(int i = 0; i < n; ++i){
        std::cin >> monuments[i];
    }

    bool flag = true;
    long i = 0, j = 1;
    long res = 0;
    while (flag)
    {
        if(monuments[j] - monuments[i] > r) {
            res += n - j;
            i++;
        } 
        else if(monuments[j] - monuments[i] <= r){
            if(j == n-1){
                flag = false;
            } else {
                j++;
            }
        }
    }
    
    std::cout << res << '\n';

    return 0;
}