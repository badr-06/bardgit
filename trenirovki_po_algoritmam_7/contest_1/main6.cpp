#include <iostream>
#include <vector>
#include <climits>
#include <math.h>

int main() {
    long long M;
    std::cin >> M;
    
    std::vector<long long> a(31);
    std::vector<long long> cost(31);
    for (int j = 0; j <= 30; ++j) {
        std::cin >> a[j];
        cost[j] = (1LL << j);
    }

    std::vector<bool> check(31, true);
    for (int i = 1; i <= 30; ++i) {
        if (a[i] == 0) {
            check[i] = false;
            continue;
        }
        
        for (int k = 0; k < i; ++k) {
            if (!check[k]) continue;
            if (a[k] * (cost[i] / cost[k]) >= a[i]) {
                check[i] = false;
                break;
            }
        }
    }
    
    long long min_cost = LLONG_MAX;

    for(int i = 0; i <= 30; ++i){
        if(!check[i]) continue;

        long long need = M;
        long long current_cost = 0;

        long long take1 = need / a[i];
        current_cost = take1 * cost[i];
        need -= take1 * a[i];

        int ind = 30;
        if(need > 0){
        for(int j = ind; j >= 0; j--){
            if(!check[j]) continue;

            long long take2 = 0;
            if(need >= a[j]){
                take2 = need / a[j];
            }
            else {
                take2 = (need + a[j] -1) / a[j];
            }
            current_cost += take2 * (1LL << j);
            need -= take2 * a[j];
            if(need <= 0){
                if(current_cost < min_cost){
                    min_cost = current_cost;
                }
                
                current_cost  = take1 * cost[i];
                need = M - (take1 * a[i]);
                j = (ind--);
            }

        }
        }

        if(need <= 0 && current_cost < min_cost){
            min_cost = current_cost;
        } 
       
    }

    
    std::cout << min_cost << std::endl;

    return 0;
}

