
#ifndef S21_CONTAINARS_TREE_H
#define S21_CONTAINARS_TREE_H

#include <iostream>

typedef enum { RED, BLACK } Colors;

template <typename Key, typename T>
class RBtree
{
protected:
      struct Node;

public:

    class RBTreeIterator;
    class RBTreeConstIterator;

    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<key_type, mapped_type>;
    using refernce = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using iterator = RBTreeIterator;
    using const_iterator = RBTreeConstIterator;

    Node* root;
    Node* nil;
    size_type size = 0;

    class RBtreeIteratorBase{
        protected:
            Node* current;
            RBtree<Key, T>* tree;

        public:      

            RBtreeIteratorBase() : current(nullptr), tree(nullptr) {}
            RBtreeIteratorBase(Node* node, RBtree<Key, T>* tree) : current(node), tree(tree) {}

            void next() {
                
                if(current->ibnYamina != tree->nil){
                    current = current->ibnYamina;
                    if(current->ibnShimala != tree->nil){
                    current = tree->getmin(current);
                    }
                }  
                else {
                    Node* ubi = current->ubi;
                    Node* node = current;
                    while (ubi != tree->nil && ubi->ibnYamina == node)
                    {
                            node = ubi;
                            ubi = ubi->ubi;
                        }
                        if(ubi != tree->nil){
                            current = ubi;
                        }
                    }
                
            }
            void prev(){
                
                if(current->ibnShimala != tree->nil){
                    current = current->ibnShimala;
                    if(current->ibnYamina != tree->nil){
                        current = tree->getmax(current);
                    }
                }
                else{
                    Node* ubi = current->ubi;
                    Node* node = current;
                    while (ubi != tree->nil && ubi->ibnShimala == node)
                    {   
                        node = ubi;
                        ubi = ubi->ubi;
                    }
                    if(ubi != tree->nil){
                        current = ubi;
                    }
                }
                
            }

    };

    class RBTreeIterator : public RBtreeIteratorBase{
        public:
            using RBtreeIteratorBase::RBtreeIteratorBase;
            using RBtreeIteratorBase::current;

            value_type& operator*() { return current->date; }
            value_type* operator->() { return &(current->date); }

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
            
            bool operator!=(const RBTreeIterator& other) { return current != other.current; }
            bool operator==(const RBTreeIterator& other) { return current == other.current; }

    };

    class RBTreeConstIterator : public RBTreeIterator {
        public:
            using RBtreeIteratorBase::current;
            RBTreeConstIterator() : RBTreeIterator() {}
            const value_type& operator*() { return current->date; }
    };

    RBtree();
    ~RBtree();

    void clear();
    iterator begin();
    iterator cbegin();
    iterator end();
    std::pair<iterator, bool> insert(const value_type& value);
    void erase(iterator pos);

    void print();
    bool checkBlack();

protected:
    struct Node{
        value_type date;
        Node* ubi; // отец
        Node* ibnShimala; // левый сын
        Node* ibnYamina; // правый сын
        Colors color;

        Node(const key_type x = 0, mapped_type y = 0, Node *ibnl = nullptr, Node *ibnr = nullptr, Node* ub = nullptr, Colors col = RED) : date({x, y}) {
            ubi = ub;
            ibnShimala = ibnl;
            ibnYamina = ibnr;
            color = col;
        };
    };

    iterator find(const key_type k);
    Node* getmax(Node* node);
    Node* getmin(Node* node);
    void Delete(Node* node);
    void translations(Node* z, Node* x);
    void Delete_fixup(Node* x);
    void DeleteTree(Node* node);
    Node* insert_node(Node* node, key_type k, mapped_type val);
    void printTree(Node* node);
    void balance(Node* node);
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    
};

#endif
