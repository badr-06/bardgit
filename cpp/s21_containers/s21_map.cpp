#include "tree.h"
#include <stdexcept>

namespace s21{
template <typename Key, typename T>
class map : public RBtree<Key, T> {
    private:
    
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using refernce = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;

        class MapIterator : public RBtree<Key, T>::RBTreeIterator {

        public:
            MapIterator() : RBtree<Key, T>::RBTreeIterator() {}
            MapIterator(typename RBtree<Key, T>::Node *node, RBtree<Key, T>* tree) : RBtree<Key, T>::RBTreeIterator(node, tree) {}


            value_type& operator*() { return this->current->date; }
            value_type* operator->() { return &(this->current->date); }
        };

        class MapConstIterator;

        using iterator = MapIterator;
        using const_iterator = MapConstIterator;
    public:
        // constructors
        map() : RBtree<Key, T>() {}
        map(std::initializer_list<value_type> const &items){
            for(const auto& item : items){
                RBtree<Key, T>::insert(item);
            }
        }
        map(const map &m){
            RBtree<Key, T>::Copy(m);
        }
        map(map &&m){
            RBtree<Key, T>::swap(m);
        }
        map operator=(map &&m){
            RBtree<Key, T>::swap(m);
            m.DeleteTree(m.root);
            m.initialization();
            return *this;
        }
        map operator=(const map& m){
            RBtree<Key, T>::Copy(m);
            return *this;
        }
        ~map() {};

        T& at(const Key& key){
            auto it = RBtree<Key, T>::find(key);
            if(it == this->end()){
                throw std::out_of_range("RBtree::at: key not found");
                // abort();
            }

            return it->second;
        }
        T& operator[](const Key& key){
            auto it = this->find(key);
            if(it == this->end()){
                it = RBtree<Key, T>::insert({key, T()}).first;
            }

            return it->second;
        }

        iterator begin(){
            auto it = RBtree<Key, T>::begin();
            return iterator(it);
        }
        iterator end(){
            auto it = RBtree<Key, T>::end();
            return iterator(it);
        }

        bool empty(){
            if(this->size_tree == 0) return true;
            else return false;
        }
        size_type size(){
            return this->size_tree;
        }
        size_type max_size(){
            return sizeof(size_type);
        }

        void clear() { RBtree<Key, T>::clear(); }

        std::pair<iterator, bool> insert(const value_type& value){ 
            auto it = RBtree<Key, T>::insert(value);
            
            return {iterator(it.first), it.second};
        }
        std::pair<iterator, bool> insert(const Key& key, const T& obj){ 
            auto it = RBtree<Key, T>::insert({key, obj}); 
            return {iterator(it.first), it.second};    
        }
        std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj){
            auto it_rb(RBtree<Key, T>::insert({key, obj}));
            std::pair<iterator, bool> it = {iterator(it_rb.first), it_rb.second}; 
            if(!it.second){
                it.first->second = obj; 
            }

            return it;
        }
        void erase(iterator pos) { RBtree<Key, T>::erase(pos); }
        void swap(map& other) { RBtree<Key, T>::swap(other); }
        void merge(map& other) { RBtree<Key, T>::merge(other); }
        bool contains(const Key& key) {
            auto it = this->find(key);
            if(it != this->end()){
                return true;
            } else {
                return false;
            }
        }

        class MapIterator : public RBtree<Key, T>::RBTreeIterator {
            using Base = typename RBtree<Key, T>::RBTreeIterator;
            public:
            MapIterator(const Base& base_it) : Base(base_it) {}

            using Base::Base;

            value_type& operator*() { return this->current->date; }
            value_type* operator->() { return &(this->current->date); }
        };

        class MapConstIterator : public RBtree<Key, T>::RBTreeConstIterator {
            using Base = typename RBtree<Key, T>::RBTreeConstIterator;
            public:

            using Base::Base;
        };

        bool contains(const Key& key){
            auto it = this->find(key);
            if(it != this->end()){
                return true;
            } else {
                return false;
            }
        }
};
}

int main(){

    s21::map<int, char> mp1{{1, 'a'}, {2, 'b'}};
    s21::map<int, char> mp2{{4, 'r'}, {3, 'c'}, {5, 'g'}};

    auto it = mp1.begin();

    // mp1.insert_or_assign(1, 'c');

    std::cout << it->second << '\n';    

    return 0;
}