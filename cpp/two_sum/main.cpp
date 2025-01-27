#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        for(int i = 0; i < nums.size(); ++i){
            int x = target - nums[i];
            if(hash.find(x) != hash.end()){
                return {hash[x], i};
            }
            else {
                hash.emplace(nums[i], i);
            }
        }
        return {0, 0};
    }
};

int main(){

    Solution clacc;
    vector<int> nums;
    int num, size;
    cin >> size;

    for(int i = 0; i < size; ++i)
    {
        cin >> num;
        nums.push_back(num);
    }

    int target;
    cin >> target;

    vector<int> array = clacc.twoSum(nums, target);

    cout << array[0] << " " << array[1] << endl;    

    return 0;
}