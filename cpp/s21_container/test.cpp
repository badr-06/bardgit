#include <iostream>
// #include <list>
// #include "vector.hpp"

namespace s21 {
template <typename T>
class list 
{
public:
    list();
    ~list();

    void push_back(T data);
    unsigned size() { return length; }
    T& operator[](const int index);

private:

    class Node 
        {
        public:
            Node *adrNext;
            T data;

            Node(T data=T(), Node* adrNext=nullptr) 
            {
                this->data = data;
                this->adrNext = adrNext;
            }
        };

    Node *head;
    unsigned length;   

};
template <typename T>
T &list<T>::operator[](const int index)
{
    
}
}

template <typename T>
s21::list<T>::list()
{
    head = nullptr;
    length = 0;
}

template <typename T>
s21::list<T>::~list()
{

}

template <typename T>
inline void s21::list<T>::push_back(T data)
{

    if(head == nullptr)
    {
        head = new Node(data);
    } 
    else
    {
        Node *new_head = this->head;

        while(new_head->adrNext != nullptr)
        {
             new_head = new_head->adrNext;
        }
        new_head->adrNext = new Node(data);

    } 

    length++;
}


int main() {

    s21::list<int> lst;

    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);

    std::cout << lst.size() << std::endl;

    return 0;
}