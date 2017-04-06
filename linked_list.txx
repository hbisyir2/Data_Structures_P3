// implement your linked list template class here

#include "linked_list.h"
#include <utility>
#include <stdexcept>

// Constructor
template <typename T>
LinkedList<T>::LinkedList() : first(nullptr), count(0) {}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
	while (first != nullptr) {
		Node<T> * temp = first;
		first = first->next;
		delete temp;
	}
}

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& oldList) : first(nullptr), count(0)
{
	Node<T> * x_curr = oldList.first;
	Node<T> * this_prev = nullptr;

	while (x_curr != nullptr) {
		Node<T> * this_curr = new Node<T>(x_curr->items);
		this_curr->prev = this_prev;
		if (this_prev != nullptr) this_prev->next = this_curr;
		else first = this_curr;
		this_prev = this_curr;
		x_curr = x_curr->next;
		count++;
	}

}

// swap
template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
	std::swap(x.first, y.first);
	std::swap(x.count, y.count);
}

// Copy operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> oldList)
{
	swap(*this, oldList);
	return *this;
}

// is empty
template <typename T>
bool LinkedList<T>::isEmpty()
{
	if (count) return false;
	return true;
}

// get length
template <typename T>
std::size_t LinkedList<T>::getLength()
{
	return count;
}

// insert
template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
	if (position < 0 || position > count) throw std::range_error("Invalid Insert Position");
	Node<T> * current = first;
	Node<T> * temp = first;
	Node<T> * newItem = new Node<T>(item);
	// make new head if inserting at first position
	if (position == 0) {
		newItem->prev = nullptr;
		newItem->next = first;
		first = newItem;
	}
	// create new end if position is at the end of the list
	else if (position == count) {
		for (std::size_t i = 0; i < position - 1; i++) {
			current = current->next;
		}
		newItem->prev = current;
		newItem->next = nullptr;
		current->next = newItem;
	}
	// inserts in between list values
	else {
		for (std::size_t i = 0; i < position - 1; i++) {
			current = current->next;
		}
		temp = current->next;
		current->next = newItem;
		newItem->prev = current;
		temp->prev = newItem;
		newItem->next = temp;
	}
	count++;
}

// remove
template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
	if (position < 0 || position >= count || count == 0) throw std::range_error("Invalid Remove Position");
	Node<T> * current = first;
	Node<T> * replace = first;
	// creates new head if removing first position
	if (position == 0) {
		current = current->next;
		if (current != nullptr) current->prev = nullptr;
		first = current;
	}
	// if a second item does exist
	else if (current->next != nullptr) {
		// move to position-1 in list
		for (std::size_t i = 0; i < position-1; i++) {
			current = current->next;
		}
		// goes two places forward and stores in a new temp called replace
		replace = current->next;
		if (replace->next != nullptr) {
			// connects the two temporary nodes,
			// bypassing the removed item
			replace = replace->next;
			current->next = replace;
			replace->prev = current;
		}
		else {
			current->next = nullptr;
		}
		if (position + 1 != count) replace->prev = current;
	}
	else {
		first = nullptr;
	}
	count--;
}

// clear
template <typename T>
void LinkedList<T>::clear()
{
	while (first != nullptr) {
		Node<T> * temp = first;
		first = first->next;
		delete temp;
	}
	first = nullptr;
	count = 0;
}

// get Entry
template <typename T>
T LinkedList<T>::getEntry(std::size_t position)
{
	if (position < 0 || position >= count) throw std::range_error("Invalid Entry Position");
	Node<T> * current = first;
	for (std::size_t i = 0; i < position; i++) {
		current = current->next;
	}
	return current->items;
}

// set Entry
template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
	if (position < 0 || position >= count) throw std::range_error("Invalid Entry Position");
	Node<T> * current = first;
	for (std::size_t i = 0; i < position; i++) {
		current = current->next;
	}
	current->items = newValue;
}