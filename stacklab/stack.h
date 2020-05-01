#include <iostream>

typedef int stack_element;

class stack {
 private:
  struct node {
    stack_element data;
    node * next;
  };

  node * _top;
  
 public:
  stack();  // no-arg constructor
  stack(const stack &);  // copy constructor
  ~stack();  // destructor
  stack & operator=(const stack &); // assignment operator
  void push(const stack_element &);
  void pop();
  stack_element top() const;
  bool empty() const;
};
