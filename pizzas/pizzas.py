"""

FILE:  pizzas.py

AUTHOR: Nathan Koike

DATE: 17 January 2018

DESCRIPTION: Organize pizzas using row-major order

"""

import random

# You may find it useful to have a Pizza class.  Please feel free to
# add to this class as you see fit.

class Pizza(object):
    def __init__(self, kind, slices = 8):
        self._kind = kind
        self._slices = slices

    def __str__(self):
        return self._kind + '(' + str(self._slices) + ')'

    def remove_slices(self):
        ''' this removes all the slices from the pizza and returns the number
            of slices it previously had '''
        slices = self._slices
        self._slices = 0

        return slices
        
class PizzaTable(object):

    def __init__(self, n, m, kinds):
        """ construct a pizza table with n rows and m columns.  Order and 
            place n*m pizzas in row-major order, alternating kinds.  For
            example,
            PizzaTable(3, 4, ["pepperoni", "pepperoni", "plain",
                              "sausage", "buffalo"]) 
            would build:
+--------------+--------------+--------------+--------------+
| pepperoni(8) | pepperoni(8) | plain(8)     | sausage(8)   |
+--------------+--------------+--------------+--------------+
| buffalo(8)   | pepperoni(8) | pepperoni(8) | plain(8)     |
+--------------+--------------+--------------+--------------+
| sausage(8)   | buffalo(8)   | pepperoni(8) | pepperoni(8) |
+--------------+--------------+--------------+--------------+

        @PRE: n and m are integers, both greater than 0.
              kinds is a list of strings, whose length is at least 1.

"""
        assert(type(kinds) == list and len(kinds) > 0)
        assert(all(isinstance(x, str) for x in kinds))

        self._kinds = kinds
        self._rows = n
        self._cols = m

        # this calls a method to make the table
        self._table = self.make_table()

        # this is the name of the longest kind of pizza
        self._longest = 0
        self.longest_kind()

    # This method is provided for you
    def print(self):
        """ Write this table to the screen in a simple format. """
        for row in range(len(self._table)):
            for col in range(len(self._table[row])):
                print(self._table[row][col], end=" ")
            print()

    def find_cells_with(self, kind):
        """ return a list of tuples: locations on this table containing at 
            least one slice of pizza of the given kind. """
        # make a list to return all the tuples
        lst = []

        # look through every space in the grid and add the coordinates to the
        # list if they contain the given kind
        for n in range(self._rows):
            for m in range(self._cols):
                if self._table[n][m]._kind == kind:
                    if self._table[n][m]._slices > 0:
                        lst.append((n, m))
                    
        return lst


    def take_slice(self, position):
        """ Remove a slice of pizza from the table at the given position.

        @PRE: position is a tuple (row, col) with a valid row and col. """
        row, col = position
        assert 0 <= row < len(self._table)
        assert 0 <= col < len(self._table[row])

        if self._table[row][col]._slices > 0:
            self._table[row][col]._slices -= 1

    def consolidate(self):
        """ Rearrange pizzas on the table so that slices of the same kind are 
            together, favoring positions in row major order. """
        # the purpose of this for loop is to consolidate all the kinds of pizza
        for kind in self._kinds:
            # this list will be rewritten multiple times and contains the
            # locations of the kinds of pizza
            lst = self.find_cells_with(kind)

            # this is the total number of slices of one kind of pizza
            slices = 0

            # the purpose of this for loop is to collect all the slices of a
            # kind of pizza
            for i in lst:
                slices += self._table[i[0]][i[1]].remove_slices()

            # the purpose of this for loop is to redistribute the slices in row
            # major order
            for i in lst:
                # the purpose of this if statement is to make sure there are no
                # negative slice numbers
                if slices > 8:
                    self._table[i[0]][i[1]]._slices += 8
                    slices -= 8
                else:
                    self._table[i[0]][i[1]]._slices += slices
                    slices = 0

    def get_kind(self, position):
        """ return the kind of pizza that is, or is supposed to be, 
        in the cell at the given position 

        @PRE: position is a tuple (row, col) with a valid row and col. """
        row, col = position

        # this ensures that the condition(s) given are met
        assert 0 <= row < self._rows
        assert 0 <= col < self._cols

        return self._table[row][col]._kind

    def order(self, position, kind):
        """ Put a new pizza on the table.
        @PRE: position is a tuple (row, col) with a valid row and col;
              kind is a string matching the kind of pizza that 
                  belongs at position; and
              There are no pizza slices at position. """
        row, col = position

        assert 0 <= row < self._rows
        assert 0 <= col < self._cols
        assert 0 == self.get_slices(position)
        assert kind == self._table[row][col]._kind

        self._table[row][col]._slices += 8


    def get_slices(self, position):
        """ Return the number of slices at a particular position.
        @PRE: position is a tuple (row, col) with a valid row and col """
        row, col = position
        
        assert 0 <= row < self._rows
        assert 0 <= col < self._cols

        return self._table[row][col]._slices


    def pprint(self):
        """ Write this table to the screen in a format like the examples.  The 
            width of each cell is the same, exactly the size to accommodate 
            the longest pizza kind. """
        # call a function to print the horizontal borders
        horizontal_borders(self)

        # the purpose of this for loop is to print every row with a horizontal
        # border below it
        for n in range(self._rows):
            for m in range(self._cols):
                print("|", end = '')
                print('', self._table[n][m], end = ' ' * (self._longest + 5 - \
                        len(self._table[n][m]._kind) + 4))
            print("|")
            horizontal_borders(self)

    def make_table(self):
        """ this makes a table for the pizza and populates it """
        # this is a counter to index the list of kinds of pizza
        counter = 0

        # this will be returned as the pizza table
        table = []

        # this is an empty list that will be filled and rewritten to fill the
        # pizza table
        lst = []

        # the purpose of this for loop is to fill the pizza table with pizzas
        for n in range(self._rows):
            for m in range(self._cols):
                if counter == len(self._kinds):
                    counter -= len(self._kinds)
                lst.append(Pizza(self._kinds[counter]))
                counter += 1
            table.append(lst)
            lst = []
        return table

    def longest_kind(self):
        """ finds the longest name of a kind of pizza """
        for i in range(len(self._kinds)):
            long = len(self._kinds[i])
            if (i + 1) < len(self._kinds):
                if len(self._kinds[i + 1]) > long:
                    long  = len(self._kinds[i + i])

        self._longest = long


def horizontal_borders(table):
    # this prints the beginning of the borders
    print("+", end = '')

    # this sets the line to be the correct length
    line = '-' * (table._longest + 13)

    # the purpose of this for loop is to print the horizontal borders
    for _ in range(table._cols):
        print(line, end = '')
        print("+", end = "")
    print()
        
def main():
    """ Here is a sample program for testing your implementation. """
    N = 5
    M = 2
    types = ["Pepperoni", "Plain", "Kaja's Vegan"]
    pt = PizzaTable(N, M, types)

    #pt.pprint()

    for i in range(100):
        print(i)
        #pt.print()
        v = random.randrange(20)

        if v == 0:
            print("CONSOLIDATE!")
            pt.consolidate()
        elif v < 5:
            cell = (random.randrange(N), random.randrange(M))
            if pt.get_slices(cell) == 0:
                print("ORDERING!!")
                pt.order(cell, pt.get_kind(cell))
            else:
                got_some = False
                preference = types[:]
                random.shuffle(preference)
                for t in preference:
                    cells = pt.find_cells_with(t)
                    if len(cells) > 0:
                        cell = random.choice(cells)
                        pt.take_slice(cell)
                        got_some = True
                        break
                if not got_some:
                    print("WE'RE OUT OF PIZZA")
    print()
    pt.print()

    
if __name__ == "__main__":
    main()
