#include <iostream>
#include <map>

int main() {

    std::map<int, char> mp;

    mp.insert({1, 'a'});
    auto it = mp.insert({2, 'a'});
    mp.emplace(1, 'a');

    std::cout << it.second << '\n';

    return 0;
}