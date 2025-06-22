#include "../s21_vector/s21_vector.h"
#include "../tree.hpp"

namespace s21 {
template <typename Key>
class multiset : public RBtree<Key, Key> {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class MultiSetIterator : public RBtree<Key, Key>::RBTreeIterator {
    using Base = typename RBtree<Key, Key>::RBTreeIterator;

   public:
    using Base::Base;

    MultiSetIterator(const Base& base_it) : Base(base_it) {}

    reference operator*() { return this->current->date.second; }

    friend class multiset<Key>;
  };

  class MultiSetConstIterator : public RBtree<Key, Key>::RBTreeConstIterator {
    using Base = typename RBtree<Key, Key>::RBTreeConstIterator;

   public:
    using Base::Base;

    MultiSetConstIterator(const Base& base_it) : Base(base_it) {}

    const_reference operator*() const { return this->current->date.second; }

    friend class multiset<Key>;
  };

  using iterator = MultiSetIterator;
  using const_iterator = MultiSetConstIterator;

 public:
  multiset() : RBtree<Key, Key>() {}

  multiset(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      RBtree<Key, Key>::insert({*it, *it}, false);
    }
  }

  multiset(const multiset& s) { Copy(s); }

  multiset(multiset&& s) { RBtree<Key, Key>::swap(s); }

  ~multiset() {}

  multiset operator=(const multiset& s) {
    if (!Copy(s)) {
      RBtree<Key, Key>::clear();
    }
    return *this;
  }

  multiset operator=(multiset&& s) {
    RBtree<Key, Key>::swap(s);
    s.DeleteTree(s.root);
    s.initialization();
    return *this;
  }

  iterator begin() {
    auto it = RBtree<Key, Key>::begin();
    return iterator(it);
  }

  const_iterator begin() const {
    auto it = RBtree<Key, Key>::begin();
    return const_iterator(it);
  }

  iterator end() {
    auto it = RBtree<Key, Key>::end();
    return iterator(it);
  }
  const_iterator end() const {
    auto it = RBtree<Key, Key>::end();
    return const_iterator(it);
  }

  bool empty() {
    if (this->size_tree == 0)
      return true;
    else
      return false;
  }

  void clear() { RBtree<Key, Key>::clear(); }

  iterator insert(const value_type& value) {
    auto it = RBtree<Key, Key>::insert({value, value}, false);

    return iterator(it.first);
  }

  void erase(iterator pos) { RBtree<Key, Key>::erase(pos); }
  void swap(multiset& other) { RBtree<Key, Key>::swap(other); }
  void merge(multiset& other) { RBtree<Key, Key>::merge(other, false); }
  bool contains(const Key& key) {
    auto it = RBtree<Key, Key>::find(key);
    if (it != RBtree<Key, Key>::end()) {
      return true;
    } else {
      return false;
    }
  }

  size_type count(const Key& key) {
    size_type quantity = 0;
    auto it = lower_bound(key);
    for (; it != end() && *it == key; ++it) {
      quantity++;
    }
    return quantity;
  }

  iterator find(const Key& key) { return lower_bound(key); }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    auto it1 = lower_bound(key);
    auto it2 = upper_bound(key);

    return {it1, ++it2};
  }

  iterator lower_bound(const Key& key) {
    auto it = iterator(RBtree<Key, Key>::find(key));
    iterator res_it = it--;
    while (key == *it && it != end()) {
      res_it = it--;
    }
    return res_it;
  }

  iterator upper_bound(const Key& key) {
    auto it = find(key);
    iterator res_it = it++;
    while (key == *it && it != end()) {
      res_it = it++;
    }

    return res_it;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.push_back({this->insert(std::forward<Args>(args)), true}), ...);
    return results;
  }

 private:
  bool Copy(const multiset& Tree) {
    if (Tree.root == Tree.nil) {
      return false;
    }
    for (auto it = Tree.begin(); it != Tree.end(); ++it) {
      RBtree<Key, Key>::insert(*it, *it, false);
    }
    return true;
  }
};
}  // namespace s21
