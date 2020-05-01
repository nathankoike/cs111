/*******************************************************************************
File: stack.cc

Author: Nathan Koike

Date: 28 February 2018

Assignment: Project 3

Description: Write an algorithm that solves a sudoku puzzle. Accepted inputs are
             numbers 1-9 and _. This is the code that operates the stack class
             and provides its methods.
*******************************************************************************/

#include <cassert>
#include "stack.h"

stack::stack()
{
  // there is nothing in the stack, so there is nothing for *_top to point to
  _top = NULL;
}

stack::~stack()
{
  while (!empty())
    pop();
}

stack & stack::operator=(const stack & rhs)
{
  if (this != &rhs) {
    while (!empty())
      pop();

    _top = stack(rhs)._top;
    }
  return *this;
}

stack::stack(const stack & orig)
{
  _top = NULL;
  for (node* p = orig._top; p != NULL; p = p -> next)
    push(p -> data);
}

void stack::push(const stack_element & item)
{
  node *p = new node; // make a new node
  p -> next = _top; // link the new node to * _top
  p -> data = item; // dill the new node with data
  _top = p; // move top over one
}


void stack::pop()
{
  assert(not empty());
  node * q = _top; // copy * _top
  _top = q -> next; // move * _top down one
  delete [] q; // delete the formerly top node
}

stack_element stack::top() const
{
  assert(not empty());
  return _top -> data;
}

bool stack::empty() const
{
  return _top == NULL;
}
