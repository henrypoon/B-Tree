/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <vector>
#include <utility>
#include <algorithm>
#include <memory>
#include <sstream>
#include <cassert>
#include <type_traits>
#include <queue>
// we better include the iterator
#include "btree_iterator.h"
using namespace std;

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template<typename T> class btree;
template<typename T> ostream &operator<<(ostream&, const btree<T>&);

template <typename T> 
class btree {
public:
  /** Hmm, need some iterator typedefs here... friends? **/
    using iterator = btree_iterator<T>;
    friend iterator;
    using const_iterator = btree_iterator<T, std::add_const>;
    friend const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    friend reverse_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    friend const_reverse_iterator;

  /**
   * Constructs an empty btree.  Note that
   * the elements stored in your btree must
   * have a well-defined zero-arg constructor,
   * copy constructor, operator=, and destructor.
   * The elements must also know how to order themselves
   * relative to each other by implementing operator<
   * and operator==. (These are already implemented on
   * behalf of all built-ins: ints, doubles, strings, etc.)
   * 
   * @param maxNodeElems the maximum number of elements
   *        that can be stored in each B-Tree node
   */
    btree(size_t maxNodeElems = 40);

  /**
   * The copy constructor and  assignment operator.
   * They allow us to pass around B-Trees by value.
   * Although these operations are likely to be expensive
   * they make for an interesting programming exercise.
   * Implement these operations using value semantics and 
   * make sure they do not leak memory.
   */

  /** 
   * Copy constructor
   * Creates a new B-Tree as a copy of original.
   *
   * @param original a const lvalue reference to a B-Tree object
   */
    btree(const btree<T>& original);

  /** 
   * Move constructor
   * Creates a new B-Tree by "stealing" from original.
   *
   * @param original an rvalue reference to a B-Tree object
   */
    btree(btree<T>&& original);
  
  
  /** 
   * Copy assignment
   * Replaces the contents of this object with a copy of rhs.
   *
   * @param rhs a const lvalue reference to a B-Tree object
   */
    btree<T>& operator=(const btree<T>& rhs);

  /** 
   * Move assignment
   * Replaces the contents of this object with the "stolen"
   * contents of original.
   *
   * @param rhs a const reference to a B-Tree object
   */
    btree<T>& operator=(btree<T>&& rhs);

  /**
   * Puts a breadth-first traversal of the B-Tree onto the output
   * stream os. Elements must, in turn, support the output operator.
   * Elements are separated by space. Should not output any newlines.
   *
   * @param os a reference to a C++ output stream
   * @param tree a const reference to a B-Tree object
   * @return a reference to os
   */
  friend std::ostream& operator<< <T> (std::ostream& os, const btree<T>& tree);


  /**
   * The following can go here
   * -- begin() 
   * -- end() 
   * -- rbegin() 
   * -- rend() 
   * -- cbegin() 
   * -- cend() 
   * -- crbegin() 
   * -- crend() 
   */
  
    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

  /**
    * Returns an iterator to the matching element, or whatever 
    * the non-const end() returns if the element could 
    * not be found.  
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already 
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
    iterator find(const T& elem);
    
  /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
    const_iterator find(const T& elem) const;
      
  /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.  
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The 
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's zero-arg constructor and 
    * operator= method, and if these things aren't available, 
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field 
    *         stores true if and only if the element needed to be added 
    *         because no matching element was there prior to the insert call.
    */
    std::pair<iterator, bool> insert(const T& elem);
  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation. 
    * Check that your implementation does not leak memory!
    */
    ~btree();

  
private:    
  // The details of your implementation go here
    struct Node {
        Node(size_t _maxSize = 40, std::shared_ptr<Node> _parent = nullptr): 
            children(_maxSize+1), parent(_parent), maxSize(_maxSize) {};
        
        const bool isFull() const { return elems.size() == maxSize; }
        const size_t findIndex(const Node* node) const;
        const auto findInsert(const T& elem);
        const std::pair<int, bool> findInsertIndex(const T& elem) const;

        std::vector<T> elems;
        std::vector<std::shared_ptr<Node>> children;
        std::weak_ptr<Node> parent;
        size_t maxSize;
    };

    size_t maxSize;
    std::shared_ptr<Node> root_;
    Node *head_, *tail_;

    std::pair<typename btree<T>::iterator, bool> insertHelper(const T& elem, const std::shared_ptr<Node>& ptr);
    btree<T>::const_iterator findHelper(Node* node, const T& elem) const;
    btree<T>::iterator findHelper(Node* node, const T& elem);
    const std::shared_ptr<btree<T>::Node> copyNode(std::shared_ptr<Node> src, std::shared_ptr<Node> parent);
    Node* findTail(Node* n);
    Node* findHead(Node* n);
};

// default constructor
template<typename T>
btree<T>::btree(size_t maxNodeElems ) :
    maxSize(maxNodeElems), root_(nullptr),head_(nullptr), tail_(nullptr) {
        std::shared_ptr<Node> n = std::make_shared<Node>(Node{maxSize});
        root_ = n;
        head_ = n.get();
        tail_ = n.get();
    }

// desctructor
template<typename T>
btree<T>::~btree() {
  root_.reset();
}

// copy constructor
template<typename T>
btree<T>::btree(const btree<T>& original) : 
    maxSize(original.maxSize), 
    root_(copyNode(original.root_, nullptr)), 
    head_(findHead(root_.get())), 
    tail_(findTail(root_.get())) {
    }

// move constructor
template<typename T>
btree<T>::btree(btree<T>&& original) : 
    maxSize(original.maxSize), 
    root_(copyNode(original.root_, nullptr)), 
    head_(findHead(root_.get())), 
    tail_(findTail(root_.get())) {
        original.root_=nullptr;
        original.head_=nullptr;
        original.tail_=nullptr;
    }

// copy assignment
template<typename T> btree<T>& btree<T>::operator=(const btree<T>& rhs) {
    if (this != &rhs) {
        maxSize = rhs.maxSize;
        root_ = copyNode(rhs.root_, nullptr);
        head_ = findHead(root_.get());
        tail_ = findTail(root_.get());
    }
    return *this;
}

// move assignment
template<typename T> btree<T>& btree<T>::operator=(btree<T>&& rhs) {
    if (this != &rhs) {
        maxSize = rhs.maxSize;
        root_ = copyNode(rhs.root_, nullptr);
        head_ = findHead(root_.get());
        tail_ = findTail(root_.get());
        std::shared_ptr<Node> n = std::make_shared<Node>(Node{maxSize});
        rhs.root_ = n;
        rhs.head_ = n.get();
        rhs.tail_ = n.get();
    }
    return *this;
}

// output ostream
template<typename T> std::ostream& operator<<(std::ostream& os, const btree<T>& tree) {
    std::queue<typename btree<T>::Node*> q;
    q.push(tree.root_.get());
    while (!q.empty()) {
        typename btree<T>::Node* n = q.front();
        q.pop();
        auto v = n-> elems;
        for (auto vite = v.begin(); vite != v.end(); ++vite) {
            os << *vite << " ";
        }
        auto c = n->children;
        for (auto cite = c.begin(); cite != c.end(); ++cite) {
            if ((*cite) != nullptr) {
                q.push((*cite).get());
            }
        }
    }
    return os;
}

// deep copy all nodes of a tree recursively
template<typename T> const typename std::shared_ptr<typename btree<T>::Node> btree<T>::copyNode(std::shared_ptr<Node> src,  std::shared_ptr<Node> parent)  {
    std::shared_ptr<Node> n = std::make_shared<Node>(Node{maxSize, parent});
    for(size_t i = 0; i < src->elems.size(); ++i) {
        n->elems.push_back(src->elems.at(i));
    }
    for (size_t i = 0; i < maxSize + 1; ++i) {
        if (src->children.at(i) != nullptr) {
            n->children.at(i) = copyNode(src->children.at(i), n);
        }
    }
    return n;
}

// find the head of a tree
template<typename T> typename btree<T>::Node* btree<T>::findHead(Node* n) {
    if (n -> isFull()) {
        if (n -> children.at(0) == nullptr) {
            return n;
        } else {
            return findHead(n->children.at(0).get());
        }
    }
    return n;
}

// find a tail of a tree
template<typename T> typename btree<T>::Node* btree<T>::findTail(Node* n) {
    if (n->isFull()) {
        if (n->children.at(maxSize) == nullptr) {
            return n;
        } else {
            return findTail(n->children.at(maxSize).get());
        }
    }
    return n;
}

// find the index of a child in a node
template<typename T> const size_t btree<T>::Node::findIndex(const Node* node) const {
    auto e = std::find_if(children.begin(), children.end(), [node] (auto e) {
        return node == e.get();
    });
    return std::distance(children.begin(), e);
}

// find the index in value vector that would add in, return index and whether already existed
template<typename T> const std::pair<int, bool> btree<T>::Node::findInsertIndex(const T& elem) const {
    auto e = std::find_if(elems.begin(), elems.end(), [elem] (auto e) {
        return elem < e;
    });
    int idx = std::distance(elems.begin(), e);
    if (idx == 0) {
        if (elems.at(0) == elem) {
            return make_pair(0, true);
        }
    } else {
        if (elems.at(idx-1) == elem) {
            return make_pair(idx, true);
        }
    }
    return make_pair(idx, false);
}

// find the index in value vector that would add in, return iterator
template<typename T>
const auto btree<T>::Node::findInsert(const T& elem) {
    auto e = std::find_if(elems.begin(), elems.end(), [elem] (auto e) {
        return elem < e;
    });
    return e;
}

// non-const of find
template<typename T> typename btree<T>::iterator btree<T>::find(const T& elem) {
    return findHelper(root_.get(), elem);
}

// recursively find the iterator of a target
template<typename T> typename btree<T>::iterator btree<T>::findHelper(Node* node, const T& elem) {
    auto v = node->elems;
    auto first = std::lower_bound(v.begin(), v.end(), elem);
    size_t idx = std::distance(v.begin(), first); 
    if (first == v.end()) {
        if (node->children.back() != nullptr) {
            return findHelper(node->children.back().get(), elem);
        } else {
            return this->end();
        }
    } else {
        if (*first == elem) {
            return iterator(node, idx);
        } else {
            if (node->children.at(idx) != nullptr) {
                return findHelper(node->children.at(idx).get(), elem);
            }
            return this->end();
        }
    }
}

// recursively find the iterator of a target
template<typename T> typename btree<T>::const_iterator btree<T>::findHelper(Node* node, const T& elem) const {
    auto v = node->elems;
    auto first = std::lower_bound(v.begin(), v.end(), elem);
    size_t idx = std::distance(v.begin(), first); 
    if (first == v.end()) {                         //elem is greater any elements in this level
        if (node -> children.back() != nullptr) {           //go to next level to find
            return findHelper(node->children.back().get(), elem);
        } else {                //no result
            return this->cend();
        }
    } else {
        if (*first == elem) {       //find it!
            return const_iterator(node, idx);
        } else {                //to see whether no result of go to next level
            if (node->children.at(idx) != nullptr) {
                return findHelper(node->children.at(idx).get(), elem);
            }
            return this->cend();
        }
    }
}

// const version of find
template<typename T> typename btree<T>::const_iterator btree<T>::find(const T& elem) const {
    return findHelper(root_.get(), elem);
}

// insert the child in correct place in recursion
template<typename T> typename std::pair<typename btree<T>::iterator, bool> btree<T>::insertHelper(const T& elem, const std::shared_ptr<Node>& ptr) {
    int idx = ptr->findInsertIndex(elem).first;
    bool exist = ptr->findInsertIndex(elem).second;

    if (exist) {            //if elem is already existed
        return make_pair(iterator(ptr.get(), idx-1), false);
    }

    if (!ptr->isFull()) {           //not full yet, available to add in current level
        ptr->elems.insert(ptr->findInsert(elem), elem);
        return make_pair(iterator(ptr.get(), idx), true);
    } else {
        if (ptr->children.at(idx) == nullptr) {             // create a new child
            std::shared_ptr<Node> n = std::make_shared<Node>(Node{maxSize, ptr});
            n->elems.push_back(elem);
            ptr->children.at(idx) = n;
            if (elem > tail_->elems.back()) {
                tail_ = n.get();
            }
            if (elem < head_->elems.at(0)) {
                head_ = n.get();
            }
            return make_pair(iterator(n.get(), 0), true);
        } else {        //keep going for search
            return insertHelper(elem, ptr->children.at(idx));
        }
    }
}

template<typename T> std::pair<typename btree<T>::iterator, bool>
btree<T>::insert(const T& elem) {
        if (root_->elems.size() == 0) {     //if it's empty tree
            root_->elems.push_back(elem);
            return make_pair(iterator(root_.get()), true);
        }
        auto e = insertHelper(elem, root_);
        return e;
}
//iterator
template<typename T> typename btree<T>::reverse_iterator
btree<T>::rbegin() const {
    return reverse_iterator(end());
}

template<typename T> typename btree<T>::reverse_iterator
btree<T>::rend() const {
    return reverse_iterator(begin());
}

template<typename T> typename btree<T>::const_iterator
btree<T>::cbegin() const {
    return const_iterator(begin());
}

template<typename T> typename btree<T>::const_iterator
btree<T>::cend() const {
    return const_iterator(end());
}

template<typename T> typename btree<T>::const_reverse_iterator
btree<T>::crbegin() const {
    return const_reverse_iterator(end());
}

template<typename T> typename btree<T>::const_reverse_iterator
btree<T>::crend() const {
    return const_reverse_iterator(begin());
}

template<typename T> typename btree<T>::iterator
btree<T>::begin() const {
    return iterator(head_, 0);
}

template<typename T> typename btree<T>::iterator
btree<T>::end() const {
    return iterator(tail_, tail_->elems.size());
}

#endif
