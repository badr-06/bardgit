#include <iostream>
#include <vector>
#include <bitset>

const int MAX_N = 5000; 

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::vector<std::bitset<MAX_N>> yz(N), xz(N), xy(N);

    for (int i = 0; i < K; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        --x; --y; --z;
        yz[y][z] = 1;
        xz[x][z] = 1;
        xy[x][y] = 1;
    }

    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            if (xy[x][y]) continue; 
            for (int z = 0; z < N; ++z) {
                if (!xz[x][z] && !yz[y][z]) {
                    std::cout << "NO\n";
                    std::cout << x + 1 << ' ' << y + 1 << ' ' << z + 1 << '\n';
                    return 0;
                }
            }
        }
    }

    std::cout << "YES\n";
}
