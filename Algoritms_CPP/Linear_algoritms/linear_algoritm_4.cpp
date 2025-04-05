#include <iostream>
#include <vector>

int main() {

    int n, k, m;

    std::cin >> n >> k >> m;

    int a[n];

    for(int i = 0; i < n; ++i){
        std::cin >> a[i];
    }

    int sum = 0;
    int index = 0;


    for(int i = 0; i < k + 1; ++i){
        sum += a[i];
    }

    if(sum == m && k > 0 && n > k){
        index = 1;
    } else {
    for(int i = k + 1; i < n; ++i){
        sum += a[i] - a[i - k - 1];
        if(sum == m) {
            index = i - k + 1;
            break;
        }
    }
    }

    std::cout << index << std::endl;

    return 0;   
}