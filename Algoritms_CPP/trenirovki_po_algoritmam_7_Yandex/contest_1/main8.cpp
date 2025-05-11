#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {

    int n;
    std::cin >> n;

    std::vector<std::string> str(n);
    for(int i = 0; i < n; ++i){
        std::cin >> str[i];
    }

    std::vector<std::string> all_str1(n);
    std::vector<std::string> all_str2(n);

    int current_day = 0, max_day = 0, day = 1;
    for(int i = 0, l = n-1; i < n; ++i, --l){
        all_str1[i] = str[i];
        all_str2[i] = str[l];
        for(int j = 0, k = n-1; j < n; ++j, --k){
            if(i != j) all_str1[i] += str[j];
            if(l != k) all_str2[i] += str[k]; 
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < all_str1[i].length(); ++j){
            if(all_str1[i][j] == 'S' && day % 2 != 0) {
                current_day++;
            }
            day++;
        }
        if(current_day > max_day){
            max_day = current_day;
        }
        day = 1;
        current_day = 0;
    }

    int current_day2 = 0;
    day = 1;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < all_str2[i].length(); ++j){
            if(all_str2[i][j] == 'S' && day % 2 != 0) {
                current_day2++;
            }
            day++;
        }
        if(current_day2 > max_day){
            max_day = current_day2;
        }
        current_day2 = 0;
        day = 1;
    }


    std::cout << max_day << '\n';

    return 0;
}
