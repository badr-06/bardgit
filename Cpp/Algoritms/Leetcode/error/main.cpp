#include <iostream>
#include <vector>
#include <iomanip> // для std::setprecision(), выводит знаки после запятой, соклько указал пользователь

int main(){

    int n;

    std::cin >> n;

    long double ai, bi, sum = 0;

    std::vector<long double> numbers(n);

    for(int i = 0; i < n; ++i){
        std::cin >> ai >> bi;

        ai /= 100;
        bi /= 100;
        numbers[i] = ai * bi;
        sum += ai * bi;
    }

    for(long double to : numbers){
        std::cout << std::setprecision(12) << to/sum << "\n";
    }

    return 0;
}