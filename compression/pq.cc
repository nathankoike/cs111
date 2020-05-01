/******************************************************************************
 *
 * Name: Nate Koike
 *
 * Date: 7 May 2018
 *
 * Assignment: Final Project
 *
 * Description: Implement a min-heap based priority queue
 *
 ******************************************************************************/
template <typename T>
priority_queue<T>::priority_queue(int (*cmp)(const T &, const T &))
// initialize the priority queue
{
  _size = 0;
  _cmp = cmp;
}

template <typename T>
void priority_queue<T>::add(const T & item)
// add an item to the heap
{
  _data[size()] = item; // set the item to be the last element in the heap
  _size++;
  reheap_up(size() - 1); // re-sort the heap
}

template <typename T>
void priority_queue<T>::remove()
// remove the first element of the heap
{
  _size--;

  // store the last element added to the heap to maintain its completeness
  T temp = _data[size()];

  _data[0] = temp; // set that equal to the first element
  reheap_down(0); // re-sort the heap
}

template <typename T>
T priority_queue<T>::front() const
// return the value of the first element of the heap
{
  return _data[0];
}

template <typename T>
size_t priority_queue<T>::size() const
// return the size of the heap
{
  return _size;
}

template <typename T>
void priority_queue<T>::swap(size_t n, size_t m)
// switch the values of data[n] and data[m] with each other
{
  T temp = _data[m];
  _data[m] = _data[n];
  _data[n] = temp;
}

template <typename T>
void priority_queue<T>::reheap_up(size_t k)
// take the last element that was added to the heap and move it to where it
// should go
{
  if (k == 0) // do nothing if the heap is a singleton
    return;

  // only swap if the data at the parent index is larger than the data at k
  if (_cmp(_data[k],  _data[parent(k)]) < 0)
  {
    swap(k, parent(k));
    reheap_up(parent(k)); // recursively re-sort the list
  }
}

template <typename T>
void priority_queue<T>::reheap_down(size_t k)
// take the first element in the heap and move it to where it should be
{
  // if the left child cannot exist the data is a leaf in the tree
  // representation of the heap and it therefore has nowhere to go so do nothing
  if (left_child(k) >= size())
    return;

  // if the right child cannot exist but the left child does
  if (right_child(k) >= size())
  {
    // see if there needs to be a swap then swap if necessary
    if (_cmp(_data[k], _data[left_child(k)]) > 0)
    {
      swap(k, left_child(k));

      // recursively re-sort the list from the new position
      reheap_down(left_child(k));
    }
    return; // we don't want to do anything else so just return
  }

  // choose a direction to potentially swap based on which child is smaller
  // only go to the left if the data at the left child is strictly less than the
  // data at the right child
  size_t rep = _cmp(_data[left_child(k)], _data[right_child(k)]) < 0?
                left_child(k): right_child(k);

  // another comparison to see if a swap needs to be made
  if (_cmp(_data[k], _data[rep]) > 0)
  {
    swap(k, rep);
    reheap_down(rep); // recursively fix the heap from there
  }
}

template <typename T>
size_t priority_queue<T>::left_child(size_t k) const
// return the index value of the left child of the provided index position
// this was done in class
{
  return (2 * k) + 1;
}

template <typename T>
size_t priority_queue<T>::right_child(size_t k) const
// return the index value of the right child of the provided index position
// this was done in class
{
  return left_child(k) + 1;
}

template <typename T>
size_t priority_queue<T>::parent(size_t k) const
// return the index value of the parent of the provided index position
// this was done in class
{
  return (k - 1) / 2;
}
