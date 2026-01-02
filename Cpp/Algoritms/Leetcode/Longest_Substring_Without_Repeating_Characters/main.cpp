#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int size_str = s.length();
        if(size_str == 0) return 0;
        else if(size_str == 1) return 1;


        unordered_set<char> visit;
        visit.reserve(size_str);
        visit.insert(s[0]);

        int size = 1, lptr = 0, rptr = 1, max_size = 1;
        while(rptr < size_str){
            if(visit.contains(s[rptr])){

                while (visit.contains(s[rptr]))
                {
                    visit.erase(s[lptr]);
                    ++lptr;
                    --size;
                }
                
            }

            else {
                visit.insert(s[rptr]);
                ++size;

                if(size > max_size) max_size = size;
                ++rptr;
            }

        }

        return max_size;

    }
};

int main(){
    string str;
    getline(cin, str);
    Solution s;
    cout << s.lengthOfLongestSubstring(str) << '\n';
    
}