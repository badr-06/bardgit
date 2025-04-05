#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>

int main(){

    int n, k;
    std::cin >> n >> k;

    std::unordered_set<int> sorts;

    while (k)
    {
        sorts.insert(k);
        k -= 1;
    }
    

    std::vector<int> trees(n);

    for(int i = 0; i < n; ++i){
        std::cin >> trees[i];
    }

    std::unordered_map<int, int> window_count;
    bool flag = true;
    int i = 0, j = 0;
    int ibest = 0, jbest = 0; 
    int size = 0;
    int length = INT_MAX;
    
    while(flag){
        int temp = trees[j];

        window_count[temp]++;

        if(sorts.count(temp) > 0 && window_count[temp] == 1){
            size++;
        }    

        while(size == sorts.size())
        {
            int temp_length = j - i;
            if(temp_length < length){
                ibest = i;
                jbest = j;
                length = temp_length;
            }

            int a = trees[i];
            window_count[a]--;
            
            if(sorts.count(a) > 0 && window_count[a] == 0){
                size--;
            }

            i++;
        }
        if(j == n-1) flag = false;
        else j++;
    }

    std::cout << ibest + 1 << " " << jbest + 1 << '\n';

    return 0;
}