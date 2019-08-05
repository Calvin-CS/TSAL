#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>

// This class needs work
namespace tsal {

/** @class Buffer
 * @brief A generic buffer class
 *
 * When working with audio data, it it sometimes necessary to store 
 * the data in a buffer.
 */
template <typename Item>
class Buffer {
  public:
    Buffer(unsigned size);
    Item size() const { return mSize; };

    const Item& operator[](int index) const;
    Item& operator[](int index);
    
    void resize(unsigned size);
  private:
    unsigned mSize = 0;
    Item* mBufferArray = nullptr;
};

template <typename Item>
Buffer<Item>::Buffer(unsigned size) {
  resize(size);
}

template <typename Item>
const Item& Buffer<Item>::operator[](int index) const {
  return mBufferArray[index];
}

template <typename Item>
Item& Buffer<Item>::operator[](int index) {
  return mBufferArray[index];
}

template <typename Item>
void Buffer<Item>::resize(unsigned size) {
  if (mBufferArray != nullptr) {
    delete[] mBufferArray;
  }
  mSize = size;
  mBufferArray = new Item[size];
  for (unsigned i = 0; i < mSize; i++) {
    mBufferArray[i] = Item();
  }
}

}
#endif
