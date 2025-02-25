#include <iostream>
#include <map>

int main() {

    std::map<int, char> mp;

    auto iter = mp.begin();
    iter++;
    iter++;
    std::cout << iter->first << '\n';

    return 0;
}