#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Interval {
    double start, end, weight;
};

auto compareByEnd(const Interval& a, const Interval& b) -> bool
{
    return a.end < b.end;
}

auto find_peresec(const vector<Interval>& intervals, int current) -> int
{   


    double target = intervals[current].start;
    int left = 0, right = current - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if(intervals[mid].end <=  target){
            result = mid;
            left = mid + 1;
        } else {
            right = mid-1;
        }
    }
    
    return result;

}

int main() {
    int n;
    cin >> n;

    if(n == 0){
        std::cout << 0.0 << '\n';
        return 0;
    }

    vector<Interval> intervals(n);
    for(int i = 0; i < n; ++i){
        cin >> intervals[i].start >> intervals[i].end >> intervals[i].weight;
    }

    sort(intervals.begin(), intervals.end(), compareByEnd);
    
    vector<double> dp(n);
    dp[0] = intervals[0].weight;
    
    for(int i = 1; i < n; ++i){
        double exclude = dp[i-1];

        double include = intervals[i].weight;
        int prev = find_peresec(intervals, i);
        if(prev != -1){
            include += dp[prev];
        }

        dp[i] = std::max(include, exclude);
    }

    cout << dp[n-1] << endl;
    return 0;
}