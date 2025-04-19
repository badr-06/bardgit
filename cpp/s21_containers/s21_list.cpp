#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list 
{

protected:

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
    
    template <typename reference>
    class ListIteratorBase
        {
        protected:
            Node* current;
        
        public:

            friend class list<T>;

            ListIteratorBase(Node* node) : current(node) {}

            reference operator*() const { return current->data; }

            ListIteratorBase operator++(){
                current = current->pNext;
                return *this;
            }

            ListIteratorBase operator++(int){
                ListIteratorBase temp = *this;
                ++(*this);
                return temp;
            }

            ListIteratorBase operator--(){
                current = current->pPrev;
                return *this;
            }

            ListIteratorBase operator--(int){
                ListIteratorBase temp = *this;
                --(*this);
                return temp;
            }

            bool operator==(const ListIteratorBase& other) const { return current->data == other.current->data; }
            bool operator!=(const ListIteratorBase& other) const { return current != other.current; }

        };

    class ListIterator : public ListIteratorBase<T&>
        {
            public:
                using ListIteratorBase<T&>::ListIteratorBase;
        };

    class constListIterator : public ListIteratorBase<const T&>
        {
            public:
                using ListIteratorBase<const T&>::ListIteratorBase;

                constListIterator(const ListIterator& iterator) : ListIteratorBase<const T&>(iterator.current) {}
        };

public:

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ListIterator;
    using const_iterator = constListIterator;
    using size_type = std::size_t;

    list();
    list(size_type n);
    list(std::initializer_list<value_type> const &items);
    list(const list &other);
    list(list &&other);
    ~list();
    list operator=(list&& l);

    bool empty();
    size_type size() { return length; };
    size_type max_size() { return std::numeric_limits<size_type>::max() / sizeof(Node) / 2; };

    void clear();
    iterator insert(iterator pos, const_reference value);
    iterator erase(iterator pos);
    void push_back(value_type data);
    void push_front(value_type data);
    void pop_back();
    void pop_front();
    void swap(list& other);
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse();
    void unique();
    void sort();
    list merge_sort(list l1, list l2);
    Node* midNode(Node* head);
    list<value_type> sortList(Node* head);


    iterator begin() { return iterator(sentinel->pNext); }
    iterator end() { return iterator(sentinel); }

    const_iterator begin() const { return const_iterator(sentinel->pNext); }
    const_iterator end() const { return const_iterator(sentinel); }

    const_reference front() { return this->sentinel->pNext->data; }
    const_reference back() { return this->sentinel->pPrev->data; }

    void init_sentinel();

};

}

template <typename T>
s21::list<T>::list() : length(0)
{
    init_sentinel();
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
    init_sentinel();
    
    for(auto &it : items){
           this->push_back(it);
    }   

}

template <typename T>
s21::list<T>::list(const list& other) : length(0)
{   
    init_sentinel();   

    for(auto &it : other){
           this->push_back(it);
    }   

}

template <typename T>
s21::list<T>::list(list&& other) : length(0), sentinel(nullptr)
{   
    sentinel = other.sentinel;
    length = other.length;

    other.sentinel = nullptr;
    other.length = 0;
}

template <typename T>
s21::list<T> s21::list<T>::operator=(list&& l)
{   
    this->sentinel = l.sentinel;
    return *this;
}

template <typename T>
s21::list<T>::~list()
{
    clear();
    delete sentinel;
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
void s21::list<T>::swap(list& other)
{
    Node *newNode = other.sentinel;
    other.sentinel = this->sentinel;
    this->sentinel = newNode;

    size_type temp = other.length;
    other.length = this->length;
    this->length = temp;
}

template <typename T>
void s21::list<T>::merge(list& other)
{
    if(other.length){
        list<T> NewList = merge_sort(*this, other);
        other.clear();
        this->swap(NewList);
    }
}

template <typename T>
void s21::list<T>::splice(const_iterator pos, list& other)
{
    if(other.length)
    {
        Node *other_head = other.sentinel->pNext;
        Node *other_tail = other.sentinel->pPrev;

        Node *this_head = pos.current->pPrev;
        Node *this_tail = pos.current;

        this_head->pNext = other_head;
        other_head->pPrev = this_head;

        other_tail->pNext = this_tail;
        this_tail->pPrev = other_tail;

        this->sentinel->data = (this->length += other.length);  
        
        delete other.sentinel;

        other.init_sentinel();
        other.length = 0;
    }
}

// sentinel->5->2->sentinel | 2
template <typename T>
void s21::list<T>::reverse() {
    if (length <= 1) {
        return; // Ничего не делаем для пустого или одноэлементного списка
    }

    Node* head = sentinel->pNext;
    Node* tail = sentinel->pPrev;

    Node* current = head;
    Node* temp = nullptr;

    while(current != sentinel)
    {
        temp = current->pNext;
        current->pNext = current->pPrev;
        current->pPrev = temp;

        current = current->pPrev;
    }

    tail->pPrev = sentinel;
    head->pNext = sentinel;

    sentinel->pNext = tail;
    sentinel->pPrev = head;

}

template <typename T>
void s21::list<T>::unique() 
{
    if(length <= 1){
        return;
    }

    auto it2 = begin();
    it2++;

    for(auto it1 = begin(); it2 != end(); it1++, it2++)
    {
        while(it1 == it2 && length > 1)
        {
            it2 = erase(it2);
        }
    }

}

template <typename T>
void s21::list<T>::sort() 
{
    

    Node* head = sentinel->pNext;
    Node* tail = sentinel->pPrev;

    list<T> Newlist = sortList(head);

    this->swap(Newlist);
    Newlist.clear();
}

template <typename T>
typename s21::list<T> s21::list<T>::sortList(Node* head)
{

    if(head  == sentinel || head->pNext == sentinel){
        list<T> newlist;
        newlist.push_back(head->data);
        return newlist;
    }

    Node *mid = midNode(head);
    list<T> left = sortList(head);
    list<T> ritgh = sortList(mid);
    return merge_sort(left, ritgh);
    
}

template <typename T>
typename s21::list<T> s21::list<T>::merge_sort(list l1, list l2)
{
    list<T> NewList;
    auto it1 = l1.begin();
    auto it2 = l2.begin();

    while(it1 != l1.end() && it2 != l2.end()){
        if(*it1 <= *it2){
            NewList.push_back(*it1);
            it1++;
        }
        else {
            NewList.push_back(*it2);
            it2++;
        }
    }

    while(it1 != l1.end()){
        NewList.push_back(*it1);
        it1++;
    }
    while(it2 != l2.end()){
        NewList.push_back(*it2);
        it2++;
    }

    return NewList;
}

template <typename T>
typename s21::list<T>::Node* s21::list<T>::midNode(Node* head)
{
    Node* midPrev = head;
    head = head->pNext;

    while(head != sentinel && head->pNext != sentinel){
        midPrev = midPrev->pNext;
        head = head->pNext->pNext;
    }

    Node* mid = midPrev->pNext;
    midPrev->pNext = sentinel;
    return mid;
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
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos, const_reference value)
{
    Node *newNode = new Node(value);

    newNode->pNext = pos.current;
    newNode->pPrev = pos.current->pPrev;
    
    pos.current->pPrev->pNext = newNode;
    pos.current->pPrev = newNode;

    sentinel->data = (++length);
    return iterator(pos.current);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::erase(iterator pos)
{
    Node *newNode = pos.current;

    pos.current = newNode->pNext;

    pos.current->pNext = newNode->pNext->pNext;
    pos.current->pPrev = newNode->pPrev;

    newNode->pPrev->pNext = pos.current;

    newNode->pNext = nullptr;
    newNode->pPrev = nullptr;

    delete newNode;
    sentinel->data = (--length);
    return iterator(pos.current);
}

template <typename T>
bool s21::list<T>::empty()
{
    return length == 0 ? true : false;
}

template <typename T>
void s21::list<T>::init_sentinel()
{
    sentinel = new Node();
    sentinel->pNext = sentinel;
    sentinel->pPrev = sentinel;
}

template <typename T>
inline void s21::list<T>::push_front(T data)
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

    s21::list<int> list1 = {9, 2, 4, 6, 2};
    s21::list<int> list2 = {4, 2 , 3, 1, 7, 9};


    for(auto to : list1){
        std::cout << to << " ";
    }
    std::cout << '\n';

    for(auto to : list2){
        std::cout << to << " ";
    }
    std::cout << '\n';

    list1.merge(list2);

    for(auto to : list1){
        std::cout << to << " ";
    }
    std::cout << '\n';

    for(auto to : list2){
        std::cout << to << " ";
    }
    std::cout << '\n';
    

    return 0;
}