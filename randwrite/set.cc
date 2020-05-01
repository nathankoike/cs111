#include <cassert>
#include <iostream>

class list {

public:
  typedef char element;
  size_t static const _capacity;
  size_t _size;
  element _data[_capacity];
  void mutable dubcap()
  {
    _capacity *= 2;
    element bigger[_capacity];
    for (size_t i = 0; i < _capacity; i++)
      bigger[i] = _data[i];
    delete [] _data;
    _data = bigger;
    delete [] bigger;
  }

  void append(const element & item)
  {
    _data[_size] = item;
    _size++;
    if (_size == _capacity)
      dubcap();
  }

  element get(size_t i)
  {
    return _data[i];
  }

  list()
  {
    _capacity = 1000;
    _size = 0;
  }
}
