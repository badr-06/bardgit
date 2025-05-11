#include <iostream>
#include <vector>
#include <deque>

struct Node
    {
        int value;
        int index;
        bool alive;
        Node* pNext;
        Node* pPrev;
        
        Node(int val = int(), int idx = -1, Node* pN = nullptr, Node* pP = nullptr, bool al = true){
            value = val;
            pNext = pN;
            pPrev = pP;
            index = idx;
            alive = al;
        }
};

int main(){

    int n;
    std::cin >> n;
    std::vector<Node*> nodes(n);

    int x;
    for(int i = 0; i < n; ++i){
        std::cin >> x;
        nodes[i] = new Node(x, i);
    }

    for(int i = 0; i < n; ++i){
        nodes[i]->pPrev = nodes[(i - 1 + n) % n];
        nodes[i]->pNext = nodes[(i + 1) % n];
    }

    std::deque<Node*> to_delete;
    for(int i = 0; i < n; ++i){
        if(nodes[i]->value < nodes[i]->pPrev->value && nodes[i]->value < nodes[i]->pNext->value){
            to_delete.push_back(nodes[i]);
        }
    }

    std::vector<int> result(n, 0);
    int alive_cnt = n;
    int round = 1;
    while(!to_delete.empty() && alive_cnt > 2){
        
        std::deque<Node*> next_to_delete;
        while(!to_delete.empty()){

            Node* node = to_delete.front(); 
            to_delete.pop_front();

            if(!node->alive) continue;

            node->alive = false;
            alive_cnt--;
            result[node->index] = round;

            Node* L = node->pPrev;
            Node* R = node->pNext;

            L->pNext = R;
            R->pPrev = L;

            for(Node* temp : {L, R}){
                if(temp->value < temp->pPrev->value && temp->value < temp->pNext->value){
                    next_to_delete.push_back(temp);
                }
            }
        }

        round++;
        to_delete.swap(next_to_delete);
    }

    for(auto to : result){
        std::cout << to << ' ';
    }
    std::cout << '\n';
    
    for(int i = 0; i < n; ++i){
        delete nodes[i];
    }

    return 0;
}