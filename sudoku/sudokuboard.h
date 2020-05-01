/*******************************************************************************
File: sudokuboard.h

Author: Nathan Koike

Date: 28 February 2018

Assignment: Project 3

Description: Write an algorithm that solves a sudoku puzzle. Accepted inputs are
             numbers 1-9 and _. This is the header file for the board class and
             provides its methods.
*******************************************************************************/

#include <iostream>

using namespace std;

typedef char element;

class sudokuboard
{
  private:
    string _grid[9];

    // disallows copying by making the copy constructor private. fix this later
    // sudokuboaord(const sudokuboard, &);
  public:
    sudokuboard(); // no-arg constructor
    void place(size_t r, size_t c, char n); // place numeral n at position (r,c)
    void print(); // write the board to cout
    char get(size_t r, size_t c); // return the numeral at position (r,c)
    void remove(size_t r, size_t c); // remove the numeral at position (r,c)

    // true iff the board would allow placing n at (r,c)
    bool canPlace(size_t r, size_t c, char n);
    // ^ fix this and then delete this comment

    bool solved(); // true iff there are no blank spots on the board

    // check to see if the character exists in the subgrid the coordinates
    // belong to
    bool exists_in_grid(size_t r_multiplier, size_t c_multiplier, char n);

    bool in_col(size_t r, size_t c, char n);
};
