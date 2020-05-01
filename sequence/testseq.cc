/************************************************************************
    File: testseq.cc
    Author: Alistair Campbell
    Date: August 30, 2015

    A test program for sequences.  Modify this as much as you
want to thoroughly test your sequence implementation.
************************************************************************/
#include <iostream>
#include <cstdlib>
#include "sequence.h"

using namespace std;

int main()
{
  cout << "print an empty sequence" << endl;
  sequence s1;
  cout << s1.size() << endl;
  s1.print();
  cout << endl << endl;

  cout << "Add a number and print" << endl;
  s1.add(56);
  s1.print();
  cout << endl << endl;

  cout << "Add a couple more to the left and right" << endl;
  s1.add(90);
  s1.add(451, 0);
  s1.print();
  cout << endl << endl;

  cout << "Elements at each position:" << endl;
  for (size_t i = 0; i < s1.size(); i++)
    cout << s1.get(i) << endl;
  cout << endl;
  
  cout << "Empty?" << endl;
  if (s1.empty())
    cout << "Empty." << endl;
  else
    cout << "Not Empty." << endl;
  cout << endl;

  cout << "Runs?" << endl;
  size_t pos = s1.getLongestRun();
  if (pos==s1.size()) {
    cout << "No runs in "; s1.print(); cout << endl;
  }
  else {
    cout << "Longest run of "; s1.print(); cout << " at " << pos << endl;
  }
  cout << endl;

  cout << "Filling it up..." << endl;
  while (not s1.full())
    s1.add(0);
  s1.print();
  cout << endl << endl;

  cout << "Runs NOW?" << endl;
  pos = s1.getLongestRun();
  if (pos==s1.size()) {
    cout << "No runs in "; s1.print(); cout << endl;
  }
  else {
    cout << "Longest run of "; s1.print(); cout << " at " << pos << endl;
  }
  cout << endl;

  cout << "Clear it." << endl;
  s1.clear();
  s1.print();
  cout << endl << endl;

  cout << "Empty?" << endl;
  if (s1.empty())
    cout << "Empty." << endl;
  else
    cout << "Not Empty." << endl;
  cout << endl;

  cout << "A random interaction" << endl;
  srandom(time(NULL));  // a new random sequence each time we run it!
  for (size_t i = 0; i < 50; i++) {
    s1.print();
    cout << endl;
    int v;
    size_t p;
    size_t choice = random() % 6;
    if (choice < 3) {
      if (s1.full())
	continue;
      v = 1 + random() % 6; // number cube roll.  :-)
      p = random() % (s1.size() + 1);
      cout << "Adding " << v << " at position " << p << endl;
      s1.add(v, p);
    }
    else if (choice == 3) {
      if (s1.empty())
	continue;
      p = random() % (s1.size());
      cout << "Removing at position " << p << endl;
      s1.remove(p);
    }
    else if (choice == 4) {
      if (s1.empty())
	continue;
      v = 1 + random() % 6; // number cube roll.  :-)
      p = random() % (s1.size());
      cout << "Replacing with " << v << " at position " << p << endl;
      s1.replace(v, p);
    }
    else {
      cout << "Longest run of list with size " << s1.size() << " at "
	   << s1.getLongestRun() << endl;
    }
    s1.print();
    cout << endl <<endl;
  }
  
  return 0;
}
