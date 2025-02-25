#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> a(N);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    std::unordered_map<int, int> remainders;
    remainders[0] = -1;
    int res = -1, ibest = 0, jbest = 0;

    int perfix_sum = 0;
    for(int i = 0; i < N; ++i)
    {
        perfix_sum += a[i];

        int mod = (perfix_sum % 3 + 3) % 3;
        
        if(remainders.find(mod) != remainders.end())
        {
            int start = remainders[mod] + 1;
            int length = i - start + 1;
            if(length > res)
            {
                res = length;
                ibest = start;
                jbest = i;
            }
        }
        else
        {
            remainders[mod] = i;
        }
    }

    if(res == -1)
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        std::cout << ibest + 1 << " " << jbest + 1 << std::endl;
    }

    return 0;
}
