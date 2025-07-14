#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int main() {
    int N;
    cin >> N;
    vector<int> cost(N + 1);
    for (int i = 1; i <= N; ++i)
        cin >> cost[i];

    vector<vector<int>> dp(N + 1, vector<int>(N + 2, INF));
    dp[0][0] = 0;

    for (int day = 1; day <= N; ++day) {
        for (int coupons = 0; coupons <= N; ++coupons) {
            if (dp[day - 1][coupons] == INF) continue;

            // Вариант 1: Покупаем обед
            int new_coupons = coupons + (cost[day] > 100 ? 1 : 0);
            if (new_coupons <= N)
                dp[day][new_coupons] = min(dp[day][new_coupons], dp[day - 1][coupons] + cost[day]);

            // Вариант 2: Используем купон (если есть)
            if (coupons > 0)
                dp[day][coupons - 1] = min(dp[day][coupons - 1], dp[day - 1][coupons]);
        }
    }

    // Находим минимальную стоимость и best_j
    int min_cost = INF, best_j = 0;
    for (int j = 0; j <= N; ++j) {
        if (dp[N][j] <= min_cost) {
            min_cost = dp[N][j];
            best_j = j;
        }
    }

    // Восстанавливаем дни, когда использовались купоны
    vector<int> used_days;
    int current_j = best_j;
    for (int day = N; day >= 1; --day) {
        if (current_j < N && dp[day][current_j] == dp[day - 1][current_j + 1]) {
            used_days.push_back(day);
            current_j++;
        }
    }
    reverse(used_days.begin(), used_days.end());

    // Вывод
    cout << min_cost << endl;
    cout << best_j << " " << used_days.size() << endl;
    for (int day : used_days)
        cout << day << endl;

    return 0;
}