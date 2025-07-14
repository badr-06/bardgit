#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

int main(){

    int n, m;
    std::cin >> n;

    std::vector<int> Tshirts(n);
    for(int i = 0; i < n; ++i){
        std::cin >> Tshirts[i];
    }

    std::cin >> m;

    std::vector<int> trousers(m);
    for(int i = 0; i < m; ++i){
        std::cin >> trousers[i];
    }

    long long min = LONG_LONG_MAX;
    int mina = 0, minb = 0;
    for(int i = 0, j = 0; i < n && j < m && min;)
    {   
        long long temp = std::abs(Tshirts[i] - trousers[j]);
        if(temp < min){
            min = temp;
            mina = Tshirts[i];
            minb = trousers[j];
        }

        if(Tshirts[i] > trousers[j]){
            j++;
        } else {
            i++;
        }
    }

    std::cout << mina << " " << minb << '\n';

    return 0;
}