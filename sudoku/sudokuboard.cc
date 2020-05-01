/*******************************************************************************
File: sudokuboard.cc

Author: Nathan Koike

Date: 28 February 2018

Assignment: Project 3

Description: Write an algorithm that solves a sudoku puzzle. Accepted inputs are
             numbers 1-9 and _. This is the code that operates the board class
             and provides its methods.
*******************************************************************************/

#include<iostream>
#include"sudokuboard.h"

using namespace std;

sudokuboard::sudokuboard()
{
  // accept the inputs
  for (size_t i = 0; i < 9; i++)
    {
      cin >> _grid[i];
    }
}

// return the numeral at position (r,c)
char sudokuboard::get(size_t r, size_t c)
{
  return _grid[r][c];
}

// place numeral n at position (r,c)
void sudokuboard::place(size_t r, size_t c, char n)
{
  _grid[r][c] = n;
}

void sudokuboard::print() // write the board to cout
{
  for (size_t i = 0; i < 9; i++)
    cout << _grid[i] << endl;
}

// remove the numeral at position (r,c)
void sudokuboard::remove(size_t r, size_t c)
{
  _grid[r][c] = '_';
}

bool sudokuboard::exists_in_grid(size_t r_multiplier, size_t c_multiplier,
                                  char n)
{
  // the purpose for the multiplication by 3 here is to make sure the function
  // checks the right subgroup. these for loops check the 3x3 subgrid that
  // contains the specified coordinates
  for (size_t r = 3 * r_multiplier; r < 3 * (r_multiplier + 1); r++)
    for (size_t c = 3 * c_multiplier; c < 3 * (c_multiplier + 1); c++)
    {
      if (get(r, c) == n)
        return true;
    }
  return false;
}

// check to see if the character can be placed at the given coordinates
bool sudokuboard::canPlace(size_t r, size_t c, char n)
{
  // check horizontally from the specified coordinate
  for (size_t col = 0; col < 9; col++)
    if (get(r, col) == n)
      return false;

  // check vertically from the specified coordinate
  for (size_t row = 0; row < 9; row++)
    if (get(row, c) == n)
      return false;

  // check the 3x3 sub-grid containing the coordinate to see if it contains the
  // number. / is integer division
  if (exists_in_grid((size_t) (r / 3), (size_t) (c / 3), n))
    return false;

  return get(r, c) == '_';
}

// find if the character already exists in the column so the program can move on
bool sudokuboard::in_col(size_t r, size_t c, char n)
{
  for (; r < 9; r++)
    if (_grid[r][c] == n)
      return true;

  return false;
}

bool sudokuboard::solved() // true iff there are no blank spots on the board
{
  for (size_t i = 0; i < 9; i++)
    for (size_t j = 0; j < 9; j++)
      if (get(i, j) == '_')
        return false;

  return true;
}
