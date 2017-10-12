#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template<typename T> class btree;
template<typename T> class btree_iterator;
template<typename T> class const_btree_iterator;

template<typename T> class btree_iterator {
public:
	typedef std::ptrdiff_t                     difference_type;
	typedef std::forward_iterator_tag          iterator_category;
	typedef T                                  value_type;
	typedef T*                                 pointer;
	typedef T&                                 reference;

	friend class const_btree_iterator<T>;

	reference			operator*() const;
	pointer				operator->() const { return &(operator*()); }
	btree_iterator& 	operator++();
	btree_iterator&		operator--();
	bool				operator==(const btree_iterator& b) const;
	bool				operator!=(const btree_iterator& b) const;
	btree_iterator&		operator =(const btree_iterator& b);

	btree_iterator(typename btree<T>::Node *pointee_=nullptr, size_t index_ = 0, bool _isEnd = false): pointee(pointee_), index(index_), isEnd(_isEnd) {}

private:
    void findFirstChild();
    void findLastChild();
    void findFirstParent();
    void findLastParent();
	typename btree<T>::Node *pointee;
	size_t index;
	bool isEnd;
};


template<typename T> class const_btree_iterator {
public:
	typedef std::ptrdiff_t                     difference_type;
	typedef std::forward_iterator_tag          iterator_category;
	typedef T                                  value_type;
	typedef const T*                           pointer;
	typedef const T&                           reference;

	friend class btree_iterator<T>;

	reference			operator*() const;
	pointer				operator->() const { return &(operator*()); }
	const_btree_iterator& 	operator++();
	const_btree_iterator&		operator--();
	bool				operator==(const const_btree_iterator& b) const;
	bool				operator!=(const const_btree_iterator& b) const;
	const_btree_iterator&		operator =(const const_btree_iterator& b);

	const_btree_iterator(typename btree<T>::Node *pointee_=nullptr, size_t index_ = 0, bool _isEnd = false): pointee(pointee_), index(index_), isEnd(_isEnd) {}

private:
    void findFirstChild();
    void findLastChild();
    void findFirstParent();
    void findLastParent();
	typename btree<T>::Node *pointee;
	size_t index;
	bool isEnd;
};

#include "btree_iterator.tem"

#endif
