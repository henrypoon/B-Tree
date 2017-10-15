#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

template<typename T> class btree;
template <typename Base, template <typename U> class Constness> class btree_iterator;

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

	reference			operator*() const { return pointee->elems.at(index);};
	pointer				operator->() const { return &(operator*()); }
	btree_iterator& 	operator++();
	btree_iterator&		operator--();
	btree_iterator		operator++(int);
	btree_iterator		operator--(int);
	bool				operator==(const btree_iterator& b) const;
	bool				operator!=(const btree_iterator& b) const;
	operator btree_iterator<Base, std::add_const>() {
        return btree_iterator<Base, std::add_const>{pointee, index};
    };
	btree_iterator(typename btree<Base>::Node *pointee_=nullptr, size_t index_ = 0, bool _isEnd = false): pointee(pointee_), index(index_), isEnd(_isEnd) {}

private:
    void findNextChild();
    void findLastChild();
    void findLastParent();
    void findNextParent();
	typename btree<Base>::Node *pointee;		//pointer of current node
	size_t index;			//current index
	bool isEnd;		//flag for knowing whether is the end
};

// pre increment
template <typename Base, template <typename U> class Constness>
btree_iterator<Base, Constness>& btree_iterator<Base, Constness>::operator++() {
	if (pointee->children.at(index + 1) != nullptr) {
		pointee = pointee->children.at(index + 1).get();
		findNextChild();
		return *this;
	} else {
		if (index == pointee->elems.size() - 1) {
			typename btree<Base>::Node* temp = pointee;
			findNextParent();
			if (isEnd) {
				pointee = temp;
				index = pointee->elems.size();
			}
			return *this;
		} else {
			++index;
			return *this;
		}
	}
	return *this;
}

// pre decrement
template <typename Base, template <typename U> class Constness>
btree_iterator<Base, Constness>& btree_iterator<Base, Constness>::operator--() {
	if (pointee->children.at(index) != nullptr) {
		pointee = pointee->children.at(index).get();
		findLastChild();
		return *this;
	} else {
		if (index == 0) {
			typename btree<Base>::Node* temp = pointee;
			findLastParent();
			if (isEnd) {
				pointee = temp;
				index = 0;		
			}
			return *this;
		} else {
			--index;
			return *this;
		}
	}
	return *this;
}

//post increment
template <typename Base, template <typename U> class Constness> 
btree_iterator<Base, Constness> btree_iterator<Base, Constness>::operator ++(int){
	btree_iterator r = *this;
	operator ++();
	return r;
}

//post decrement
template <typename Base, template <typename U> class Constness> 
btree_iterator<Base, Constness> btree_iterator<Base, Constness>::operator --(int){
	btree_iterator r = *this;
		operator --();
		return r;
}

// go to upper level to find next one
template <typename Base, template <typename U> class Constness>
void btree_iterator<Base, Constness>::findLastParent() {
	while (pointee->parent.lock().get() != nullptr) {
		auto parent = pointee->parent.lock().get();
		size_t i = parent->findIndex(pointee);
		if (i != 0) {
			pointee = parent;
			index = i - 1;
			return;
		}
		pointee = parent;
	}
	isEnd = true;
}

// go to lower level to find next one
template <typename Base, template <typename U> class Constness>
void btree_iterator<Base, Constness>::findNextChild(){
	while (pointee->children.at(0).get() != nullptr) {
		pointee = pointee->children.at(0).get();
	}
	index = 0;
}

// go to lower level to find last one
template <typename Base, template <typename U> class Constness>
void btree_iterator<Base, Constness>::findLastChild(){
	while (pointee->children.back().get() != nullptr) {
		pointee = pointee->children.back().get();
	}
	index = pointee->elems.size() - 1;
}

// go to upper level to find last one
template <typename Base, template <typename U> class Constness>
void btree_iterator<Base, Constness>::findNextParent(){
	while (pointee->parent.lock().get() != nullptr) {
		auto parent = pointee->parent.lock().get();
		size_t i = parent->findIndex(pointee);
		if (i != pointee->maxSize) {
			pointee = parent;
			index = i;
			return;
		}
		pointee = parent;
	}
	isEnd = true;
}

template <typename Base, template <typename U> class Constness>
bool btree_iterator<Base, Constness>::operator ==(const btree_iterator& b) const {
	return (pointee == b.pointee && index == b.index);
}

template <typename Base, template <typename U> class Constness>
bool btree_iterator<Base, Constness>::operator !=(const btree_iterator& b) const {
	return !operator==(b);
}

#endif
