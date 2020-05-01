/******************************************************************************
 *
 * Name: Nate Koike
 *
 * Date: 7 May 2018
 *
 * Assignment: Final Project
 *
 * Description: Write a program that both compresses and uncompresses text files
 *
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "pq.h"

struct HuffmanTree {
  unsigned char value;
  size_t count;
  HuffmanTree *left;
  HuffmanTree *right;
  HuffmanTree(unsigned char value, size_t count,
	      HuffmanTree *left=NULL, HuffmanTree *right=NULL) :
    value(value), count(count), left(left), right(right) {}
};


int huffman_tree_cmp(HuffmanTree * const & a, HuffmanTree * const & b)
// provided by Professor Campbell
{
  if (a->count == b->count) return 0;
  return a->count < b->count ? -1 : 1;
}

using namespace std;

unsigned char bits_to_byte(string bitstr) {
  // Written in class on Friday 4/13
  unsigned char total = 0;
  size_t i;
  int p;
  for (i = 0, p=128; i < 8; i++, p /= 2)
    if (bitstr[i] == '1')
      total += p;
  return total;
}

string byte_to_bits(int c)
// convert a byte of data into a string of individual bits
{
  string buffer = "";

  // the purpose of this for loop is to fill the buffer
  for (int i = 128, p = 0; p < 8; i /= 2, p++)
  {
    if (c >= i) // if the value of i can divide evenly into c
    {
      buffer += "1"; // add 1 to the buffer
      c -= i; // reduce c so there is no double counting
    }

    else
      buffer += "0";
  }

  return buffer;
}

void get_counts(size_t * counts, size_t & size, istream & in)
{
  // POST:  all characters read from in.
  //        counts[k] = the number of occurrences of k in the istream.
  //        size is the number of characters read
  int c = in.get();

  for (; c != EOF; c = in.get())
  {
    counts[(unsigned char) c]++;
    size++;
  }
}

HuffmanTree * make_tree(size_t * counts)
{
  priority_queue<HuffmanTree *> queue(huffman_tree_cmp);
  // Finish.
  // 1. make leaves and insert in priority queue
  // 2. Implement tree-building algorithm removing two
  //    trees, combining and reinserting until queue size
  //    is 1.

  // this for loop makes and inserts a new Huffman tree for every character
  // possible with 256 bits and inserts it into a priority queue
  for (size_t i = 0; i < 256; i++)
    if (counts[i] > 0)
      queue.add(new HuffmanTree(i, counts[i]));

  // this while loop condenses the priprity queue until it contains a single
  // tree
  while(queue.size() > 1)
    {
      // get the left and right children
      HuffmanTree * left = queue.front();
      queue.remove();

      HuffmanTree * right = queue.front();
      queue.remove();

      // this makes a new Huffman tree from the two chars with the lowest counts
      // and inserts it back into the priority queue
      queue.add(new HuffmanTree(0, (left->count + right->count), left, right));
    }

  // 3. Remove and return the resulting tree.
  HuffmanTree *result = queue.front();
  queue.remove();
  return result;
}

void make_codes(HuffmanTree *tree, string *codes, string code="")
{
  // codes is an array of 256 strings, initially empty.
  // code is the path so far.
  // if at a leaf, store path in codes corresponding to value
  // otherwise, recursive call left and right, with updates to code.
  if (!tree)
    return;

  if (!tree->left) // if the tree is a leaf
  {
    // if the tree is a singleton tree just make the path '0' otherwise assign
    // make the path whatever the code is
    codes[tree->value] = code == ""? "0": code;
  }

  // recursively generate all of the codes
  make_codes(tree->left, codes, code + "0");
  make_codes(tree->right, codes, code + "1");
}

void write_compress(istream & in, string * codes, ostream& ostr)
// write the entire output for comrpess
{
  int let = in.get();
  string code = "";
  string buffer = "";

  // this loop terminates when the end of the file has been reached
  for (; let != EOF; let = in.get())
  {
    code += codes[let];

    // either fill the buffer to capacity or fully empty the code
    while (buffer.size() < 8 && code.size() > 0)
    {
        buffer += code[0];
        code = code.substr(1);
    }

    // only writes something when the size of the buffer is 8
    if (buffer.size() == 8)
    {
      ostr << bits_to_byte(buffer);
      buffer = "";
    }
  }

  // if the end of the file has been reached but the buffer is not empty
  if (buffer.size() > 0)
  {
    // pad the buffer
    while (buffer.size() < 8)
      buffer += "0";
    ostr << buffer;
  }
}

void write_tree(HuffmanTree * tree, ostream & ostr)
// write the tree to the output
{
  if (!tree) // don't do anything if there is no tree
    return;

  if (!tree->left) // if the tree is a leaf output L followed by the value
    ostr << 'L' << tree->value;

  else
  {
    cout << 'I'; // note this as an internal node

    // this and the following line are needed for a preorder traversal of the
    // tree
    write_tree(tree->left, ostr);
    write_tree(tree->right, ostr);
  }

}

HuffmanTree * read_tree(istream & istr)
// read the tree from a file
{
  // Inverse of write_tree
  // written in class
  int let = istr.get();
  if (let == 'L')
    return new HuffmanTree(istr.get(), 0);
  return new HuffmanTree(0, 0, read_tree(istr), read_tree(istr));
}

void compress(char *filename)
// theoretically makes a file smaller by writing character representations of
// bitstrings that correspond to leaves in a tree
{
  ifstream in(filename);
  size_t counts[256] = { }; // initializes all to zero.
  size_t file_size = 0;
  get_counts(counts, file_size, in);
  in.close();

  if (file_size == 0) // if the file is empty don't do anything
    return;

  // build a binary tree to be provided in the output
  HuffmanTree * tree = make_tree(counts);

  // make the bitstrings and save them in an array that can be indexed using the
  // integer representation of characters
  string codes[256];
  make_codes(tree, codes);

  // begin writing things to the output
  cout << file_size;
  write_tree(tree, cout);

  // Second pass through the input....
  in.open(filename);

  // write the compressed bytes to the standard output
  write_compress(in, codes, cout);
}

void traverse(HuffmanTree * & tree, istream & in, size_t & size)
// traverse the tree until the output is the correct length and write all of the
// characters to the standard output
{
  string buffer = "";
  size_t count = 0;

  // this while loop will terminate when the desired output length has been
  // achieved
  while (count < size)
  {
    // make a pointer to the root of the tree
    HuffmanTree *p = tree;

    // this while loop will terminate when the pointer made above points to a
    // leaf
    while (p->left)
    {
      // fill the buffer when neccessary
      if (buffer.size() < 1)
        buffer = byte_to_bits(in.get());

      // if the first character in the buffer is a 0 go left otherwise go right
      p = buffer[0] == '0'? p->left: p->right;

      // remove the first character from the buffer
      buffer = buffer.substr(1);
    }

    // now that p points to a leaf output its value
    cout << p->value;

    // increment the number of characters that have been written to the standard
    // output
    count++;
  }
}

void uncompress()
// tae a compressed file and restore it to the file that it came from
{
  // check to make sure that the file is not empty
  if (cin.peek() == EOF)
    return;

  // get the file size so the program knows how many characters it needs to
  // write
  size_t file_size;
  cin >> file_size;

  // remake the tree from the provided traversal
  HuffmanTree *tree = read_tree(cin);

  // write all the characters to the standard output
  traverse(tree, cin, file_size);
}

/* DON'T MODIFY BELOW */

bool ends_with(const string & str, const string & suffix)
{
  return str.size() >= suffix.size() and
    str.substr(str.size()-suffix.size()) == suffix;
}

bool is_compress(const string & command)
{
  return ends_with(command, "compress") and
    not ends_with(command, "uncompress");
}

int main(int argc, char **argv)
{
  argc = argc;
  if (is_compress(argv[0]))
    if (string(argv[1])=="-b") {
      compress(argv[2]);
    }
    else
      compress(argv[1]);
  else
    uncompress();
}
