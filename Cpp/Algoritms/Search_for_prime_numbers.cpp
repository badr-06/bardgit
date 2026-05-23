#include <iostream>
#include <vector>
#include <cmath>

void SerchPrimeNumbers(std::vector<int>& primeNumbers, const int n)
{
    std::vector<bool> vec(n, true);
    if(n >= 1){
        vec[0] = false;
        vec[1] = false;
    }

    for(int i = 2; i <= sqrt(n); ++i){
        for(int j = i * i; j <= n; j+=i){
            if(vec[j]){
                vec[j] = false;
            }
        }
    }

    for(int i = 0; i <= n; ++i){
        if(vec[i]) primeNumbers.push_back(i);
    }
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> primeNumbers;

    SerchPrimeNumbers(primeNumbers, n);

    for(auto to : primeNumbers){
        std::cout << to << ' ';
    }
    std::cout << '\n';

    return 0;
}