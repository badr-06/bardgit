#include <iostream>
#include <vector>
#include <climits>
#include <set>

int main() {

    int N, M;
    std::cin >> N >> M;

    std::vector<int> students(N + 1);

    for(int i = 1; i <= N; ++i){
        std::cin >> students[i];
    }

    std::vector<int> computers(M + 1);

    for(int i = 1; i <= M; ++i){
        std::cin >> computers[i];
    }
    int P = 0;
    int flag = false;
    std::vector<int> res(N + 1, 0);
    std::set<int> ch;
    int min = INT_MAX;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(students[i]+1 <= computers[j]){

                if(computers[j] < min && (ch.find(j) == ch.end())){

                    if(res[i] != 0) ch.erase(res[i]);
                    res[i] = j;
                    min = computers[j];
                    ch.insert(j);
                    flag = true;
                }
            }
        }
        min = INT_MAX;
        if(flag){
            P++;
            flag = false;
        }
    }

    std::cout << P << '\n';
    for(int i = 1; i <= N; ++i){
        std::cout << res[i] << ' ';
    }


    return 0;
}