#include <iostream>
#include <vector>
#include <map>

int main() {

    int n, m;
    std::cin >> n >> m;

    std::string str;
    std::cin >> str;

    std::vector<std::string> vect(m);
    std::multimap<std::string, int> substring;
    for(int i = 0; i < m; ++i){
        std::cin >> vect[i];
        substring.insert({vect[i], i+1});
    }

    int size = n/m;
    int start_i = 0;
    std::vector<int> a;
    a.reserve(m);
    
    while(start_i < str.length()){
        std::string s = str.substr(start_i, size);
        auto it = substring.find(s);
        a.push_back(it->second);
        substring.erase(it);
        start_i += size;
    }

    for(auto to : a){
        std::cout << to << ' ';
    }
    std::cout << std::endl;

    return 0;
}