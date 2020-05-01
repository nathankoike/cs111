#include <iostream>

typedef char set_element;

class list {
 private:
  static const size_t _capacity = 100;
  set_element _data[_capacity];
  size_t _size;
  void _double_capacity();

 public:
  list();
  void add(const set_element &);
  bool contains(const set_element &) const;
  void print(std::ostream &) const;
  size_t size();
  set_element get(size_t i);
};

std::ostream & operator<<(std::ostream &, const list &);
