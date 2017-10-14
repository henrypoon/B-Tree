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
template<typename T> ostream &operator<<(ostream&, btree<T>&);

template <typename T> 
class btree {
public:
  /** Hmm, need some iterator typedefs here... friends? **/
    // friend class btree_iterator<T>;
    // friend class const_btree_iterator<T>;
    // typedef btree_iterator<T> iterator;
    // typedef btree_iterator<T> const_iterator;
    // typedef std::reverse_iterator<iterator> reverse_iterator;
    // typedef std::reverse_iterator<const_iterator> const_reverse_iterator; 
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
  friend std::ostream& operator<< <T> (std::ostream& os, btree<T>& tree);


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
    void printAll() const;
    size_t getTotalSize() {return totalSize;}
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
        // Node(size_t _maxSize = 40): 
        //     maxSize(_maxSize){};

        Node(size_t _maxSize = 40, std::shared_ptr<Node> _parent = nullptr): 
            children(_maxSize+1), parent(_parent), maxSize(_maxSize) {};
        

        T& getVal(size_t idx) { return elems.at(idx); }
        const size_t getSize() const { return elems.size(); }

        const T& getLargest() const { return elems.back(); }

        std::shared_ptr<Node> getChild(size_t idx) const {return children.at(idx);}
        const std::shared_ptr<Node> getLast() const {return children.back();}
        const size_t getMaxSize() const {return maxSize; }
        std::shared_ptr<Node> getParent() const {return parent.lock();}

        // void insertNode(size_t idx, std::shared_ptr<Node>& n) {children.at(idx) = n; }

        void insertVal(const T& elem) {
            elems.push_back(elem); 
        }
        void insertValAt(const typename std::vector<T>::iterator pos, const T& elem) {
            elems.insert(pos, elem);
        }

        void insertChildAt(const std::shared_ptr<Node>& node, size_t idx) {
            children.at(idx) = node;
        }

        const std::vector<T> getElems() const {return elems; }
        const std::vector<std::shared_ptr<Node>> getChildren() const {return children; }

        const bool isFull() const {
            return elems.size() == maxSize; 

        }

        void clear() noexcept;
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
    size_t totalSize;
    std::pair<typename btree<T>::iterator, bool> insertHelper(const T& elem, const std::shared_ptr<Node>& ptr);
    btree<T>::const_iterator findHelper(Node* node, const T& elem) const;
    btree<T>::iterator findHelper(Node* node, const T& elem);
    const std::shared_ptr<btree<T>::Node> copyNode(std::shared_ptr<Node> src, std::shared_ptr<Node> parent);
    Node* findTail(Node* n);
    Node* findHead(Node* n);
};

#include "btree.tem"

#endif
