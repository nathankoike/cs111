/******************************************************************************
*                                                                             *
* list.cc                                                                     *
* Nathan Koike                                                                *
* Project 2                                                                   *
* 3/30/18                                                                     *
*                                                                             *
* this program manages the list data structure and allows the user to interact*
* with the list(s) created                                                    *
******************************************************************************/
#include "list.h"

// List node constructors provided by Prof. Campbell

list_node::list_node() : prev(NULL), next(NULL) {}

list_node::list_node(list_node *p, list_node *n) : prev(p), next(n) {}

list_node::list_node(list_node *p, const list_element & d, list_node * n):
  prev(p), data(d), next(n) {}

// List constructors/destructor/assignment also provided.
// No need to change these.

list::list()
// initialize a new list with no data
{
  _init();
}

list::~list()
// destroys the list so that (hopefully) there are no memory leaks
{
  _destroy();
}

list::list(const list & orig)
// create a list to be an exact copy of another list
{
  _init();
  _copy(orig);
}

list & list::operator=(const list & rhs)
// overload the = operator so the existing list on the left is an exact copy of
// the list on the right
{
  if (this != &rhs) {
    _copy(rhs);
  }

  return *this;
}

// List method stubs provided.  Here's where you come in. You delete this
// comment and fill in the method bodies.

void list::_init()
// initialize a new list with no nodes other than the sentinels
{
  // make new nodes for the front and the rear sentinels
  _front = new list_node;
  _rear = new list_node;

  // link the sentinels to each other
  _front->next = _rear;
  _rear->prev = _front;
  _front->prev = _rear->next = NULL;

  // set the size to be 0 and make the current pointer NULL. the current index
  // should also be 0
  _size = 0;
  _current = NULL;
  _current_index = 0;
}

void list::_copy(const list & orig)
// copy the nodes between the sentinels in a list
{
  _destroy();
  _init();

  for (list_node* p = orig._front->next; p != orig._rear and
      p != orig._rear; p = p->next)
    {
      add(p->data, _size);
      if (_size == orig._current_index)
        {
          _current_index = _size;
          _current = _rear->prev;
        }
    }
}

void list::_destroy()
// destroys all the nodes in a list including the sentinels
{
  if (size())
    for (; 0 < size();)
      remove_at(0);

  delete _rear;
  delete _front;
}

void list::add(const list_element & item, int index)
// adds a new node at the specified index and moves every other node back one
// index value
{
  if (_size > 0 && index != 0)
  {
    // find and set the index where the new node should go
    size_t i = index > 0? index: size() + index;
    _set_current_index(i);

    // make a new node and attach it to the list
    list_node* temp = new list_node(_current->prev, item, _current);

    // allow the new node to go between two existing nodes and finish attaching
    // the node to the list
    _current->prev->next = temp;
    _current->prev = temp;

    // increment the current index so it lines up with the node that _current is
    // pointing to
    _current_index++;
  }

  else
  {
    // make a new node and attach it to the front of the list behind the front
    // sentinel
    _front->next = new list_node(_front, item, _front->next);

    // attach the node behind the front sentinel to the new node
    _front->next->next->prev = _front->next;

    // set the current index to 0 for safety
    _set_current_index(0);
  }

  _size++;
}

void list::remove_at(int index)
// removes the node at the specified index
{
  // find and set the index where the node should be removed
  size_t i = index >= 0? index: size() + index;
  _set_current_index(i);

  // do not attempt to remove a node that is at an index larger than that which
  // is contained by the list
  if (i >= size())
    return;

  // make pointers to allow detatching the node from the list to be easier
  list_node* nextNode = _current->next;
  list_node* prevNode = _current->prev;

  // detatch the node from the list
  prevNode->next = nextNode;
  nextNode->prev = prevNode;

  _size--;

  delete _current;

  // _current has just been deleted, so set the current index to 0 for safety
  _set_current_index(0);
}

void list::remove(const list_element & item)
// finds the item in the list if possible and removes it
{
  size_t index = (find(item));
  if (index != size())
    remove_at(index);
}

size_t list::find(const list_element & item) const
// finds the index value of the item and returns it. returns size() if the item
// is not in the list
{
  _current = _front->next;
  _current_index = 0;

  // march through the list and return the first instance of the data
  for (; _current->next != _rear; _advance())
  {
    if (_current->data == item)
      return _current_index;
  }

  // if the data cannot be found return the size of the list
  return size();
}

list_element list::get(int index) const
// gets the data at the specified index
{
  // find and set the index where the new node should go
  size_t i = index >= 0? index: size() + index;
  _set_current_index(i);

  return _current->data;  // same type as list_element
}

size_t list::size() const
// returns the size of the list
{
  return _size;
}

void list::output(std::ostream & ostr) const
// writes the list to the specified output stream
{
  ostr << '<'; // make the start of the output look pretty

  // march through the list adding a ", " before every element that is not the
  // first one
  for (size_t i = 0; i < size(); i++)
    {
      if (i > 0)
        ostr << ", ";
      ostr << get(i);
    }

  ostr << '>'; // make the end of the output look pretty but do not end the line
}

void list::_set_current_index(size_t index) const
// sets the current index and current node to be the node at the specified index
{
  /*
  A message to myself and the readers of this code:

  I planned to add a way to move the current index from its current location,
  but I ran out of time. I will add this later. Adding this will improve the
  runtime of this code, but it does operate in its current state.

  -Nate Koike
  */

  // check to see if it is faster to set the current index from the front of the
  // list
  if(size() == 0 || size() - 1 - index > index)
  {
    // set the current index to be the first node in the list that is not the
    // front sentinel
    _current_index = 0;
    _current = _front->next;

    // march up the list until _current_index matches the value of index
    while (_current_index != index)
      _advance();
  }

  else
  {
    // set the current index to be the last node in the list that is not the
    // rear sentinel
    _current_index = size() - 1;
    _current = _rear->prev;

    // march down the list until _current_index matches the value of index
    while (_current_index != index)
      _retreat();
  }
}

void list::_advance() const
// moves the current index up once
{
  _current_index++;
  _current = _current->next;
}

void list::_retreat() const
// moves the current index down once
{
  _current_index--;
  _current = _current->prev;
}
