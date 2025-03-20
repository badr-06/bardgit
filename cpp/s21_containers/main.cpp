#include <iostream>
#include <map>
#include <set>

int main() {

    std::map<int, char> mp;
    mp.insert({7, 'a'});
    mp.insert({5, 'b'});
    mp.insert({1, 'c'});;
    mp.insert({3, 'd'});
    mp.insert({8, 'e'});;
    mp.insert({10, 'f'});
    mp.insert({9, 'g'});

    auto it = mp.begin();

    it++;
    it++;
    it++;
    it++;

    std::cout << it->second << '\n';

    return 0;
}