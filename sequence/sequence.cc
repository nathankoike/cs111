/************************************************************************
    File: sequence.cc
    Author: Your name here
    Date: Date
    Assignment:  Lab 1 (sequence)

    Implementation of a simple array-based sequence class.

************************************************************************/
#include <iostream>
#include "sequence.h"

using namespace std;

/*** Constructor ***/
sequence::sequence()
{
  // Initializes this sequence with 0 elements
  _size = 0;
}

/*** const member functions ***/


size_t sequence::size() const
{
  // return the number of elements in this sequence
  return _size;
}

bool sequence::empty() const
{
  // return true if this sequence has no elements, false otherwise.
  return _size == 0;
}

bool sequence::full() const
{
  // return true if this sequence has _capacity elements, false otherwise.
  return _size == _capacity;
}

void sequence::print() const
{
  // Produce output with cout: a single open square bracket, the elements
  // of the sequence, separated by commas and spaces, followed by a single
  // close square bracket.  No newline.
  // Examples of output:
  //  []
  //  [6]
  //  [9, -1, 4]
  cout << '[';

  // this for loop prints every element and prints ", " before every element
  // except the first one
  for (size_t i = 0; i < _size; i++)
  {
    // this if/else structure just checks to see if the element the for loop is
    // looking at is the first one
    if (i == 0)
      cout << _data[i];
    else
      cout << ", " << _data[i];
  }
  cout << ']';
}

int sequence::get(size_t position) const
{
  // Precondition:  position < size()
  // Return the element at the given position.
  return _data[position];
}

size_t sequence::getLongestRun() const
{
  // Determine the length of the longest run of two or more identical adjacent
  // elements of this sequence.  Return the smallest starting position of a
  // run with this length.  If no such run occurs, return size().
  // (This method may use auxiliary stand-alone functions, but, again, you
  // cannot change this  file.  This means that you cannot define auxiliary
  // methods.)

  size_t longest = 0;
  size_t start = 0;
  // this array is meant to hold both the length of the longest run and its
  // start for comparison within the for loop
  size_t long_start[2] = {0, 0};

  if (_size > 1)
    // this for loop looks through _data to find and compare the longest runs
    // of data it contains
    for (size_t i = 0; i < _size - 1; i++)
    {
      // this if/else checks to see whether the run has continued or if it
      // should be cancelled and reset to 0. it also checks to see if start
      // needs to be changed to the beginning of the new run
      if (_data[i] == _data[i + 1])
      {
        if (longest == 0)
          start = i;
        longest++;
      }
      else
        longest = 0;

      // this if statement checks to see if the longest run has changed and
      // modifies the array if it has. it changes both the longest run value and
      // the starting position value
      if (longest > long_start[0])
      {
        long_start[0] = longest;
        long_start[1] = start;
      }
  }

  // this checks to see if there was a longest run and returns the starting
  // position if there was one
  if (long_start[0] > 1)
    return long_start[1];
  return _size;
}


/*** non-const member functions ***/


void sequence::add(int item)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != _capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ...VN-1]
  // Adds item to the end of the sequence.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., VN-1, item];
  //   size() == N+1.
  _size++;

  // add the item to the last spot for data to go
  _data[_size - 1] = item;
}

void sequence::add(int item, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  //   position <= size()
  // Inserts item at the given position.  All elements with indices at position
  // or greater are shifted to the right.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., item, Vposition,..., VN-1];
  //   size() == N+1
  _size++;

  // this for loop copies all the date to be one position to the right so the
  // new piece of data can be inserted where it needs to be
  for (size_t i = _size; i > position; i--)
    _data[i] = _data[i - 1];
  _data[position] = item;
}

void sequence::remove(size_t position)
{
  // Preconditions:
  //   The sequence has N elements
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1,  ..., Vposition-1, Vposition, Vposition+1, ... VN-1];
  //   0 <= position and position < N
  // The item at the given position is discarded.  All elements with greater
  // indices are shifted to the left.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., Vposition-1, Vposition+1, ..., VN-1]
  //   size() == N-1.
  // this makes sure the user is not trying to remove something from an empty
  // array
  if (_size != 0)
    // this shifts everything to the right of the position data is being removed
    // from to the left. this rewrites the data and removes it
    for (size_t i = position; i < _size - 1; i++)
      _data[i] = _data[i + 1];

  _size--;

  return;
}


void sequence::replace(int newitem, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   0 <= position < N
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  // Replaces the item at the given position with the given new item.
  // Postcondition:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., newitem,... VN-1];
  //   size() == N  (unchanged)
  _data[position] = newitem;

  return;
}

void sequence::clear()
{
  // Remove all elements from the sequence.
  // Postcondition:
  //   size() == 0
  _size = 0;

  return;
}
