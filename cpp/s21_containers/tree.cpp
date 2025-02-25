

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

int main(){

    RBtree<int, char> mp;


    return 0;
}