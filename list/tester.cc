#include "list.h"

using namespace std;

int main()
{
  // a VERY simple tester. You will want to throw this away and write your own.
  list mylist;
  list mylist2(mylist);

  list mylist3;
  mylist3 = mylist;
  mylist.add(1,0);
  mylist.output(cout);

  mylist.add(2,0);
  mylist.output(cout);

  mylist.add(3,0);
  mylist.output(cout);

  cout << mylist.size() << endl;   // outputs 3
  cout << mylist.find(2) << endl;  // outputs 1
  cout << mylist.get(1) << endl;   // outputs 2
  mylist.output(cout);  // outputs <3, 2, 1>  (no newline)
  mylist.remove_at(1);  // removes 2
  mylist.output(cout);
  mylist.remove(40);    // nothing
  mylist.output(cout); cout << endl;
  mylist.remove(1);
  mylist.output(cout);  // outputs <3>
  cout << "Going to destruct" << endl;
}
