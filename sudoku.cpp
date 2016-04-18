#include "sudoku.h"

using namespace std;

Sudoku::Sudoku()
{
	int row;
	int column; 
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 9; column++)
		{
			board[row][column] = 0;
		}
	}
	
}

int Sudoku::inputintoBoard()
{

	int c = 0;

  char input[256];

  // while (!cin.eof() && !cin.fail())
  // {
  //   cin.getline(input, 256);
  //   cin.ignore();
  // }

  cin.getline(input,256);
  int length = strlen(input);

  if (length > 81)
  {
    if (!isprint(input[81]))
    {
     
      cout << "ERROR: expected \\n saw \\x" << setw(2) << setfill('0') << hex << (int)(input[81]) << endl;
      return 0;
    }
    else
    {
      cout << "ERROR: expected \\n saw " << input[81] << endl;
      return 0;
    }

  }
  else if (length < 81)
  {
    cout << "ERROR: expected <value> saw \\n" << endl;
    return 0;
  }
  else
  {
    for (int row = 0; row < 9; row++)
    {
      for (int column = 0; column < 9; column++)
      {
        if (input[c] == 0)
        {
          cout << "ERROR: expected <value> saw " << input[c] << endl;
          return 0;
        }
        if (!isdigit(input[c]) && input[c] != '.' && isprint(input[c]))
        {
          cout << "ERROR: expected <value> saw " << input[c] << endl;
          return 0;
        }
        else if (!isdigit(input[c]) && input[c] != '.' && !isprint(input[c]))
        {
          char hex=input[c]/16;
          char hex1=input[c]%16;

          if (hex < 10) 
            hex = hex +'0';
          else 
            hex = hex - 10 + 'b';

          
          if (hex1 < 10) 
            hex1 = hex1 + '0';
          else 
            hex1 = hex1 - 10 + 'a';
          //setw(2) << setfill('0') 
          //cout << "ERROR: expected <value> saw \\x" << setw(2) << setfill('0') << hex << (int) input[c] << endl;
          cout << "ERROR: expected <value> saw \\x" << hex << hex1 << endl;

          
          return 0;
        }


        if (input[c] == '0')
        {
        	return 0;
        }
        if (input[c] == '.')
        {
          input[c] = '0';
        }
        
        int a = input[c] - '0';
        board[row][column] = a;
        c++;
      } 
    }
    char ch;
    cin >> ch;
    cin.ignore();
    if (!cin.eof())
    {
      cout << "ERROR: expected <eof> saw " << ch << endl;
      return 0;
    }

    setconstraints();
    findSolutions(0,0);

    if (count == 0)
    {
      cout << "No solutions." << endl;
    }

    return 1;
   }

}


void Sudoku::setconstraints()
{

	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
      puzzle[row][column] = mysetb(row,column);
		}
	}
  
}

set<int> Sudoku::mysetb(int row, int column)
{
	 std::set<int> myset;
	 std::set<int>::iterator it;

	 int element;

   if (board[row][column] != 0)
   {
      myset.insert(board[row][column]);
   }
   else
  {
  	 for (int i=1; i<=9; ++i)
  	 {
  	 	myset.insert(i);
  	 }

  	for (int col = 0; col < 9; col++)
  	{
         if (board[row][col] != 0)
          {
          	myset.erase(board[row][col]);
          }
    }

    for (int roww = 0; roww < 9; roww++)
  	{
         if (board[roww][column] != 0)
          {
          	myset.erase(board[roww][column]);
          }
    }


     	for (int y = (row/3) * 3; y <= (row/3)*3 + 2; y++)
     	{
     		for (int x = (column/3) * 3; x <= (column/3)*3 + 2; x++)
     		{
     			if (board[y][x] != 0)
     			{	
     				myset.erase(board[y][x]);
     			}
     		}
     	}

     	if (myset.size() == 1)
      {
        for ( it=myset.begin() ; it != myset.end(); it++ )
        {
          element = *it;
        }
        board[row][column] = element;
      }
    }
    

  return myset;
}

bool Sudoku::FindZeroes()
{
    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++)
            if (board[row][col] == 0)
                return true;
    return false;
}

bool Sudoku::checkCol(int row, int column, int i)
{

    for (int roww = 0; roww < 9; roww++)
	     if (board[roww][column] == i)
          return true;
    return false;

   
}

bool Sudoku::checkRow(int row, int column, int i)
{
  for (int col = 0; col < 9; col ++)
       if (board[row][col] == i)
          return true;
  return false;
}


bool Sudoku::checkBox(int row, int column, int i)
{
    for (int y = (row/3) * 3; y <= (row/3)*3 + 2; y++)
    {
      for (int x = (column/3) * 3; x <= (column/3)*3 + 2; x++)
      {
        if (board[y][x] == i)
        { 
          return true;
        }
      }
    }
  return false;
}



int Sudoku::findSolutions(int row, int col)
{
  if (!FindZeroes())
  {
    isBoardSolved();
    return 0;
  }

  if (row == 8 && col == 8)
  {
    return 1;
  }

  while (row < 9 && col < 9 && board[row][col] != 0)
  {
    col++;
    if (col >= 9)
    {
      findSolutions(row+1,0);

    }
    if (row >= 9)
    {
      findSolutions(0, col+1);
    }
  }
  for (int num = 0; num <= 9; num++)
  {
    if (!checkCol(row,col,num) && !checkBox(row, col, num) && !checkRow(row,col,num) && puzzle[row][col].count(num))
    {
      board[row][col] = num;
      if (findSolutions(row,col))
        return 1;
    }
  }
  board[row][col] = 0;
  return 0;
  
}




void Sudoku::isBoardSolved()
{
  count++;
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			cout << board[row][column];
		}
	}
	cout << '\n';
}


