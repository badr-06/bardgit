#include <iostream>
#include <map>

int main() {

    std::map<int, char> mp;

    mp.insert({1, 'a'});
    auto it = mp.begin();

    std::cout << it->second << '\n';

    return 0;
}