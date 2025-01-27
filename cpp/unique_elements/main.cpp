#include <iostream>
#include <vector>
#include <map>

int main(){
    int n;
    int res = 0;

    std::cin >> n;

    std::vector<int> numbers(n);
    std::map<int, int> quantity_numbers;

    for(int i = 0; i < n; ++i){
        std::cin >> numbers[i];
        quantity_numbers[numbers[i]]++;
    }

    for(auto &[num, count] : quantity_numbers){
        if(count == 1) res++;
    }

    std::cout << res << '\n';

    return 0;
}