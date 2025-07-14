#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>

int closed_key(long long x, long long y)
{

    unsigned long long d = y / x;

    std::vector<unsigned long long> divisors;

    for(int i = 1; i <= sqrt(d); ++i){
        if(d % i == 0){
            divisors.push_back(i);
        }
    }

    int count = 0;
    for(unsigned long long k : divisors){
        unsigned long long m = d / k;

        unsigned long long p1 = k * x;
        unsigned long long q1 = m * x;

        if(std::gcd(p1, q1) == x && std::lcm(p1, q1) == y){
            count++;
        } 

        if(q1 != p1 && std::gcd(q1, p1) == x && std::lcm(q1, p1) == y){
            count++;
        }
    }

    return count;
}

int main() {

    long long x, y;

    std::cin >> x >> y;

    std::cout << closed_key(x, y) << std::endl;

    return 0;
}