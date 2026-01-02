#include <iostream>
#include <vector>

class Solution {
public:
    bool isPalindrome(int x) {
        
        if(x < 0) return false;

        std::vector<int> numbers;
        int temp = x;
        
        while (temp != 0)
        {
            numbers.push_back(temp % 10);
            temp /= 10;
        }

        for(int i = numbers.size() - 1; i >= 0; --i)
        {
            if((x % 10) != numbers[i]) return false;
            x /= 10;
        }

        return true;
        
    }
};

int main(){

    int x;
    std::cin >> x;
    Solution S;
    std::cout << S.isPalindrome(x) << '\n';


}

