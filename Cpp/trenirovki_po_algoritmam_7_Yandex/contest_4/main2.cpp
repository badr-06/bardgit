#include <iostream>

class mylist{
private:    
    struct Node
    {
        long long value;
        Node* pNext;
        Node* pPrev;
        
        Node(long long val = long(), Node* pN = nullptr, Node* pP = nullptr){
            value = val;
            pNext = pN;
            pPrev = pP;
        }
    };

    Node* head;
    Node* tail;
    size_t lentgh;
public:
    mylist() {
        head = nullptr;
        tail = nullptr;
        lentgh = 0;
    }
    ~mylist() {
        clear();
    }

    void push(int n){
        if(!lentgh){
            head = new Node(n);
            tail = head;
        }
        else if(lentgh == 1){
            tail = new Node(n, nullptr, head);
            head->pNext = tail;
        }
        else{
            Node* newNode = new Node(n, nullptr, tail);
            tail->pNext = newNode;
            tail = newNode;
        }
        lentgh++;
    }
    void pop(){
        if(lentgh == 0) return;

        if(lentgh == 1){
            delete head;
            tail = nullptr;
        }
        else if(lentgh > 1){
            Node* temp = head;
            head = temp->pNext;
            head->pPrev = nullptr;
            delete temp;
        }  
        --lentgh;   
    }

    long long front (){
        return head->value;     
    }
    size_t size(){
        return lentgh;
    }
    void clear(){
        while(lentgh){
            pop();
        }
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    mylist ls;

    do 
    {
        std::cin >> str;
        if(str == "push"){
            long long n;
            std::cin >> n;
            ls.push(n);
            std::cout << "ok\n";
        } else if(str == "pop"){
            if(ls.size() == 0){
                std::cout << "error\n";
            } else {
                std::cout << ls.front() << '\n';
                ls.pop();
            }
             
        } else if(str == "front"){
            if(ls.size() == 0){
                std::cout << "error\n";
            } else {
            std::cout << ls.front() << '\n';
            }
        } else if(str == "size"){
            std::cout << ls.size() << '\n';
        } else if(str == "clear"){
            ls.clear();
            std::cout << "ok\n";
        }

    } while (str != "exit");
    
    std::cout << "bye\n";

    return 0;
}