#include <iostream>
// #include <list>
// #include "vector.hpp"

namespace s21 {
template <typename T>
class list 
{

private:

    class Node 
        {
        public:
            Node *pNext;
            Node *pPrev;
            T data;

            Node(T data=T(), Node* pNext=nullptr, Node* pPrev=nullptr) 
            {
                this->data = data;
                this->pNext = pNext;
                this->pPrev = pPrev;
            }
        };

    Node *head;
    Node *tail;
    unsigned length;   

    class ListIterator
        {
        private:
            Node* current;
        public:
            ListIterator(Node* node) : current(node) {}

            T& operator*() { return current->data; }

            ListIterator operator++();

        };

public:

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using Iterator = ListIterator;
    // using const_iterator = constListIterator;
    using size_type = size_t;

    list();
    ~list();

    void push_back(T data);
    void push_front(T data);
    void pop_back();
    void pop_front();
    void clear();
    unsigned size() { return length; };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }


};

}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator++()
{
    current = current->pNext;
    return *this;
}

template <typename T>
void s21::list<T>::pop_back()
{
    if(tail)
    {
        if(tail->pPrev == nullptr)
        {
            delete tail;
            this->head = nullptr;
            this->tail = nullptr;
        }
        else
        {
            Node* del_tail = this->tail;
            tail = del_tail->pPrev;
            delete del_tail;
            tail->pNext = nullptr;
        }
    length--;
    } 
}

template <typename T>
void s21::list<T>::pop_front()
{
   if(head)
    {
        if(head->pNext == nullptr)
        {
            delete head;
            this->head = nullptr;
            this->tail = nullptr;
        }
        else
        {
            Node* del_head = this->head;
            head = del_head->pNext;
            delete del_head;
            head->pPrev = nullptr;
        }
    length--;
    } 
}

template <typename T>
void s21::list<T>::clear()
{
    while(length)
    {
        this->pop_back();
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
    clear();
}

template <typename T>
void s21::list<T>::push_front(T data)
{
    if(head == nullptr)
    {
        head = tail = new Node(data);
    }
    else
    {   
        if(length == 1)
        {
            tail->pPrev = head = new Node(data, tail);
        }
        else
        {
        Node* new_head = this->head;
        new_head->pPrev = head = new Node(data, new_head);
        }
    }
    length++;
}

template <typename T>
inline void s21::list<T>::push_back(T data)
{

    if(head == nullptr)
    {
        tail = head = new Node(data);
    } 
    else
    {

        Node *new_tail = this->tail;

        new_tail->pNext = tail = new Node(data, nullptr, new_tail);
        
    } 

    length++;
}


int main() {

    s21::list<int> lst;

    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);

    s21::list<int>::Iterator it = lst.begin();
    auto i = ++it;
    ++it;

    std::cout << *it << std::endl;
    std::cout << *i << std::endl;
    std::cout << lst.size() << std::endl;

    return 0;
}