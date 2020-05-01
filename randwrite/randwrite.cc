/*******************************************************************************
*                                                                              *
* randwrite.cc                                                                 *
* Nathan Koike                                                                 *
* Project 5                                                                    *
* 4/8/18                                                                       *
*                                                                              *
* this program takes a random seed and a corpus, and it  uses the seed to      *
* genetate a random string of text based off of the corpus                     *
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "list.cc"

using namespace std;

string find_followers(list & seed, string & corpus, size_t & length)
// find all the followers of a given seed
{
  string followers = "";
  int c;

  // the purpose of this for loop is to look through every character in the
  // original text
  for (size_t i = 0; i < corpus.size(); i++)
  {
    // look for a match with the first character of the seed
    if (corpus[i] == seed.get(0))
      // if the character index where the match was found supports being able to
      // find the rest of the output between it and the end of the corpus
      if (i + length + 1 < corpus.size())
        // look through every character following the first match
        for (size_t j = 0; j < seed.size(); j++)
          {
            // if a character doesn't match end the loop
            if (corpus[i + j] != seed.get(j))
              break;

            // if the loop is completed add the next character to the string of
            // followers
            if (j == seed.size() - 1)
              c = (int) corpus[i + j + 1];
          }
  }

  if (c != EOF)
    followers += (char) c;

  return followers;
}

char get_next(list & seed, string & corpus, size_t & length)
// get the next character for the output given the seed
{
  char next;

  // if the requested seed length was 0, fill the output with entirely random
  // characters
  if (seed.size() == 0)
    next = corpus[(rand() % corpus.size() - length)];

  // find all the followers and randomly pick one. it will most likely be the
  // character that appears the most after the given seed
  else
  {
    string followers = find_followers(seed, corpus, length);
    next = followers[rand() % followers.size()];
  }

  return next;
}

void get_seed(size_t & k, size_t & length, string & corpus, list & seed)
// get the seed for the program to use to generate text
{
  string followers = "";

  // pick a random character as the seed because an input of this length should
  // make no sense
  if (k < 2)
    seed.add(corpus[(rand() % (corpus.size() - (k < length? length: k)))],
              seed.size());

  // find a random characcter in the corpus and take every character that
  //follows it until the desired seed length has been reached
  else
  {
    size_t i = (rand() % (corpus.size() - k));
    seed.add(corpus[i], seed.size());

    for (size_t j = 1; j < k; j++)
      seed.add(corpus[i + j], seed.size());
  }
}

string get_output(size_t k, size_t length, list & seed, string & corpus)
// get the output of the program as a string
{
  // do a trick so this compiles and it still allows me to pass corpus without
  // using it in the function
  char _ = corpus[0];
  _ = _;

  string result = "";

  // the purpose of this for loop is to add every charatcter in the seed to the
  // result string to make sure every character gets counted
  for (size_t i = 0; i < seed.size(); i++)
    result += seed.get(i);

  int c; // this is an integer representation of a characcter

  // this prevents the code from breaking wiht a desired seed length of 0
  if (k < 1)
  {
    // thr purpose of this for loop is to add random characters until the
    // output length is reached
    for (size_t i = 0; i < length; i++)
    {
      c = (int) corpus[rand() % corpus.size()];
      result += (char) c;
    }
  }

  else
  {
    // the purpose of this for loop is to add the next most likely character to
    // the result string
    for (; result.size() < length; seed.remove_at(0))
    {
      c = (int) get_next(seed, corpus, length);
      seed.add((char) c, seed.size());
      result += (char) c;
    }
  }

  return result;
}

int main(int argc, char ** argv)
// command line inputs are seed length(k), output length(length), source
// file(source), and output file(output)
{
  if (argc != 5)
    return -1;

  srand(time(NULL)); // make a random seed based on the time

  // k is the level of complexity whose name is provided in the assignment sheet
  size_t k = atoi(argv[1]);

  size_t length = atoi(argv[2]); // number of characters in the output file

  ifstream source;
  ofstream output (argv[4]);
  source.open(argv[3]); // this is the source file

  string corpus = "";

  int c;

  c = source.get();
  while (c != EOF)
  {
    corpus += ((char) c);
    c = source.get();
  }

  list seed;

  get_seed(k, length, corpus, seed);

  string result = get_output(k, length, seed, corpus);

  output << result; // open or create the output file

  source.close();
}
