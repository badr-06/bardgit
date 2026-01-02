#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestPalindrome(string str) {
        int size_str = str.length();
        if(size_str == 1) return str;

        int max_size = 0;
        std::string res;
        for(int j = 1; j <= size_str; ++j){
            

            string s = str.substr(0, j);
        
            if(isCheck(s)){
                if(max_size < s.length()){
                    max_size = s.length();
                    res = s;
                }
                
            }

            int size_s = s.length();
            for(int i = 0; i < size_s - 1 && max_size < s.length(); ++i){
            
            if(max_size >= s.length()) break;

            s.erase(0, 1);
            if(isCheck(s)){
                if(max_size < s.length()){
                    max_size = s.length();
                    res = s;
                }
                
            }
            
        }
    }

        return res;
    }



    bool isCheck(string& s){
        int size_str = s.length();
        if(size_str == 1) return true;

        int i = 0, j = size_str - 1;

        while(j > i){
            if(s[i] != s[j]) return false;
            ++i;
            --j;
        }


        return true;
    }
};

int main(){
    string str;
    getline(cin, str);
    Solution s;
    cout << s.longestPalindrome(str) << '\n';
}