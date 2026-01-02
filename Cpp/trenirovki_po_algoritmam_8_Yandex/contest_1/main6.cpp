#include <iostream>
#include <vector>

int main() {

    int n, m;
    std::cin >> n >> m;
    int max_r = -m, max_c = -n;
    std::vector<std::string> vect(n);
    int index = 0;
    int min_vopros = 0;

    for(int i = 0; i < n; ++i){
        std::cin >> vect[i];
        int r = 0;
        int c = 0;
        int min_v = 0;
        for(int j = 0; j < m; ++j){
            if(vect[i][j] == '+' || vect[i][j] == '?'){
                if(vect[i][j] == '?') min_v++;
                r++;
            } else{
                c++;
            }
            
        }
        r -= c;
        if(r > max_r){
            max_r = r;
            index = i;
            min_vopros = min_v;
        }
        else if(r == max_r && min_v < min_vopros){
            index = i;
            min_vopros = min_v;
        }
    }

    for(int i = 0; i < m; ++i){
        int c = 0;
        for(int j = 0; j < n; ++j){
            if(vect[j][i] == '-' || vect[j][i] == '?' && j != index){
                c++;
            }
        }
        int temp = n - c;
        c -= temp;
        max_c = std::max(max_c, c); 
    }

    std::cout << max_r + max_c << std::endl;



    return 0;
}