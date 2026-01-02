
#include <iostream>
#include <string>
#include <map>

int main() {

    long long n = 1;
    std::string password;
    std::cin >> password;
    std::map<char, long long> map_;

    const char* c = password.c_str();
    
    while (*c != '\0')
    {
        map_[*c]++;
        c++;
    }

    auto end_ = map_.end();
    for(auto it1 = map_.begin(); it1 != end_; ++it1){
        long long second_ = it1->second;
        auto it2 = it1;
        it2++;
        if(it2 == end_) break;

        long long s = 0;
        while (it2 != end_)
        {
            s += it2->second;
            it2++;
        }
        n += second_ * s;
        

    }

    std::cout << n << '\n';
    
}