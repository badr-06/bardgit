#include <iostream>
#include <vector>

int main(){

    int n;
    long t[40][4] = {0};
    t[0][0] = 1;
    t[0][1] = 1;
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
    t[i][0] = t[i - 1][0] + t[i - 1][2];
    t[i][1] = t[i - 1][0] + t[i - 1][2];
    t[i][2] = t[i - 1][1] + t[i - 1][3];
    t[i][3] = t[i - 1][1];
    }
    std::cout << t[n - 1][0] + t[n - 1][1] + t[n - 1][2] + t[n - 1][3];
    return 0;
}
0
1

01
00
10
00

000
001
010
100
110
101
011
