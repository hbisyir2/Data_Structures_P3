// define your dynamic array list template class here

#ifndef _DYNAMIC_ARRAY_LIST_H_
#define _DYNAMIC_ARRAY_LIST_H_

#include "abstract_list.h"
#include <iostream>

template <typename T>
class DynamicArrayList: public AbstractList<T>
{
public:
	
	// Constructor
	DynamicArrayList();

	// Destructor
	~DynamicArrayList();

	// copy constructor
	DynamicArrayList(const DynamicArrayList & oldList);

	// copy assignment
	DynamicArrayList& operator=(DynamicArrayList oldList);

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
	void swap(DynamicArrayList<T>& x, DynamicArrayList<T>& y);

private:
	T* data;
	std::size_t count;
	long int max;
};

#include "dynamic_array_list.txx"

#endif // _DYNAMIC_ARRAY_LIST_H_