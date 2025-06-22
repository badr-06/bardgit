#include <iostream>
#include <vector>

void dfs(int v, std::vector<int> &visited, std::vector<std::vector<int>> &graph)
{ 
    visited[v] = 1;
    for(int to : graph[v]) {
        if(!visited[to]){
            dfs(to, visited, graph);
        }
    }

}


int main() {

    int N, M;

    std::cin >> N >> M;

    std::vector<std::vector<int>> graph(N + 1);

    int x, y;
    for(int i = 0; i < M; ++i){
        std::cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    std::vector<int> visited(N + 1, 0);
    dfs(1, visited, graph);

    std::vector<int> date;
    for(int i = 0; i < visited.size(); ++i){
        if(visited[i]){
            date.push_back(i);
        }
    }

    std::cout << date.size() << std::endl;
    for(int to : date){
        std::cout << to << ' ';
    }
    std::cout << std::endl;


}