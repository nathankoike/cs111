/******************************************************************************
*                                                                             *
* wordfind.cc                                                                 *
* Nathan Koike                                                                *
* Project 1                                                                   *
* 1/29/18                                                                     *
*                                                                             *
* This program finds and capitalizes words in a grid. It prints FOUND if the  *
* word is found and NOT FOUND if the word is not found.                       *
******************************************************************************/

#include <wordgrid.h>

using namespace std;

//-function: bool find(string word, wordgrid & grid)------------------------
// PRE: word consists of lowercase letters
// POST: If word is found in grid, starting anywhere
//       and in any of the 8 directions, it is converted
//       to uppercase in the grid, and true is returned.
//       otherwise, grid is unchanged, and false is returned.

bool horizontal(wordgrid & grid, string & word, size_t r, size_t c){
  string s1 = ""; // this string represents the first direction we search
  string s2 = ""; // this string represents the second direction we search

  // the purpose of this for loop is to add build a string that is the same
  // length as the word going both forwards and backwards
  for (size_t i = 0; i < word.size(); i ++){
    // the purpose of these if statements is to test to see if the word can
    // exist in that direction before building the string if possible
    if (c + word.size() < grid.size())
    	s1 += grid.get(r, c + i);
    if (c - word.size() < grid.size())
    	s2 += grid.get(r, c - i);
  }

  // these if statements check if the word was found and capitalize it if it was
  if (s1 == word){
   	for (size_t i = 0; i < word.size(); i++)
      grid.set(r, c + i, (char) ((int) grid.get(r, c + i) - ('a' - 'A')));
  	return true;
    }

  if (s2 == word){
    for (size_t i = 0; i < word.size(); i++)
      grid.set(r, c - i, (char) ((int) grid.get(r, c - i) - ('a' - 'A')));
    return true;
    }

  return false;
}

bool vertical(wordgrid & grid, string & word, size_t r, size_t c){
  string s1 = ""; // this string represents the first direction we search
  string s2 = ""; // this string represents the second direction we search

  // the purpose of this for loop is to add build a string that is the same
  // length as the word going both forwards and backwards
  for (size_t i = 0; i < word.size(); i ++){
    // the purpose of these if statements is to test to see if the word can
    // exist in that direction before building the string if possible
    if (r + word.size() < grid.size())
      s1 += grid.get(r + i, c);
    if (r - word.size() + 1 < grid.size())
      s2 += grid.get(r - i, c);
  }

  // these if statements check if the word was found and capitalize it if it was
  if (s1 == word){
    for (size_t i = 0; i < word.size(); i++)
      grid.set(r + i, c, (char) ((int) grid.get(r  +i, c) - ('a' - 'A')));
    return true;
    }

  if (s2 == word){
    for (size_t i = 0; i < word.size(); i++)
      grid.set(r - i, c, (char) ((int) grid.get(r - i, c) - ('a' - 'A')));    
    return true;
    }

  return false;
}

bool fslash(wordgrid & grid, string & word, size_t r, size_t c){
  string s1 = ""; 
  string s2 = "";

  // the purpose of this for loop is to add build a string that is the same
  // length as the word going both forwards and backwards
  for (size_t i = 0; i < word.size(); i ++){
    // the purpose of these if statements is to test to see if the word can
    // exist in that direction before building the string if possible
    if (r + 1 - word.size() < grid.size())
      if (c + word.size() - 1 < grid.size())
        s1 += grid.get(r - i, c + i);

    if (r + word.size() - 1 < grid.size())
      if (c + 1 - word.size() < grid.size())
        s2 += grid.get(r + i, c - i);
  }

  // these if statements check if the word was found and capitalize it if it was
  if (s1 == word){
    for (size_t i = 0; i < word.size(); i++)
      grid.set(r - i, c + i, (char) ((int) grid.get(r - i, c + i) - \
        ('a' - 'A')));
    return true;
  }
  
  if (s2 == word){
    for (size_t i = 0; i < word.size(); i++)
      grid.set(r + i, c - i, (char) ((int) grid.get(r + i, c - i) - \
        ('a' - 'A')));
    return true;
  }
  

  return false;
}

bool bslash(wordgrid & grid, string & word, size_t r, size_t c){
  string s1 = "";
  string s2 = "";

  // the purpose of this for loop is to add build a string that is the same
  // length as the word going both forwards and backwards
  for (size_t i = 0; i < word.size(); i ++){
  	// the purpose of these if statements is to test to see if the word can
    // exist in that direction before building the string if possible
    if (r + word.size() - 1 < grid.size())
      if (c + word.size() - 1 < grid.size())
	      s1 += grid.get(r + i, c + i);
	if (r + 1- word.size() < grid.size())
    if (c + 1 - word.size() < grid.size())
  	  s2 += grid.get(r - i, c - i);
  }

  // these if statements check if the word was found and capitalize it if it was
  if (s1 == word){
	  for (size_t i = 0; i < word.size(); i++)
  	  grid.set(r + i, c + i, (char) ((int) grid.get(r + i, c + i) - \
        ('a' - 'A')));
  	return true;
  	}

  if (s2 == word){
	  for (size_t i = 0; i < word.size(); i++)
  	  grid.set(r - i, c - i, (char) ((int) grid.get(r - i, c - i) - \
        ('a' - 'A')));
  	return true;
  	}

  return false;
}

//------------------------------------------------------------------------
bool find(string word, wordgrid & grid)
{
  size_t D = grid.size();

  bool found_word = false; // we assume this is false until proven otherwise

  // the purpose of these for loops is to find the first letter of the word
  // to test the word's possible existence
  for (size_t r = 0; r < D; r++){
    for (size_t c = 0; c < D; c++){
      char letter = grid.get(r, c);
        // if the first letter exists then search all directions for the word
        // but only as far as the word would extend
        if (letter == word[0]){
          // this funcion searches horizontally
          bool h = horizontal(grid, word, r, c);
          if (h)
            found_word = true;
          // this function searches vertically
          bool v = vertical(grid, word, r, c);
          if (v)
            found_word = true;

          // this function searches in the shape of forward slash
          bool forward_slash = fslash(grid, word, r, c);

          // this function searches in the shape of a backslash
          bool back_slash = bslash(grid, word, r, c);


          // this combines the previous two results with an or to get the truth
          // for the diagonals
          bool d = forward_slash || back_slash;
          if (d)
            found_word = true;

        }
    }
  }

  return found_word;
}

//------------------------------------------------------------------------
int main()
{
  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search for
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters

  // SETUP
  cin >> dim;  // read the dimension
  // read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    cin >> one_row;
    all_rows += one_row;
  }
  wordgrid grid(dim, all_rows);  // create the grid from that data
  cin >> word; // read the word

  // SEARCH
  found = find(word, grid);

  // REPORT
  if (found) {
    cout << "FOUND!" << endl;
    cout << grid;
  }
  else
    cout << "NOT FOUND!" << endl;
}
