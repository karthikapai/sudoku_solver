#ifndef sudokuH
#define sudokuH

#include <iostream>
#include <ostream>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <iomanip> 
#include <set>
#include <string>
#include <sstream>
#include <istream>
#include <cstring>




using namespace std;

class Sudoku
{
 public:
  int board[9][9];
  set <int> puzzle[9][9];
  int count = 0;
  Sudoku();
  int inputintoBoard();
  void setconstraints();
  set<int> mysetb(int row, int column);
  void isBoardSolved();
  bool FindZeroes();
  int findSolutions(int row, int col);
  bool checkRow(int row, int column, int i);
  bool checkCol(int row, int column, int i);
  bool checkBox(int row, int column, int i);
}; 

#endif