#include <iostream>
#include <vector>
#include <map>
#include <set>

int main() {

    int n,  k;

    std::cin >> k >> n;

    std::vector<int> tasks;
    std::map<int, int> map_;

    for(int i = 0; i < k; ++i){
        int x;
        std::cin >> x;
        map_[x]++;
    }

    int idx = 1;
    int size = 0;
    while (size < n)
    {
        for(auto [a, b] : map_){
            if(b >= idx){
                tasks.push_back(a);
                size++;
                if(size >= n) break;
            }
        }
        idx++;
    }
    for(auto to : tasks){
        std::cout << to << ' ';
    }
    std::cout << std::endl;

    

    return 0;
}