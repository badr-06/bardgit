#include "../s21_vector/s21_vector.h"
#include "../tree.hpp"

namespace s21 {
template <typename Key>
class set : public RBtree<Key, Key> {
 protected:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class SetIterator : public RBtree<Key, Key>::RBTreeIterator {
    using Base = typename RBtree<Key, Key>::RBTreeIterator;

   public:
    using Base::Base;

    SetIterator(const Base& base_it) : Base(base_it) {}

    reference operator*() { return this->current->date.second; }

    friend class set<Key>;
  };

  class SetConstIterator : public RBtree<Key, Key>::RBTreeConstIterator {
    using Base = typename RBtree<Key, Key>::RBTreeConstIterator;

   public:
    using Base::Base;

    SetConstIterator(const Base& base_it) : Base(base_it) {}

    const_reference operator*() const { return this->current->date.second; }

    friend class set<Key>;
  };

 public:
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

  set() : RBtree<Key, Key>() {}
  set(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      RBtree<Key, Key>::insert({*it, *it});
    }
  }
  set(const set& s) { Copy(s); }

  set(set&& s) { RBtree<Key, Key>::swap(s); }

  ~set() {}

  set operator=(const set& s) {
    if (!Copy(s)) {
      RBtree<Key, Key>::clear();
    }
    return *this;
  }

  set operator=(set&& s) {
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

  std::pair<iterator, bool> insert(const value_type& value) {
    auto it = RBtree<Key, Key>::insert({value, value});

    return {iterator(it.first), it.second};
  }

  void erase(iterator pos) { RBtree<Key, Key>::erase(pos); }
  void swap(set& other) { RBtree<Key, Key>::swap(other); }
  void merge(set& other) { RBtree<Key, Key>::merge(other); }
  bool contains(const Key& key) {
    auto it = RBtree<Key, Key>::find(key);
    if (it != RBtree<Key, Key>::end()) {
      return true;
    } else {
      return false;
    }
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.push_back(this->insert(std::forward<Args>(args))), ...);
    return results;
  }

 private:
  bool Copy(const set& Tree) {
    if (Tree.root == Tree.nil) {
      return false;
    }
    for (auto it = Tree.begin(); it != Tree.end(); ++it) {
      RBtree<Key, Key>::insert(*it, *it);
    }
    return true;
  }
};
}  // namespace s21
