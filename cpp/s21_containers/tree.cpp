#include "tree.h"

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
typename RBtree<Key, T>::iterator RBtree<Key, T>::find(const key_type k)
{
    Node* node = root;
    while (node != nil)
    {
        if(node->key == k){
            return iterator(node);
        }

        if(node->key < k){
            node = node->ibnYamina;
        }
        else{
            node = node->ibnShimala;
        }
    }
    return iterator(node);
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
    return getmin(node->ibnShimala);
}

template <typename Key, typename T>
void RBtree<Key, T>::DeleteNode(Node *node, key_type k)
{
    Node* newnode = getmax(node);
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
typename RBtree<Key, T>::Node* RBtree<Key, T>::insert_node(Node *node, key_type k, mapped_type val)
{
    if(k < node->key){
        if(node->ibnYamina != nil) return insert_node(node->ibnShimala, k, val);
        else return (node->ibnShimala = new Node(k, val, node));
    }
    else{
        if(node->ibnYamina != nil) return insert_node(node->ibnYamina, k, val);
        else return (node->ibnYamina = new Node(k, val, node));
    }
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
    auto it = find(value.first);
    if(it != end()){
        return {it, false};
    }
    else{
        Node* node = insert_node(root, value.first, value.second);
        return {iterator(node), true};
    }
}

int main(){

    RBtree<int, char> mp;
    mp.insert({1, 'a'});

    return 0;
}