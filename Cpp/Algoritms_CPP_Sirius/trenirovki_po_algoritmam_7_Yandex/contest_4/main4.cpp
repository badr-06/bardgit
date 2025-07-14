#include <iostream>

class mylist{
private:    
    struct Node
    {
        std::string str;
        Node* pNext;
        Node* pPrev;
        
        Node(std::string s = "", Node* pN = nullptr, Node* pP = nullptr){
            str = s;
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

    void push_back(std::string str){

        if(!lentgh){
            head = new Node(str);
            tail = head;
        }
        else if(lentgh == 1){
            tail = new Node(str, nullptr, head);
            head->pNext = tail;
        }
        else{
            Node* newNode = new Node(str, nullptr, tail);
            tail->pNext = newNode;
            tail = newNode;
        }
        lentgh++;
    }
    std::string push_front(std::string str){

        if(!lentgh){
            head = new Node(str);
            tail = head;
        }
        else if(lentgh == 1){
            head = new Node(str, tail, nullptr);
            tail->pPrev = head;
        }
        else{
            Node* newNode = new Node(str, head, nullptr);
            head->pPrev = newNode;
            head = newNode;
        }
        
        lentgh++;
        return head->str;
    }

    void pop_front(){
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
    void pop_back(){
        if(lentgh == 0) return;

        if(lentgh == 1){
            delete head;
            tail = nullptr;
        }
        else if(lentgh > 1){
            Node* temp = tail;
            tail = temp->pPrev;
            tail->pNext = nullptr;
            delete temp;
        }  
        --lentgh;   
    }
    std::string run(int n){
        Node* newNode = head;
        for(int i = 1; i < n; ++i){
            newNode = newNode->pNext;
        }

        if (newNode == tail && newNode != head)
        {
            tail = newNode->pPrev;
            tail->pNext = nullptr;
            
            head->pPrev = newNode;
            newNode->pNext = head;
            newNode->pPrev = nullptr;

            head = newNode;
        } else if(newNode != head) {
            newNode->pNext->pPrev = newNode->pPrev;
            newNode->pPrev->pNext = newNode->pNext;

            head->pPrev = newNode;
            newNode->pNext = head;
            newNode->pPrev = nullptr;

            head = newNode;
        }
        
        return head->str;
    }
    
    size_t size(){
        return lentgh;
    }
    void clear(){
        while(lentgh){
            pop_back();
        }
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    mylist ls;

    while(n--) 
    {
        std::string str;
        std::cin >> str;
        if(str == "Run"){
            std::string s;
            std::getline(std::cin, s);
            s.erase(0, 1);
            std::cout << ls.push_front(s) << '\n';
        }
        else{
            int x = 0;
            for(size_t i = 3; i < str.size(); i+=4){
                if(str[i] == '+') x++;
            }

            std::cout << ls.run(x % ls.size() + 1) << '\n';
        }

    }
    

    return 0;
}