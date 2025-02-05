#include <iostream>
#include <string>
#include <unordered_set>
#include <climits>

int main() {
    std::string s, c;
    std::cin >> s >> c;

    std::unordered_set<char> unique_c;

    for(char ch : c){
        unique_c.insert(ch);
    }

    unsigned long left, right, min_length = INT_MAX;


    for(left = 0; left < s.length(); ++left){
        std::unordered_set<char> window_count;        
        for(right = left; right < s.length(); ++right){
            char ch = s[right];
            window_count.insert(ch);

            if(window_count == unique_c)
            {
                min_length = std::min(min_length, (right - left) + 1);
            }
        }
    }

    if(min_length == INT_MAX){
    std::cout << 0 << std::endl;
    } else {
    std::cout << min_length << std::endl;
    }
}
