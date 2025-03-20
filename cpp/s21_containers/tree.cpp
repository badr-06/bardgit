#include "tree.h"

template <typename Key, typename T>
RBtree<Key, T>::RBtree()
{
    RBtree<Key, T>::nil = new Node();
    nil->color = BLACK;
    root = nil;
}

template <typename Key, typename T>
RBtree<Key, T>::~RBtree()
{
    DeleteTree(root);
    delete nil;
}

template <typename Key, typename T>
typename RBtree<Key, T>::iterator RBtree<Key, T>::find(const key_type k)
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
typename RBtree<Key, T>::Node* RBtree<Key, T>::getmax(Node *node)
{
    if(node == nil) return nil;
    if(node->ibnYamina == nil) return node;
    return getmax(node->ibnYamina);
}

template <typename Key, typename T>
typename RBtree<Key, T>::Node* RBtree<Key, T>::getmin(Node *node)
{
    if(node == nil) return nil;
    if(node->ibnShimala == nil) return node;
    return getmin(node->ibnShimala);
}

template <typename Key, typename T>
void RBtree<Key, T>::Delete(Node *node)
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
void RBtree<Key, T>::translations(Node *z, Node *x)
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
void RBtree<Key, T>::Delete_fixup(Node *x)
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
void RBtree<Key, T>::DeleteTree(Node* node)
{
    if(node == nil) return;
    DeleteTree(node->ibnShimala);
    DeleteTree(node->ibnYamina);
    delete node;
}

template <typename Key, typename T>
void RBtree<Key, T>::printTree(Node *node)
{
    if(node == nil) return;
    printTree(node->ibnShimala);
    std::cout << node->date.first << ' ';
    printTree(node->ibnYamina);
}

template <typename Key, typename T>
void RBtree<Key, T>::balance(Node *node)
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
void RBtree<Key, T>::leftRotate(Node *node)
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
void RBtree<Key, T>::rightRotate(Node *node)
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
bool RBtree<Key, T>::checkBlack()
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
void RBtree<Key, T>::print()
{
    if(root == nil) return;

    printTree(root);
    std::cout << '\n';
    
}

template <typename Key, typename T>
void RBtree<Key, T>::clear()
{
    if(root == nil){
        delete nil;
    }
    else {
        DeleteTree(root);
        delete nil;
    }
}

template <typename Key, typename T>
typename RBtree<Key, T>::iterator RBtree<Key, T>::begin()
{
    Node* node = getmin(root);
    return iterator(node, this);
}

template <typename Key, typename T>
typename RBtree<Key, T>::iterator RBtree<Key, T>::cbegin()
{

    Node* node = getmax(root);
    return iterator(node);
}

template <typename Key, typename T>
typename RBtree<Key, T>::iterator RBtree<Key, T>::end()
{
    return iterator(nil);
}

template <typename Key, typename T>
std::pair<typename RBtree<Key, T>::iterator, bool> RBtree<Key, T>::insert(const value_type &value)
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
    size++;
    return {iterator(newNode, this), true};
}

template <typename Key, typename T>
typename RBtree<Key, T>::Node* RBtree<Key, T>::insert_node(Node *node, key_type k, mapped_type val)
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
void RBtree<Key, T>::erase(iterator pos)
{
    if(pos.current != nil){
    Delete(pos.current);
    size--;
    }
}

int main(){

    RBtree<int, char> mp;

    mp.insert({7, 'a'});
    mp.insert({5, 'b'});
    mp.insert({1, 'c'});
    mp.insert({3, 'd'});
    mp.insert({8, 'e'});
    mp.insert({10, 'f'});
    mp.insert({9, 'g'});

    auto it = mp.begin();

    it++;
    it++;
    mp.erase(it);

    std::cout << mp.checkBlack() << '\n';

    return 0;
}