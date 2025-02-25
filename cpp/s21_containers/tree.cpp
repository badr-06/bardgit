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

            friend class RBtree;

            RBtreeIteratorBase() : current(nullptr) {}
            RBtreeIteratorBase(Node* node) : current(node) {}

            RBtreeIteratorBase next() {
                if(current->ibnYamina != nullptr){
                    
                }
            }
            RBtreeIteratorBase prev();

    };

    RBtree();
    ~RBtree();

    void insert(Node* node, key_type k, value_type val);
    Node search(Node* node, key_type k);
    Node getmax(Node* node);
    Node getmin(Node* node);
    void Delete(Node* node, key_type k);

protected:
    struct Node{
        key_type key = 0;
        value_type value;
        Node* ubi = nullptr; // отец
        Node* ibnShimala = nullptr; // левый сын
        Node* ibnYamina = nullptr; // правый сын
        int color = BLACK;
        int Bheigth = 0;

        Node(key_type x, value_type y) : key(x), value(y), color(RED) { };
        Node(key_type x, value_type y, Node* ub) : key(x), value(y), ubi(ub), color(RED) { };
        Node(key_type x, value_type y, Node ibnl, Node ibnr, Node* ub) : key(x), value(y), ibnShimala(ibnl), ibnYamina(ibnr), ubi(ub), color(RED) { };
    };

    Node* root;
    Node* nil;
    size_type size = 0;

};

template <typename Key, typename T>
RBtree<Key, T>::RBtree()
{
    nil = new Node();
    root = nil;
}

template <typename Key, typename T>
RBtree<Key, T>::~RBtree()
{
}

template <typename Key, typename T>
void RBtree<Key, T>::insert(Node* node, key_type k, value_type val)
{
    if(node == nil){
        root = new Node(k, val, nil, nil, nil);
    }

    if(k < node->key){
        if(node->ibnYamina != nil) insert(node->ibnShimala, k, val);
        else node->ibnShimala = new Node(k ,val, node);
    }
    else{
        if(node->ibnYamina != nil) insert(node->ibnYamina, k, val);
        else node->ibnYamina = new Node(k, val, node);
    }
}

template <typename Key, typename T>
typename RBtree<Key, T>::Node RBtree<Key, T>::search(Node *node, key_type k)
{
    if(node == nil) return nil;
    if(node->key == k) return node->key;
    return k < node->key ? search(node->ibnShimala, k) : search(node->ibnYamina, k);
}

template <typename Key, typename T>
typename RBtree<Key, T>::Node RBtree<Key, T>::getmax(Node *node)
{
    if(node == nil) return nil;
    if(node->ibnYamina == nil) return node;
    return getmax(node->ibnYaminanYa);
}

template <typename Key, typename T>
typename RBtree<Key, T>::Node RBtree<Key, T>::getmin(Node *node)
{
    if(node == nil) return nil;
    if(node->ibnShimala == nil) return node;
    return getmax(node->ibnShimala);
}

template <typename Key, typename T>
void RBtree<Key, T>::Delete(Node *node, key_type k)
{
    Node* newnode = getmax(node);
}

int main(){

    RBtree<int, char> mp;


    return 0;
}