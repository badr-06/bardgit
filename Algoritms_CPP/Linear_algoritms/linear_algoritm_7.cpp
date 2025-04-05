#include <iostream>
#include <vector>

int main(){

    int n;
    std::cin >> n;

    std::vector<int> a(n);

    for(int i = 0; i < n; ++i){
        std::cin >> a[i];
    }

    std::vector<long> perfix_sum(n + 1, 0);
    
    for(int i = 1; i <= n; ++i){
        perfix_sum[i] = perfix_sum[i - 1] + a[i - 1];
    }

    int ibest = 0, jbest = 0, imin = 0;

    for(int i = 1; i < n; ++i){

        if(perfix_sum[i] <= perfix_sum[imin]){
            imin = i;
        }

        if(perfix_sum[i + 1] - perfix_sum[imin] > perfix_sum[jbest + 1] - perfix_sum[ibest]){
            jbest = i;
            ibest = imin;
        }
    }

    std::cout << ibest + 1 << " " << jbest + 1 << '\n';

    return 0;
}