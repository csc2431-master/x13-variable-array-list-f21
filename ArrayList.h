//
// Interface Definition for the ArrayList Base Class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
using std::ostream;

template <typename ItemType>
class ArrayList {
public:
    ArrayList(size_t capacity);
    ArrayList(const ArrayList&);
    const ArrayList<ItemType>& operator=(const ArrayList&);
    ~ArrayList();

    // Other methods
    bool Get(size_t position, ItemType& item) const;
    int Find(const ItemType& item, size_t start = 0) const;
    bool Insert(size_t position, const ItemType& item);
    bool Replace(size_t position, const ItemType& item);
    bool Swap(size_t position1, size_t position2);
    bool Remove(size_t position, ItemType& item);
    void Clear();

    size_t Size() const;

    bool CheckConsistency() const;

    // Stream output
    friend ostream& operator<<(ostream& os, const ArrayList& list) {
        os << "[";
        for (size_t position = 0; position < list._size; position ++) {
            if (position > 0) {
                os << ", ";
            }
            os << list._array[position];
        }
        return os << "]";
    }

protected:
    // Resizeability
    virtual bool GrowCapacity() = 0;
    virtual void ShrinkCapacity() = 0;

    ItemType* _array;
    size_t _size;
    size_t _capacity;
};

/**
 * Constructor
 * Creates an empty list.
 */
template <typename ItemType>
ArrayList<ItemType>::ArrayList(size_t capacity) {
    this->_array = new ItemType[capacity];
    this->_size = 0;
    this->_capacity = capacity;
}

/**
 * Copy assignment operator
 * Enables deep copy assignment using the operator = overload.
 * Uses the copy constructor to copy the rhs.  Then swaps internals of
 * the copy with this.  By doing it this way, the old contents
 * of this will be automatically freed when the method finishes.
 * The running time of this method is the same as the copy
 * constructor , i.e. O(N)
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
template <typename ItemType>
const ArrayList<ItemType>& ArrayList<ItemType>::operator=(const ArrayList& rhs) {
    if (this != &rhs) {
        delete[] _array;
        _array = new ItemType[rhs._capacity];
        for (size_t i = 0; i < rhs._size; i ++) {
            _array[i] = rhs._array[i];
        }
        _size = rhs._size;
        _capacity = rhs._capacity;
    }
    return *this;
}

/**
 * Copy Constructor
 * Creates a deep copy of the list.
 * The running time of the whole method is O(N) time where N is the
 * length of the list
 * @param other the list to be copied
 */
template <typename ItemType>
ArrayList<ItemType>::ArrayList(const ArrayList& other) {
    this->_array = new ItemType[other._capacity];
    for (size_t i = 0; i < other._size; i ++) {
        this->_array[i] = other._array[i];
    }
    this->_size = other._size;
    this->_capacity = other._capacity;
}



/**
 * Destructor
 * Frees the dynamic memory allocated for the list
 */
template <typename ItemType>
ArrayList<ItemType>::~ArrayList() {
    delete[] _array;
}

/**
 * Get  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the item found at position
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Get(size_t position, ItemType& item) const {
    if (position < _size) {
        item = _array[position];
        return true;
    }
    return false;
}

/**
 * Searches for the position of the first matching item in the list starting
 * at position "start".  The method performs a linear search for the item.
 * If the element is found it returns the position, if it is not found it
 * returns -1.
 * The running time of this method depends on where the search starts
 * and where the item is found (if it is found)
 * @param item the object that the client is searching for.
 * @param start position at which to start the search
 * @return the position of the element if found, -1 otherwise.
 */
template <typename ItemType>
int ArrayList<ItemType>::Find(const ItemType& item, size_t start)  const {
    for (size_t i = start; i < _size; i++) {
        if (_array[i] == item) {
            return i;
        }
    }
    return -1;
}

/**
 * Inserts an element into a given position so long as the position is valid
 * and the list is not filled to capacity.
 * THe running time of inserting at the start is O(N), it's O(1) if you are
 * inserting at the end.
 * @param item what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise.
 */
template <typename ItemType>
bool ArrayList<ItemType>::Insert(size_t position, const ItemType& item) {
    if (position > _size) {
        return false;
    }
    else
    {
        if (_size == _capacity && !GrowCapacity()) {
            return false;
        }

        // Shift out elements to make room for insertion
        for (size_t i = _size; i > position; i --) {
            _array[i] = _array[i-1];
        }
        // Insert the element
        _array[position] = item;
        _size ++;
        return true;
    }
}

/**
 * Replace  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the new item to insert in the old one's place
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Replace(size_t position, const ItemType& item) {
    if (position < _size) {
        _array[position] = item;
        return true;
    }
    return false;
}


/**
 * Swap elements in specified positions
 * This method runs in O(1) time.
 * @param position1 the position of the first element
 * @param position2 the position of the second element
 * @return true if valid positions were given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Swap(size_t position1, size_t position2) {
    if (position1 < _size && position2 < _size) {
        ItemType tmp;

        tmp = _array[position1];
        _array[position1] = _array[position2];
        _array[position2] = tmp;
        return true;
    }
    return false;
}

/**
 * Removes the item at position, so long as the position is valid. The item previously
 * stored in the list is returned in the supplied parameter.
 * THe running time of removing the first element is  O(N), it's O(1) if you are
 * removing the last element.
 * @param position the position of the element to be removed.
 * @param item the item previously stored in the list
 * @return true if node could be deleted, false if position at end of list or invalid,
 */
template <typename ItemType>
bool ArrayList<ItemType>::Remove(size_t position, ItemType& item) {
    if (position >= _size) {
        return false;
    }
    else {
        item = _array[position];

        // Close up the gap
        for (size_t i = position; i < _size-1; i ++) {
            _array[i] = _array[i+1];
        }
        _size--;

        ShrinkCapacity();

        return true;
    }
}

/**
 * Clear the list
 * and then resetting _head to nullptr.
 * This method runs in O(1) time
 * There is no need to free the string values
 * that will occur when the class destructs
 */
template <typename ItemType>
void ArrayList<ItemType>::Clear() {
    _size = 0;
}

/**
 * Returns the number of itmes in the array
 * This method runs in O(1) time
 * @return current number of items in array
 */
template <typename ItemType>
size_t ArrayList<ItemType>::Size() const {
    return _size;
}

/**
 * Checks if list data structure appears to be consistent
 * @return true if list consistent, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::CheckConsistency() const {
    return _size <= _capacity;
};

#endif //ARRAYLIST_H
