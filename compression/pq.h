/******************************************************************************
 *
 * Name: Nate Koike
 *
 * Date: 7 May 2018
 *
 * Assignment: Final Project
 *
 * Description: This is the header file for a min-heap based priority queue
 *
 ******************************************************************************/

#ifndef PQ
#define PQ

template <typename T>
class priority_queue {
 private:
  int (*_cmp)(const T &, const T &);  // _cmp is the comparison function
  T _data[256];
  size_t _size;

  void swap(size_t, size_t); // swap two elements with each other
  void reheap_up(size_t); // place an added element where it should be
  void reheap_down(size_t); // fix the heap after removing something
  size_t left_child(size_t) const; // return the index value of the left child
  size_t right_child(size_t) const; // return the index value of the right child

  // return the index value of the parent of the node
  size_t parent(size_t) const;

 public:
   // initialize a new priority queue
  priority_queue(int (*cmp)(const T &, const T &));

  void add(const T & item); // add an item to the priority queue
  void remove(); // remove the first item of the priority queue
  T front() const; // return the first element of the priority queue
  size_t size() const; // return the size of the priority queue
};

#include "pq.cc"

#endif
