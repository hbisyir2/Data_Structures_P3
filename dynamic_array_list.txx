// implement your dynamic array list template class here

#include "dynamic_array_list.h"
#include <utility>
#include <stdexcept>

// Constructor
template <typename T>
DynamicArrayList<T>::DynamicArrayList(): data(nullptr), count(0), max(0)
{}

// Destructor
template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
  if(data != nullptr) delete [] data;
}

// Copy constructor
template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T> & oldArray)
{
  max = oldArray.max;
  count = oldArray.count;
  data = max ? new T[max] : nullptr;
  std::copy(oldArray.data, oldArray.data+oldArray.max, data);
}

// Copy assignment
template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> oldArray)
{
  swap(*this,oldArray);

  return *this;
}

// is empty
template <typename T>
bool DynamicArrayList<T>::isEmpty()
{
	if (count) return false;
	return true;
}

// get length
template <typename T>
std::size_t DynamicArrayList<T>::getLength()
{
	return count;
}

// insert
template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item)
{
	if (position < 0 || position > count) throw std::range_error("Invalid Insert Position");
	if (count == max) // increase max if necessary
	{
		//grow the items array
		T * oldData = data; 

		// Set max to 1 if it is zero, otherwise double it
		max = max ? max * 2 : 1;

		data = new T[max];
		if (max - 1 != 0) {


			for (int i = 0; i < max; i++) {
				data[i] = oldData[i];
			}

			if (oldData != nullptr) delete[] oldData;
		}
	}

	if (position != count)
	{
		//shift all entries if needed
		for (std::size_t i = count; i > position; i--) {
			data[i] = data[i - 1];
		}
	}


	// insert
	data[position] = item;
	count++;
}

// remove
template <typename T>
void DynamicArrayList<T>::remove(std::size_t position) 
{
	if (position < 0 || position >= count || count == 0) throw std::range_error("Invalid Remove Position");

	if (data[position]) count--;

	for (std::size_t i = position; i < max; i++)
	{
		data[i] = data[i + 1];
	}
}

// clear
template <typename T>
void DynamicArrayList<T>::clear()
{
	if (data != nullptr) delete[] data;
	count = 0;
	max = 0;
}

// get Entry
template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position)
{
	if (position < 0 || position >= count) throw std::range_error("Invalid Entry Position");
	return data[position];
}

// set Entry
template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
	if (position < 0 || position >= count) throw std::range_error("Invalid Entry Position");
	if (!data[position]) count++;
	data[position] = newValue;
}

// swap
template <typename T>
void DynamicArrayList<T>::swap(DynamicArrayList<T>& x, DynamicArrayList<T>& y)
{
	std::swap(x.max, y.max);
	std::swap(x.count, y.count);
	std::swap(x.data, y.data);
}