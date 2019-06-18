#include <memory>

#ifndef BUFFER_H
#define BUFFER_H

namespace tsal {

template <typename Item>
class Buffer {
  public:
    Buffer(unsigned size);
    Item size() const { return mSize; };

    const Item& operator[](int index) const;
    Item& operator[](int index);
  private:
    int getCircularIndex(int index);
    unsigned mSize = 0;
    std::unique_ptr<Item[]> mBufferArray; 
};

template <typename Item>
Buffer<Item>::Buffer(unsigned size){
  mSize = size;
  mBufferArray = std::make_unique<Item[]>(size);
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
  return (index < 0) ? mSize + index : index % mSize;
}

}
#endif
