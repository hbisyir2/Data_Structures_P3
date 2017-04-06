// define your linked list template class here

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "abstract_list.h"
#include <iostream>

template <typename T>
class LinkedList : public AbstractList<T>
{
public:

	// Constructor
	LinkedList();

	// Destructor
	~LinkedList();

	// copy constructor
	LinkedList(const LinkedList & oldList);

	// copy assignment
	LinkedList& operator=(LinkedList oldList);

	// returns true if list is empty
	bool isEmpty();

	// Returns size of array
	std::size_t getLength();

	// insert item at position
	void insert(std::size_t position, const T& item);

	// remove list data at position
	void remove(std::size_t position);

	// clears all data from list
	void clear();

	// returns data at position
	T getEntry(std::size_t position);

	// sets data at position to new value
	void setEntry(std::size_t position, const T& newValue);

	//for copy-swap idiom used in copy operator
	void swap(LinkedList<T>& x, LinkedList<T>& y);
private:

	template<typename U>
	struct Node {
		U items;
		Node<U> * next;
		Node<U> * prev;

		Node() : next(nullptr), prev(nullptr) {};
		Node(const U& d) : items(d), next(nullptr), prev(nullptr) {};
	};

	Node<T> * first;
	std::size_t count;
};

#include "linked_list.txx"

#endif // _LINKED_LIST_H_