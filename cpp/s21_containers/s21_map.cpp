#include "tree.h"

namespace s21{
template <typename Key, typename T>
class map : public RBtree<Key, T> {
    public:
        class MapIterator;
        class MapConstIterator;
    
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using refernce = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;
        using iterator = MapIterator;
        using const_iterator = MapConstIterator;

        // constructors
        map() : RBtree<Key, T>() {}
        map(std::initializer_list<value_type> const &items)
        {
            for(const auto& item : items){
                this->insert(item);
            }
        }
        map(const map &m);
        map(map &&m);
        // operator=(map &&m);
        ~map() {};

        T& at(const Key& key);
        T& operator[](const Key& key);

        bool empty();
        size_type size();
        size_type max_size();

        void clear();
        std::pair<iterator, bool> insert(const Key& key, const T& obj);
        std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
        void erase(iterator pos);

        bool contains(const Key& key);

        class MapIterator : public RBtree<Key, T>::RBTreeIterator {
            public:
                MapIterator() : RBtree<Key, T>::RBTreeIterator() {}
                MapIterator(typename RBtree<Key, T>::Node *node, RBtree<Key, T>* tree) 
                : RBtree<Key, T>::RBTreeIterator(node, tree) {}
        };

        class MapConstIterator : public RBtree<Key, T>::RBTreeConstIterator {
            public:
                MapConstIterator() : RBtree<Key, T>::RBTreeConstIterator() {}
        };

};
}

int main(){

    s21::map<int, char> mp{{1, 'a'}, {2, 'b'}};



    return 0;
}