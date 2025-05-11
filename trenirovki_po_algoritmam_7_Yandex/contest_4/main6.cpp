#include <iostream>
#include <vector>

void dfs(int v, std::vector<int>& to, std::vector<bool>& visited, std::vector<int>& in_stack, int& res){
    visited[v] = true;
    in_stack[v] = true;


    int u = to[v];
    if(!visited[u]){
        dfs(u, to, visited, in_stack, res);
    } else if(in_stack[u]){
        res++;
    }

    in_stack[v] = false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> to(n + 1);
    std::vector<bool> visited(n + 1, false); 
    std::vector<int> in_stack(n + 1, 0); 

    for (int i = 1; i <= n; ++i) {
        std::cin >> to[i];
    }

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, to, visited, in_stack, result);
        }
    }

    std::cout << result << '\n';
    return 0;
}
