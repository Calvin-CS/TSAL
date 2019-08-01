#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

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
    Item size() const { return mBufferArray.size(); };

    const Item& operator[](int index) const;
    Item& operator[](int index);
  private:
    int getCircularIndex(int index);
    std::vector<Item> mBufferArray;
};

template <typename Item>
Buffer<Item>::Buffer(unsigned size) : mBufferArray(size) {
}

template <typename Item>
const Item& Buffer<Item>::operator[](int index) const {
  return mBufferArray[getCircularIndex(index)];
}

template <typename Item>
Item& Buffer<Item>::operator[](int index) {
  return mBufferArray[getCircularIndex(index)];
}

template <typename Item>
int Buffer<Item>::getCircularIndex(int index) {
  // The "true" modulo operation. Works on negative values
  return ((index % mBufferArray.size()) + mBufferArray.size()) % mBufferArray.size();
}

}
#endif
