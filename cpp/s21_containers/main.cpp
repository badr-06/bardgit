#include <iostream>
#include <map>

int main() {

    std::map<int, char> mp;
    mp.emplace(1, 'a');
    mp.emplace(2, 'b');
    mp.emplace(3, 'c');
    

    auto iter = mp.begin();
    iter++;
    iter++;
    iter++;
    iter++;
    iter--;
    std::cout << iter->second << '\n';

    return 0;
}