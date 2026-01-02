#include <iostream>
#include <vector>
#include <map>

int main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> vect(n);
    for(int i = 0; i < n; ++i){
        std::cin >> vect[i];
    }

    std::vector<std::vector<int>> dp_vert_x(n + 2, std::vector<int>(m + 2, 0));
    std::vector<std::vector<int>> dp_gorizont_x(n + 2, std::vector<int>(m + 2, 0));
    std::vector<std::vector<int>> dp_vert_o(n + 2, std::vector<int>(m + 2, 0));
    std::vector<std::vector<int>> dp_gorizont_o(n + 2, std::vector<int>(m + 2, 0));
    std::vector<std::vector<int>> dp_diag_x_left(n + 2, std::vector<int>(m + 2, 0));
    std::vector<std::vector<int>> dp_diag_x_right(n + 2, std::vector<int>(m + 2, 0));
    std::vector<std::vector<int>> dp_diag_o_left(n + 2, std::vector<int>(m + 2, 0));
    std::vector<std::vector<int>> dp_diag_o_right(n + 2, std::vector<int>(m + 2, 0));
    
    std::string res = "No";

    for(int i = 1; i <= n; ++i){
     int x1 = 0, x2 = 0, x3 = 0, x4;
     int o1 = 0, o2 = 0, o3 = 0, o4;
        for(int j = 1; j <= m; ++j){
            if(vect[i-1][j-1] == 'X'){
                x1 = dp_vert_x[i][j] = 1 + dp_vert_x[i-1][j];
                x2 = dp_gorizont_o[i][j] = 1 + dp_gorizont_o[i][j-1];
                x3 = dp_diag_x_left[i][j] = 1 + dp_diag_x_left[i-1][j+1];
                x4 = dp_diag_x_right[i][j] = 1 + dp_diag_x_right[i-1][j-1];
            }
            else if(vect[i-1][j-1] == 'O'){
                o1 = dp_vert_o[i][j] = 1 + dp_vert_o[i-1][j];
                o2 = dp_gorizont_o[i][j] = 1 + dp_gorizont_o[i][j-1];
                o3 = dp_diag_o_left[i][j] = 1 + dp_diag_o_left[i-1][j+1];
                o4 = dp_diag_o_right[i][j] = 1 + dp_diag_o_right[i-1][j-1];
            }
        }
        if(x1 >= 5 || x2 >= 5 || x3 >= 5 || x4 >= 5 || o1 >= 5 || o2 >= 5 || o3 >= 5 || o4 >= 5){
            res = "Yes";
            break;
        }
    }

    std::cout << res << '\n';

    return 0;
}