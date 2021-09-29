//
// Interface Definition for the FixedArrayList Class as a derived class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef FIXEDARRAYLIST_H
#define FIXEDARRAYLIST_H

#include "ArrayList.h"

template <typename ItemType>
class FixedArrayList : public ArrayList<ItemType>  {
public:
    FixedArrayList(size_t capacity)
        : ArrayList<ItemType>(capacity) {};

private:
    bool GrowCapacity() override;
    void ShrinkCapacity() override;
};

/**
 * Grow the capacity of the array
 * Since this is a fixed array, this does nothing but return false
 * @return false
 */
 template <typename ItemType>
bool FixedArrayList<ItemType>::GrowCapacity() {
    return false;
}

/**
 * Shrink the capacity of the array
 * Since this is a fixed array, this does nothing
 */
 template <typename ItemType>
void FixedArrayList<ItemType>::ShrinkCapacity() {
}


#endif //FIXEDARRAYLIST_H
