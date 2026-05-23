#include <iostream>
#include <vector>
#include <cmath>

void SearchPrimeNumbers(std::vector<int>& primeNumbers, const int n)
{
    std::vector<bool> vec(n, true);

    vec[0] = vec[1] = false;

    for(int i = 2; i <= sqrt(n); ++i){
        for(int j = i * i; j <= n; j+=i){
            vec[j] = false;
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

    if(n < 2) {
        std::cout << 0 << '\n';
        return 0;
    }

    std::vector<int> primeNumbers;

    SearchPrimeNumbers(primeNumbers, n);

    for(auto to : primeNumbers){
        std::cout << to << ' ';
    }
    std::cout << '\n';

    return 0;
}