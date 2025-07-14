#include <iostream>
#include <bits/stdc++.h>

long long sum(std::vector<std::vector<std::vector<long long>>>&  t, int x, int y, int z) {
    if(x < 0 || y < 0 || z < 0) return 0;

    long long result = 0;

    for (int xi = x; xi >= 0; xi = (xi & (xi + 1)) - 1) {
        for(int yi = y; yi >= 0; yi = (yi & (yi + 1)) - 1){
            for(int zi = z; zi >= 0; zi = (zi & (zi + 1)) - 1){
                result += t[xi][yi][zi];
            }
        }    
    }

    return result;
}

long long sum(std::vector<std::vector<std::vector<long long>>>&  t, int x1, int y1, int z1, int x2, int y2, int z2) {

    return sum(t, x2, y2, z2) - sum(t, x1 - 1, y2, z2) - sum(t, x2, y1 - 1, z2) - sum(t, x2, y2, z1 - 1) + 
            sum(t, x1 - 1, y1 - 1, z2) + sum(t, x1 - 1, y2, z1 - 1) + sum(t, x2, y1 - 1, z1 - 1) - sum(t, x1 - 1, y1 - 1, z1 - 1);
 
}   

void update(std::vector<std::vector<std::vector<long long>>>& t, int x, int y, int z, int val, int n){
    for(int xi = x; xi < n; xi |= xi + 1){
        for(int yi = y; yi < n; yi |= yi + 1){
            for(int zi = z; zi < n; zi |= zi + 1){
                t[xi][yi][zi] += val;
            }
        }      
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<std::vector<long long>>> t(n, std::vector<std::vector<long long>>(n, std::vector<long long>(n, 0)));

    std::vector<long long> res;
    
    int ch;
    do {
        std::cin >> ch;

        if(ch == 1){
            int x, y, z, val;
            std::cin >> x >> y >> z >> val;
            update(t, x, y, z, val, n);
        } else if(ch == 2){
            int x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            res.push_back(sum(t, x1, y1, z1, x2, y2, z2));
        } else if(ch == 3){
            break;
        }
    } while(ch != 3);

    for(auto to : res){
        std::cout << to << '\n';
    }

    return 0;   
}