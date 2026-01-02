#include <iostream>
#include <vector>

int main() {

    int size, money;

    std::cin >> size >> money;

    std::vector<int> a(size), b(size);

    for(int i = 0; i < size; ++i){
        std::cin >> a[i];
    }

    for(int i = 0; i < size; ++i){
        std::cin >> b[i];
    }

    int i_min = 0;
    int i_best = -1;
    int j_best = -1;
    long long max_money = money;

    for(int j = 1; j < size; ++j){
      
       if(a[j - 1] < a[i_min]){
        i_min = j - 1;
       }

       if(b[j] > a[i_min]){
            long long current = money / a[i_min];
            long long new_money = current * b[j] + (money % a[i_min]);

            if(new_money > max_money){
                max_money = new_money;
                j_best = j + 1;
                i_best = i_min + 1;
            }
       }
    }

    if(j_best != -1){
        std::cout << max_money << '\n' << i_best << " " << j_best << std::endl;
    } else {
        std::cout << money << '\n' << i_best << " " << j_best << std::endl;
    }

    return 0;
}