#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

template<typename T> class btree;
template <typename Base, template <typename U> class Constness> class btree_iterator;
// template<typename T> class const_btree_iterator;

template <typename T>
struct Identity {
  using type = T;
};

template <typename Base, template <typename U> class Constness = Identity> class btree_iterator {
	using T = typename Constness<Base>::type;
public:
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	// friend class const_btree_iterator<T>;

	reference			operator*() const { return pointee->getVal(index);};
	pointer				operator->() const { return &(operator*()); }
	btree_iterator& 	operator++();
	btree_iterator&		operator--();
	btree_iterator	operator++(int);
	btree_iterator	operator--(int);
	// btree_iterator&		operator =(const btree_iterator<Base, Constness>& b);
	bool				operator==(const btree_iterator& b) const;
	bool				operator!=(const btree_iterator& b) const;
	operator btree_iterator<Base, std::add_const>() {
        return btree_iterator<Base, std::add_const>{pointee, index};
    };
	// friend bool	operator==<>(const btree_iterator<Base, Constness>& a, const btree_iterator<Base, Constness>& b);
	// friend bool	operator!=<>(const btree_iterator<Base, Constness>& a, const btree_iterator<Base, Constness>& b);

	btree_iterator(typename btree<Base>::Node *pointee_=nullptr, size_t index_ = 0, bool _isEnd = false): pointee(pointee_), index(index_), isEnd(_isEnd) {}

private:
    void findFirstChild();
    void findLastChild();
    void findFirstParent();
    void findLastParent();
	typename btree<Base>::Node *pointee;
	size_t index;
	bool isEnd;
};





#include "btree_iterator.tem"

#endif
