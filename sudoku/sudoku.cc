/*******************************************************************************
File: sudoku.cc

Author: Nathan Koike

Date: 28 February 2018

Assignment: Project 3

Description: Write an algorithm that solves a sudoku puzzle. Accepted inputs are
             numbers 1-9 and _
*******************************************************************************/

#include "stack.h"
#include "sudokuboard.h"
using namespace std;

void place_nums(sudokuboard & board, stack & st)
{
  // initialize variables to get the character at row r and column c
  size_t r = 0;
  size_t c = 0;

  // CITE: Sarah Magee
  // DESC: Inspired the increment of a character by using neighboring ASCII
  //       values
  // this for loop goes tries to place every number going from 1 to 9.
  for (char num = '1'; num <= '9'; num++)
  {
    // the goal is to place one number in every column. when c is 9 the program
    // has placed one number in every column and can move on to the next number
    while (c < 9)
    {
      // check to see if the number is already in the column. move on if it is
      if (board.in_col(r, c, num))
        c++;
      // if r > 8 the program cannot place another number in the column and must
      // go back to correct the error that caused this; it must backtrack
      else if (r > 8)
      {
        // take the number from the top of the stack and make it the number used
        // by the for loop
        num = (char) st.top();
        st.pop(); // remove the number from the stack

        // take the number from the top of the stack and make it the new column
        // value
        c = st.top();
        st.pop();

        // take the number from the top of the stack and make it the new row
        // number
        r = st.top();
        st.pop();

        // remove the character at this previous location so it can be fixed
        board.remove(r, c);

        // increment r so the problem does not repeat itself
        r++;
      }

      // place the number if possible
      else if (board.canPlace(r, c, num))
      {
        // change the value of the string at the location to be the number
        board.place(r, c, num);

        st.push(r); // add the r value to the stack
        st.push(c); // add the c value to the stack

        // add the number to the stack after type casting it to size_t
        st.push((size_t) num);

        // increment c so the program can try to place the next number in the
        // next column
        c++;

        // set r to 0 to reset so the program can work its way down the next
        // column
        r = 0;
      }

      else
        // increment r so the program can try to place the number in the next
        // row as it works its way down the column
        r++;
    }

    // reset r and c so the program can repeat exactly the same process with the
    // next number
    c = 0;
    r = 0;
  }
}

int main()
{
  // get the baord
  sudokuboard board;

  // make a stack to backtrack from
  stack back;

  // place the numbers on the board
  place_nums(board, back);

  // print the finished board
  board.print();
}
