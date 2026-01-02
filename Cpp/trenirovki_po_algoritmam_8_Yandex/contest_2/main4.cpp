#include <iostream>
#include <vector>
#include <unordered_set>

int main(){

    std::string str;
    std::cin >> str;

    int n;
    std::cin >> n;
    std::unordered_set<std::string> substrings;

    for(int i = 0; i < n; ++i){
        std::string s;
        std::cin >> s;
        substrings.insert(s);
    }

    std::vector<bool> dp(str.length()+1, false);
    std::vector<int> prev(str.length()+1, -1);
    dp[0] = true;
    prev[0] = 0;
    for(int i = 1; i <= str.length(); ++i){
        for(int j = 1; j <= 20 && j <= i; ++j){
            int start = i - j;
            std::string word = str.substr(start, j);

            if(substrings.contains(word) && (dp[start] == true)){
                dp[i] = true;
                prev[i] = j;
                break;
            }
        }
    }

    std::vector<std::string> result;
    int pos = str.length();
    while(pos > 0)
    {
        int word_len = prev[pos];
        result.push_back(str.substr(pos - word_len, word_len));
        pos -= word_len;
    }

    for(int i = result.size() - 1; i >= 0; --i){
        std::cout << result[i] << ' ';
    }

    return 0;
}