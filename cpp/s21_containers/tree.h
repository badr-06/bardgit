
#ifndef S21_CONTAINARS_TREE_H
#define S21_CONTAINARS_TREE_H

#include <iostream>

typedef enum { RED, BLACK } Colors;

template <typename Key, typename T>
class RBtree
{
protected:
    struct Node;

    class RBTreeIterator;
    class RBTreeConstIterator;

    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = size_t;

    Node* root;
    Node* nil;
    size_type size_tree = 0;

    template <typename NodeT,typename RBtreeT>
    class RBTreeIteratorBase{
        protected:
            NodeT current;
            RBtreeT tree;

        public:    
            friend class RBtree<Key, T>;

            RBTreeIteratorBase() : current(nullptr), tree(nullptr) {}
            RBTreeIteratorBase(NodeT node, RBtreeT tree) : current(node), tree(tree) {}

            NodeT get_current() {return this->current;}

            void next() {

                if(current == tree->getmax(tree->root)){
                    current = tree->nil;
                }
                else if(current == tree->nil){
                    current = tree->getmax(tree->root);
                }
                else if(current->ibnYamina != tree->nil){
                    current = current->ibnYamina;
                    if(current->ibnShimala != tree->nil){
                    current = tree->getmin(current);
                    }
                }  
                else {
                    NodeT ubi = current->ubi;
                    NodeT node = current;
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
                
                if(current == tree->getmax(tree->root)){
                    current = tree->nil;
                }
                else if(current == tree->nil){
                    current = tree->getmax(tree->root);
                }
                else if(current->ibnShimala != tree->nil){
                    current = current->ibnShimala;
                    if(current->ibnYamina != tree->nil){
                        current = tree->getmax(current);
                    }
                }
                else{
                    NodeT ubi = current->ubi;
                    NodeT node = current;
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
            
            bool operator!=(const RBTreeIteratorBase& other) const { return current != other.current; }
            bool operator==(const RBTreeIteratorBase& other) const { return current == other.current; }

    };

    class RBTreeIterator : public RBTreeIteratorBase<Node*, RBtree<Key, T>* >{    
            using Base = RBTreeIteratorBase<Node*, RBtree<Key, T>* >;
        public:
            friend class RBtree<Key, T>;
            using Base::Base;

            RBTreeIterator& operator++() {
                this->next();
                return *this;
            }
            RBTreeIterator operator++(int) {
                RBTreeIterator temp = *this;
                this->next();
                return temp;
            }
            RBTreeIterator& operator--() {
                this->prev();
                return *this;
            }
            RBTreeIterator operator--(int) {
                RBTreeIterator temp = *this;
                this->prev();
                return temp;
            }
    };

    class RBTreeConstIterator : public RBTreeIteratorBase<const Node*, const RBtree<Key, T>* > {
            using Base = RBTreeIteratorBase<const Node*, const RBtree<Key, T>* >;
        public:
            friend class RBtree<Key, T>;
            using Base::Base;

            const value_type& operator*() const { return this->current->date; }
            const value_type* operator->() const { return &(this->current->date); }

            RBTreeConstIterator& operator++() {
                this->next();
                return *this;
            }
            RBTreeConstIterator operator++(int) {
                RBTreeConstIterator temp = *this;
                this->next();
                return temp;
            }
            RBTreeConstIterator operator--() {
                this->prev();
                return *this;
            }
            RBTreeConstIterator& operator--(int) {
                RBTreeConstIterator temp = *this;
                this->prev();
                return temp;
            }
    };

    using iterator = RBTreeIterator;
    using const_iterator = RBTreeConstIterator;
    
public:
    RBtree();
    ~RBtree();

    void clear();
    iterator begin();
    iterator cbegin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    
    iterator end();
    const_iterator end() const;

    std::pair<iterator, bool> insert(const value_type& value);
    void erase(iterator pos);
    void merge(RBtree<Key, T>& other);
    void swap(RBtree<Key, T>& other);

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
    Node* getmax(Node* node) const;
    Node* getmin(Node* node) const;

    const Node* getmax(const Node* node) const;
    const Node* getmin(const Node* node) const;

    void Delete(Node* node);
    void translations(Node* z, Node* x);
    void Delete_fixup(Node* x);
    void DeleteTree(Node* node);
    Node* insert_node(Node* node, key_type k, mapped_type val);
    void printTree(Node* node);
    void balance(Node* node);
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    bool Copy(const RBtree<Key, T>& Tree);
    void initialization();
};

template <typename Key, typename T>
inline RBtree<Key, T>::RBtree()
{
    RBtree<Key, T>::nil = new Node();
    nil->color = BLACK;
    root = nil;
}

template <typename Key, typename T>
inline RBtree<Key, T>::~RBtree()
{
    DeleteTree(root);
    delete nil;
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::iterator RBtree<Key, T>::find(const key_type k)
{
    Node* node = root;
    while (node != nil)
    {
        if(node->date.first == k){
            return iterator(node, this);
        }

        if(node->date.first < k){
            node = node->ibnYamina;
        }
        else{
            node = node->ibnShimala;
        }
    }
    return iterator(node, this);
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::Node* RBtree<Key, T>::getmax(Node *node) const
{
    if(node == nil) return nil;
    while (node->ibnYamina != nil)
    {
        node = node->ibnYamina;
    }
    return node;
}

template <typename Key, typename T>
inline const typename RBtree<Key, T>::Node* RBtree<Key, T>::getmax(const Node *node) const
{
    if(node == nil) return nil;
    while (node->ibnYamina != nil)
    {
        node = node->ibnYamina;
    }
    return node;
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::Node* RBtree<Key, T>::getmin(Node *node) const
{
    if(node == nil) return nil;
    while (node->ibnShimala != nil)
    {
        node = node->ibnShimala;
    }
    return node;
}

template <typename Key, typename T>
inline const typename RBtree<Key, T>::Node* RBtree<Key, T>::getmin(const Node *node) const
{
    if(node == nil) return nil;
    while (node->ibnShimala != nil)
    {
        node = node->ibnShimala;
    }
    return node;
}

template <typename Key, typename T>
inline void RBtree<Key, T>::Delete(Node *node)
{
    Colors original_color = node->color;
    Node* x;
    if(node->ibnShimala == nil || node->ibnYamina == nil){
        x = node->ibnShimala == nil ? node->ibnYamina : node->ibnShimala;
        translations(node, x);
    }
    else {
        Node* y = getmin(node->ibnYamina);
        original_color = y->color;
        x = y->ibnYamina;

        if(y->ubi == node){
            x->ubi = y;
        }
        else {
            translations(y, y->ibnYamina);
            y->ibnYamina = node->ibnYamina;
            node->ibnYamina->ubi = y;
        }

        translations(node, y);
        y->ibnShimala = node->ibnShimala;
        node->ibnShimala->ubi = y;
        y->color = node->color;
        
    }

    delete node;

    if(original_color == BLACK){
        Delete_fixup(x);
    }
}

template <typename Key, typename T>
inline void RBtree<Key, T>::translations(Node *z, Node *x)
{
    Node* ub = z->ubi;
    if(ub == nil){
        root = x;
    }
    else if(ub->ibnShimala == z){
        ub->ibnShimala = x;
    }
    else{
        ub->ibnYamina = x;
    }
    x->ubi = ub;
}

template <typename Key, typename T>
inline void RBtree<Key, T>::Delete_fixup(Node *x)
{
    while(x != root && x->color == BLACK)
    {
        if(x = x->ubi->ibnShimala){
            Node *w = x->ubi->ibnYamina;
            // case 1
            if(w->color == RED){
                w->color = BLACK;
                x->ubi->color = RED;
                leftRotate(x->ubi);
                w = x->ubi->ibnYamina;
            }
            // case 2
            if(w->ibnShimala->color == BLACK && w->ibnYamina->color == BLACK){
                w->color = RED;
                x = x->ubi;
            }
            else {
                // case 3
                if(w->ibnYamina->color == BLACK){
                    w->ibnShimala->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->ubi->ibnYamina;
                }

                // case 4 
                w->color = x->ubi->color;
                x->ubi->color = BLACK;
                w->ibnYamina->color = BLACK;
                leftRotate(x->ubi);
                x = root;
            }
        }
        else{
            Node *w = x->ubi->ibnShimala;

            if(w->color == RED){
                w->color = BLACK;
                x->ubi->color = RED;
                rightRotate(x->ubi);
                w = x->ubi->ibnShimala;
            }

            if(w->ibnShimala->color == BLACK && w->ibnYamina->color == BLACK){
                w->color = RED;
                x = x->ubi;
            }
            else{

                if(w->ibnShimala->color == BLACK){
                    w->ibnYamina->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->ubi->ibnShimala;
                }

                w->color = x->ubi->color;
                x->ubi->color = BLACK;
                w->ibnShimala->color = BLACK;
                rightRotate(x->ubi);
                x = root;
            }
        }
    }

    x->color = BLACK;
}

template <typename Key, typename T>
inline void RBtree<Key, T>::DeleteTree(Node* node)
{
    if(node == nil) return;
    DeleteTree(node->ibnShimala);
    DeleteTree(node->ibnYamina);
    delete node;
}

template <typename Key, typename T>
inline void RBtree<Key, T>::printTree(Node *node)
{
    if(node == nil) return;
    printTree(node->ibnShimala);
    std::cout << node->date.first << ' ';
    printTree(node->ibnYamina);
}

template <typename Key, typename T>
inline void RBtree<Key, T>::balance(Node *node)
{
    while(node->ubi->color == RED){
        if(node->ubi == node->ubi->ubi->ibnShimala){
            Node* uncle = node->ubi->ubi->ibnYamina;
            if(uncle->color == RED){
                node->ubi->color = BLACK;
                node->ubi->ubi->color = RED;
                uncle->color = BLACK;
                node = node->ubi->ubi;
            } 
            else{ 
                if(node == node->ubi->ibnYamina){
                    node = node->ubi;
                    leftRotate(node);
                }
                node->ubi->color = BLACK;
                node->ubi->ubi->color = RED;
                rightRotate(node->ubi->ubi);
            }
        }
        else{
            Node* uncle = node->ubi->ubi->ibnShimala;
            if(uncle->color == RED){
                node->ubi->color = BLACK;
                node->ubi->ubi->color = RED;
                uncle->color = BLACK;
                node = node->ubi->ubi;
            }
            else{
                if(node == node->ubi->ibnShimala){
                    node = node->ubi;
                    rightRotate(node);
                }
                node->ubi->color = BLACK;
                node->ubi->ubi->color = RED;
                leftRotate(node->ubi->ubi);
            }
        }
    }
    root->color = BLACK;
}

template <typename Key, typename T>
inline void RBtree<Key, T>::leftRotate(Node *node)
{
    Node* right = node->ibnYamina;
    node->ibnYamina = right->ibnShimala;
    if(right->ibnShimala != nil){
        right->ibnShimala->ubi = node;
    }
    right->ubi = node->ubi;
    if(node->ubi == nil){
        root = right;
    } 
    else if(node == node->ubi->ibnShimala){
        node->ubi->ibnShimala = right;
    }
    else {
        node->ubi->ibnYamina = right;
    }
    right->ibnShimala = node;
    node->ubi = right;
}

template <typename Key, typename T>
inline void RBtree<Key, T>::rightRotate(Node *node)
{
    Node* left = node->ibnShimala;
    node->ibnShimala = left->ibnYamina;
    if(left->ibnYamina != nil){
        left->ibnYamina->ubi = node;
    }
    left->ubi = node->ubi;
    if(node->ubi == nil){
        root = left;
    }
    else if(node == node->ubi->ibnShimala){
        node->ubi->ibnShimala = left;
    }
    else {
        node->ubi->ibnYamina = left;
    }
    left->ibnYamina = node;
    node->ubi = left;
}

template <typename Key, typename T>
inline bool RBtree<Key, T>::Copy(const RBtree<Key, T> &Tree)
{
    if(Tree.root == Tree.nil){
        return false;
    }
    for(auto it = Tree.begin(); it != Tree.end(); ++it){
        this->insert(*it);
    }
    return true;
}

template <typename Key, typename T>
inline void RBtree<Key, T>::initialization()
{
    root = nil;
    root->ibnShimala = nil;
    root->ibnYamina = nil;
    size_tree = 0;
}

template <typename Key, typename T>
inline bool RBtree<Key, T>::checkBlack()
{
    int lb = 0;
    int rb = 0;

    Node *l = root;
    Node *r = root;

    while(l != nil){
        l = l->ibnShimala;
        if(l->color == BLACK) lb++;
    }

    while(r != nil){
        r = r->ibnYamina;
        if(r->color == BLACK) rb++;
    }

    if(rb == lb) return true;
    else return false;
}  

template <typename Key, typename T>
inline void RBtree<Key, T>::print()
{
    if(root == nil) return;

    printTree(root);
    std::cout << '\n';
    
}

template <typename Key, typename T>
inline void RBtree<Key, T>::clear()
{
    if(root != nil){
        DeleteTree(root);
        initialization();
    }
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::iterator RBtree<Key, T>::begin()
{
    Node* node = getmin(root);
    return iterator(node, this);
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::iterator RBtree<Key, T>::cbegin()
{

    Node* node = getmax(root);
    return iterator(node, this);
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::const_iterator RBtree<Key, T>::begin() const
{
    Node* node = getmin(root);
    return const_iterator(node, this);
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::const_iterator RBtree<Key, T>::cbegin() const
{

    Node* node = getmax(root);
    return const_iterator(node, this);
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::iterator RBtree<Key, T>::end()
{
    return iterator(nil, this);
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::const_iterator RBtree<Key, T>::end() const
{
    return const_iterator(nil, this);
}

template <typename Key, typename T>
inline std::pair<typename RBtree<Key, T>::iterator, bool> RBtree<Key, T>::insert(const value_type &value)
{
    Node *newNode = nullptr;
    if(root == nil){
        newNode = new Node(value.first, value.second, nil, nil, nil);
        root = newNode;
    }
    else{
        auto it = find(value.first);
        if(it.current != nil){
            return{it, false};
        }
        newNode = insert_node(root, value.first, value.second);
    }
    balance(newNode);
    size_tree++;
    return {iterator(newNode, this), true};
}

template <typename Key, typename T>
inline void RBtree<Key, T>::erase(iterator pos)
{
    if(pos.current != nil){
    Delete(pos.current);
    size_tree--;
    }
}

template <typename Key, typename T>
inline typename RBtree<Key, T>::Node* RBtree<Key, T>::insert_node(Node *node, key_type k, mapped_type val)
{
    Node *temp = nullptr;
    while(node != nil){
        temp = node;
        if(k > node->date.first){
            node = node->ibnYamina;
        }
        else {
            node = node->ibnShimala;
        }
    }
    Node* newNode = new Node(k, val, nil, nil, temp);
    if(k > temp->date.first)
        temp->ibnYamina = newNode;
    else 
        temp->ibnShimala = newNode;

    return newNode;
}



template <typename Key, typename T>
inline void RBtree<Key, T>::merge(RBtree<Key, T> &other)
{   
    auto it = other.begin();
    while(it != other.end()){
        auto del_it = it++;
        if(this->insert(*del_it).second){
            other.erase(del_it);
        }
    }
}

template <typename Key, typename T>
inline void RBtree<Key, T>::swap(RBtree<Key, T> &other)
{
    Node *temp = other.root;
    other.root = this->root;
    this->root = temp;

    Node* n = other.nil;
    other.nil = this->nil;
    this->nil = n;

    size_type s = other.size_tree;
    other.size_tree = this->size_tree;
    this->size_tree = s; 
}

#endif
