#include <iostream>
#include <limits>
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

    Node *sentinel;
    std::size_t length;

    class ListIterator
        {
        private:
            Node* current;
        public:
            ListIterator(Node* node) : current(node) {}

            T& operator*() { return current->data; }

            ListIterator operator++();
            ListIterator operator++(int);
            ListIterator operator--();
            ListIterator operator--(int);
            bool operator==(ListIterator it);
            bool operator!=(ListIterator it);

        };

    class constListIterator : public ListIterator
        {

        };

public:

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using Iterator = ListIterator;
    using const_iterator = constListIterator;
    using size_type = std::size_t;

    list();
    list(size_type n);
    list(std::initializer_list<value_type> const &items);
    list(const list &other);
    list(list &&l);
    ~list();
    list operator=(list &&l);

    void push_back(T data);
    void push_front(T data);
    void pop_back();
    void pop_front();
    void clear();
    size_type size() { return length; };
    size_type max_size() { return std::numeric_limits<size_type>::max() / sizeof(Node) / 2; };

    Iterator begin() { return Iterator(sentinel->pNext); }
    Iterator end() { return Iterator(sentinel); }
    Iterator begin() { return Iterator(sentinel->pNext); }
    Iterator end() { return Iterator(sentinel); }

    const_reference front() { return this->sentinel->pNext->data; }
    const_reference back() { return this->sentinel->pPrev->data; }


};

}

template <typename T>
s21::list<T>::list() : length(0)
{
    sentinel = new Node();
    sentinel->pNext = sentinel;
    sentinel->pPrev = sentinel;

}

template <typename T>
s21::list<T>::list(size_type n)
{
    for(int i = 0; i < n; ++i){
        this->push_back(0);
    }
}

template <typename T>
s21::list<T>::list(std::initializer_list<value_type> const &items) : length(0)
{
    sentinel = new Node();
    sentinel->pNext = sentinel;
    sentinel->pPrev = sentinel;
    
    for(auto it = items.begin(); it != items.end(); it++){
           this->push_back(*it);
    }   

}

template <typename T>
s21::list<T>::list(const list& other) : length(0)
{   
    
    for(auto it = other.begin(); it != other.end(); it++){
           this->push_back(*it);
    }   

}

template <typename T>
s21::list<T>::~list()
{
    clear();
    delete sentinel;
}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator++()
{
    current = current->pNext;
    return *this;
}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator++(int)
{
    ListIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator--()
{
    return ListIterator();
}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator--(int)
{
    return ListIterator();
}

template <typename T>
bool s21::list<T>::ListIterator::operator==(ListIterator other)
{
    return current == other.current;
}

template <typename T>
bool s21::list<T>::ListIterator::operator!=(ListIterator other)
{
    return this->current != other.current;
}

template <typename T>
void s21::list<T>::pop_back()
{
    if(length)
    {
        Node *del = sentinel->pPrev;
        sentinel->pPrev = del->pPrev;
        del->pPrev->pNext = sentinel;

        delete del;
        sentinel->data = (--length);
    } 
}

template <typename T>
void s21::list<T>::pop_front()
{
    if(length)
    {
        Node *del = sentinel->pNext;
        sentinel->pNext = del->pNext;
        del->pNext->pPrev = sentinel;

        delete del;
        sentinel->data = (--length);
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
void s21::list<T>::push_front(T data)
{
    if(this->length == 0)
    {
        Node* newNode = new Node(data, sentinel, sentinel);
        this->sentinel->pNext = newNode;
        this->sentinel->pPrev = newNode;
    }
    else
    {   
        Node *head = this->sentinel->pNext;

        Node *new_head = new Node(data, head, sentinel);
        sentinel->pNext = new_head;
        head->pPrev = new_head;
    }
    sentinel->data = (++length);
}

template <typename T>
inline void s21::list<T>::push_back(T data)
{

    if(this->length == 0)
    {
        Node* newNode = new Node(data, sentinel, sentinel);
        sentinel->pNext = newNode;
        sentinel->pPrev = newNode;
    } 
    else
    {

        Node *tail = this->sentinel->pPrev;

        Node *new_tail = new Node(data, sentinel, tail);
        sentinel->pPrev = new_tail;
        tail->pNext = new_tail;
        
    } 

    sentinel->data = (++length);
}


int main() {

    s21::list<int> list1 = {1, 2, 3};

    s21::list<int> list2(list1);


    // std::cout << *it << '\n';


    return 0;
}