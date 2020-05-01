/*******************************************************************************
File: stack.h

Author: Nathan Koike

Date: 28 February 2018

Assignment: Project 3

Description: Write an algorithm that solves a sudoku puzzle. Accepted inputs are
             numbers 1-9 and _. This is the header file for the stack class.
*******************************************************************************/

#include <iostream>

typedef size_t stack_element;

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
