
#ifndef S21_CONTAINARS_TREE_H
#define S21_CONTAINARS_TREE_H

#include <iostream>

enum { RED, BLACK };

template <typename Key, typename T>
class RBtree
{
protected:
    struct Node;

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using refernce = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

    class RBtreeIteratorBase{
        protected:
            Node* current;

        public:      
            friend class RBtree<Key, T>;

            RBtreeIteratorBase() : current(nullptr) {}
            RBtreeIteratorBase(Node* node) : current(node) {}

            void next() {
                if(current->ibnYamina != nil){
                    current = current->ibnYamina;
                    if(current->ibnShimala != nil){
                    current = getmin(current);
                    }
                }  
                else {
                    Node* ubi = current->ubi;
                    Node* node = current;
                    while (ubi != nil && ubi->ibnYamina == node)
                    {
                        node = ubi;
                        ubi = ubi->ubi;
                    }
                    if(ubi != nil){
                        current = node;
                    }
                }
            }
            void prev(){
                if(current->ibnShimala != nil){
                    current = current->ibnShimala;
                    if(current->ibnYamina != nil){
                        current = getmax(current);
                    }
                }
                else{
                    Node* ubi = current->ubi;
                    Node* node = current;
                    while (ubi != nil && ubi->ibnShimala == node)
                    {   
                        node = ubi;
                        ubi = ubi->ubi;
                    }
                    if(node != nil){
                        current = node;
                    }
                }
            }

    };

    class RBTreeIterator : public RBtreeIteratorBase{
        public:
            using RBtreeIteratorBase::RBtreeIteratorBase;
            using RBtreeIteratorBase::current;

            RBTreeIterator operator++() {
                this->next();
                return *this;
            }
            RBTreeIterator operator++(int) {
                RBTreeIterator temp = *this;
                this->next();
                return temp;
            }
            RBTreeIterator operator--() {
                this->prev();
                return *this;
            }
            RBTreeIterator operator--(int) {
                RBTreeIterator temp = *this;
                this->prev();
                return temp;
            }

    };

    class RBTreeConstIterator : public RBtreeIteratorBase{
        public:
            using RBtreeIteratorBase::RBtreeIteratorBase;
            using RBtreeIteratorBase::current;

            RBTreeIterator operator++() {
                this->next();
                return *this;
            }
            RBTreeIterator operator++(int) {
                RBTreeIterator temp = *this;
                this->next();
                return temp;
            }
            RBTreeIterator operator--() {
                this->prev();
                return *this;
            }
            RBTreeIterator operator--(int) {
                RBTreeIterator temp = *this;
                this->prev();
                return temp;
            }

    };


    RBtree();
    ~RBtree();

    void insert(Node* node, key_type k, value_type val);
    Node search(Node* node, key_type k);
    Node getmax(Node* node);
    Node getmin(Node* node);
    void DeleteNode(Node* node, key_type k);
    void DeleteTree(Node* node);
    void clear();

protected:
    struct Node{
        key_type key = 0;
        value_type value;
        Node* ubi = nullptr; // отец
        Node* ibnShimala = nullptr; // левый сын
        Node* ibnYamina = nullptr; // правый сын
        int color = BLACK;
        int Bheigth = 0;

        Node() {}
        Node(key_type x, value_type y) : key(x), value(y), color(RED) { };
        Node(key_type x, value_type y, Node* ub) : key(x), value(y), ubi(ub), color(RED) { };
        Node(key_type x, value_type y, Node ibnl, Node ibnr, Node* ub) : key(x), value(y), ibnShimala(ibnl), ibnYamina(ibnr), ubi(ub), color(RED) { };
    };



    Node* root;
    Node* nil;
    size_type size = 0;

};

#endif
