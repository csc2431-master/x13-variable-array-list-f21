//
// Interface Definition for a VariableArrayList Class derived from a base class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef VARIABLEARRAYLIST_H
#define VARIABLEARRAYLIST_H

#include "ArrayList.h"

template <typename ItemType>
class VariableArrayList : public ArrayList<ItemType>  {
public:
    VariableArrayList()
        : ArrayList<ItemType>(1) {};

    // Added method for testing
    size_t Capacity() const {
        return this->_capacity;
    }

private:
    bool GrowCapacity() override;
    void ShrinkCapacity() override;
};

/**
 * Doubles the size of the array allocation
 * This is meant to be called when array is full.
 * @return success
 */
template <typename ItemType>
bool VariableArrayList<ItemType>::GrowCapacity() {
    ItemType* newArray;

    assert(this->_size == this->_capacity);
    newArray = new ItemType[2*this->_capacity];
    for (size_t i = 0; i < this->_size; i ++) {
        newArray[i] = this->_array[i];
    }
    delete[] this->_array;
    this->_array = newArray;
    this->_capacity *= 2;
    return true;
}

/**
 * Check if array allocation should be reduced
 * If using less than 1/4 capacity, halves the size of allocation.
 */
template <typename ItemType>
void VariableArrayList<ItemType>::ShrinkCapacity() {
    if (this->_size > 0 && 4*this->_size <= this->_capacity) {
        ItemType* newArray;

        newArray = new ItemType[this->_capacity/2];
        for (size_t i = 0; i < this->_size; i ++) {
            newArray[i] = this->_array[i];
        }
        delete[] this->_array;
        this->_array = newArray;
        this->_capacity /= 2;
    }
}


#endif //VARIABLEARRAYLIST_H
