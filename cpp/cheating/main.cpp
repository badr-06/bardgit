#include <iostream>
#include <vector>

int dfs(int v, std::vector<std::vector<int>> &graph, std::vector<int> &visit, int color)
{
    visit[v] = color;
    for(int to : graph[v]){
        if(visit[to] == -1){
          if(dfs(to, graph, visit, 3 - color)) {
            return 1;
          }
        }
        else if(visit[to] == visit[v]){
            return 1;
        }
    }

    return 0;
}

int main() {

    int N, M, error = 0;
    std::cin >> N >> M;

    std::vector<std::vector<int>> par_students(N + 1);

    for(int i = 0; i < M; ++i){
        int a, b;
        std::cin >> a >> b;
        par_students[a].push_back(b);
        par_students[b].push_back(a);
    }

    std::vector<int> visit(N + 1, -1);

    for(int i = 1; i <= N; ++i){
        if(visit[i] == -1)
        error = dfs(i, par_students, visit, 1);
        
        if(error) break;
    }
    if(!error){ std::cout << "YES" << std::endl; }
    else{ std::cout << "NO" << std::endl; }


    return 0;
}