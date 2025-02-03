#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    int T;
    std::cin >> T;
    std::vector<int> res_numb(T);
        
    for(int i = 0; i < T; ++i){

        int n; // количество лежаков
        std::cin >> n;

        std::vector<int> numbers(n);

        for(int j = 0; j < n; ++j){
            std::cin >> numbers[j];
        }

        std::sort(numbers.begin(), numbers.end());

        res_numb[i] = numbers[0] ^ numbers[1];

        for(int l = 1, r = 2; r < n; ++l, ++r){
            if((numbers[l] ^ numbers[r]) < res_numb[i]){
                res_numb[i] = numbers[l] ^ numbers[r];
            }
        }

    }

    for(int to : res_numb){
        std::cout << to << std::endl;
    }

    return 0;
}