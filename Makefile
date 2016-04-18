# kspai: Pai, Karthika

sudsolve : puzzle.o sudoku.o 
	g++ -g -Wall -ansi -o sudsolve puzzle.o sudoku.o 

puzzle.o : puzzle.cpp sudoku.h
	g++ -g -Wall -ansi -c puzzle.cpp
	
sudoku.o : sudoku.cpp sudoku.h 
	g++ -g -Wall -ansi -c sudoku.cpp




