#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    auto convert(string s, int numRows) -> string {
        vector<string> strings(numRows);
        for(int j = 0; j < numRows; ++j){
            for(int i = 0; ((i * numRows) + j) < s.length(); ++i){
                strings[j] += s[i * numRows + j];
            }
        }
        std::string res;
        for(const auto str : strings){
            res += str;
        }

        return res;
    }
};

int main() {

    string str = "PAYPALISHIRING";
    int numRows = 3;
    Solution s;
    auto res = s.convert(str, numRows);

    std::cout << res;

    return 0;
}