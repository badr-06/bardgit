#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void dfs(int v, std::vector<std::vector<int>> &graph, std::vector<int> &visited, std::vector<int> &component)
{
    visited[v] = true;
    component.push_back(v);
    for(int to : graph[v]){
        if(!visited[to]){
            dfs(to, graph, visited, component);
        }
    }

}

int main() 
{
    int N, M;

    std::cin >> N >> M;

    std::vector<std::vector<int>> graph(N + 1);

    int a, b;
    for(int i = 0; i < M; ++i){
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> visited(N + 1, 0);
    std::vector<std::vector<int>> components;

    int flag = 0;
    for(int i = 1; i <= N; ++i){
        if(!visited[i]){
        std::vector<int> component;
        dfs(i, graph, visited, component);
        components.push_back(component);
        }
    }


    std::cout << "количество комонентов связанности: " << components.size() << std::endl;
    for(int i = 0; i < components.size(); ++i){
        std::sort(components[i].begin(), components[i].end());
        std::cout << components[i].size() << std::endl;
        for(int to : components[i]){
            std::cout << to << ' ';
        }
        std::cout << std::endl;
    }


	return 0;
}