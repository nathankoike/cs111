stack.o: stack.cc
	g++ -c stack.cc

sudokuboard.o: sudokuboard.cc
	g++ -c sudokuboard.cc

sudoku.o: sudoku.cc
	g++ -c sudoku.cc

sudoku: sudoku.o sudokuboard.o stack.o
	g++ -o sudoku.o sudokuboard.o stack.o
