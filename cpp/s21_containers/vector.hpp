#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace s21 {
template <typename T>
class list 
{
public:
    list();
    ~list();

    void push_back(T data);

private:

    template <typename T>
    class Node 
        {
        public:
            Node *adrNext;
            T data;

            Node(T data(T()), Node* adrNext(nullptr)) 
            {
                this->data = data;
                this->adrNext = adrNext;
            }
        };

    Node<T> *head;
    unsigned Size;   

};

}

template <typename T>
s21::list<T>::list()
{
    head = nullptr;
    Size = 0;
}

template <typename T>
s21::list<T>::~list()
{

}

template <typename T>
inline void s21::list<T>::push_back(T data)
{
    Node<T> *new_head = new Node<T>(data);

    if(new_head->adrNext == nullptr)
    {
        head = new_head;
    } 
    else
    {

    } 

}

#endif