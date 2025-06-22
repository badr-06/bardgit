#include <stdexcept>
#include <string>

#include "../s21_vector/s21_vector.h"
#include "../tree.hpp"

namespace s21 {
template <typename Key, typename T>
class map : public RBtree<Key, T> {
 private:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class MapIterator : public RBtree<Key, T>::RBTreeIterator {
    using Base = typename RBtree<Key, T>::RBTreeIterator;

   public:
    MapIterator(const Base& base_it) : Base(base_it) {}

    using Base::Base;

    reference operator*() { return this->current->date; }

    friend class map<Key, T>;
  };

  class MapConstIterator : public RBtree<Key, T>::RBTreeConstIterator {
    using Base = typename RBtree<Key, T>::RBTreeConstIterator;

   public:
    MapConstIterator(const Base& base_it) : Base(base_it) {}
    using Base::Base;

    const_reference operator*() const { return this->current->date; }

    friend class map<Key, T>;
  };

  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

 public:
  // constructors
  map() : RBtree<Key, T>() {}
  map(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      RBtree<Key, T>::insert(*it);
    }
  }
  map(const map& m) { Copy(m); }
  map(map&& m) { RBtree<Key, T>::swap(m); }
  map operator=(map&& m) {
    RBtree<Key, T>::swap(m);
    m.DeleteTree(m.root);
    m.initialization();
    return *this;
  }
  map operator=(const map& m) {
    if (!Copy(m)) {
      RBtree<Key, T>::clear();
    }
    return *this;
  }
  ~map() {};

  T& at(const Key& key) {
    auto it = RBtree<Key, T>::find(key);
    if (it == this->end()) {
      throw std::out_of_range("RBtree::at: key not found");
      // abort();
    }

    auto map_it = iterator(it);
    return map_it->second;
  }
  T& operator[](const Key& key) {
    auto it = this->find(key);
    if (it == this->end()) {
      it = RBtree<Key, T>::insert({key, T()}).first;
    }
    auto map_it = iterator(it);
    return map_it->second;
  }

  iterator begin() {
    auto it = RBtree<Key, T>::begin();
    return iterator(it);
  }
  const_iterator begin() const {
    auto it = RBtree<Key, T>::begin();
    return const_iterator(it);
  }
  iterator end() {
    auto it = RBtree<Key, T>::end();
    return iterator(it);
  }
  const_iterator end() const {
    auto it = RBtree<Key, T>::end();
    return const_iterator(it);
  }
  bool empty() {
    if (this->size_tree == 0)
      return true;
    else
      return false;
  }

  void clear() { RBtree<Key, T>::clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto it = RBtree<Key, T>::insert(value);

    return {iterator(it.first), it.second};
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    auto it = RBtree<Key, T>::insert({key, obj});
    return {iterator(it.first), it.second};
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto it_rb(RBtree<Key, T>::insert({key, obj}));
    std::pair<iterator, bool> it = {iterator(it_rb.first), it_rb.second};
    if (!it.second) {
      it.first->second = obj;
    }

    return it;
  }
  void erase(iterator pos) { RBtree<Key, T>::erase(pos); }
  void swap(map& other) { RBtree<Key, T>::swap(other); }
  void merge(map& other) { RBtree<Key, T>::merge(other); }
  bool contains(const Key& key) {
    auto it = this->find(key);
    if (it != this->end()) {
      return true;
    } else {
      return false;
    }
  }
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

 private:
  bool Copy(const map& Tree) {
    if (Tree.root == Tree.nil) {
      return false;
    }
    for (auto it = Tree.begin(); it != Tree.end(); ++it) {
      RBtree<Key, T>::insert(*it);
    }
    return true;
  }
};
}  // namespace s21
