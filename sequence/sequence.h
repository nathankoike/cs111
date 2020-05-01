/************************************************************************
    File: sequence.h
    Author: Alistair Campbell
    Date: August 30, 2015

    Declaration of a simple array-based sequence class.

    Make no changes to this file.
************************************************************************/
#include <cstdlib>

class sequence {

 private:
  
  /*** Member data ***/
  
  static const size_t _capacity = 100;  // the maximum number of items in
                                      // any sequence
  size_t _size; // the number of items in this sequence
  int _data[_capacity];  // an array with sufficient slots to hold the items
                         // of this sequence

 public:
  
  /*** Constructor ***/
  sequence();
  // Initializes this sequence with 0 elements

  
  /*** const member functions ***/

  
  size_t size() const;
  // return the number of elements in this sequence

  bool empty() const;
  // return true if this sequence has no elements, false otherwise.

  bool full() const;
  // return true if this sequence has _capacity elements, false otherwise.

  void print() const;
  // Produce output with cout: a single open square bracket, the elements
  // of the sequence, separated by commas and spaces, followed by a single
  // close square bracket.  No newline.
  // Examples of output:
  //  []
  //  [6]
  //  [9, -1, 4]

  int get(size_t position) const;
  // Precondition:  position < size()
  // Return the element at the given position.

  size_t getLongestRun() const;
  // Determine the length of the longest run of two or more identical adjacent
  // elements of this sequence.  Return the smallest starting position of a
  // run with this length.  If no such run occurs, return size().
  // (This method may use auxiliary stand-alone functions, but, again, you
  // cannot change this  file.  This means that you cannot define auxiliary
  // methods.)

  
  /*** non-const member functions ***/


  void add(int item);
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

  void add(int item, size_t position);
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

  void remove(size_t position);
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

  void replace(int newitem, size_t position);
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
  
  void clear();
  // Remove all elements from the sequence.
  // Postcondition:
  //   size() == 0
  
};
