#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>

int main() {

    int N;
    std::cin >> N;
    while(N--){
        size_t size;
        std::cin >> size;
        std::vector<int> numbers;
        int a;
        for(size_t i = 0; i < size; ++i){
            std::cin >> a;
            numbers.push_back(a);
        }

        size_t start = 0;
        std::vector<int> segments;
        while(start < size){
            
            size_t max_len = 1;
            int current_min = numbers[start];

            for(size_t len = 1; len <= size - start; ++len){
                current_min = std::min(current_min, numbers[len + start - 1]);
                if(current_min >= static_cast<int>(len)){
                    max_len = len;
                } else {
                    break;
                }
            }
            segments.push_back(static_cast<int>(max_len));
            start += max_len;
        }

        std::cout << segments.size() << '\n';
        for(int to : segments){
            std::cout << to << ' ';
        }
        std::cout << std::endl;

    }

    return 0;
}