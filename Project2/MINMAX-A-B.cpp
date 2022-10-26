#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

char board[2][2]; // tic tac toe board
bool freeSpaces[2][2]; // same as tic tac toe board but holds true if a space has been played in and false if not

void displayBoard();

int main()
{
  for (int i = 0; i <= 2; i++)
  {
    for (int j = 0; j<=2; j++)
    {
      board[i][j] = '~';
      freeSpaces[i][j] = false;
    }
  }
  
  displayBoard();
  
}

void displayBoard() // prints out the current tic tac toe board
{
  for (int i = 0; i<=2; i++)
  {
    cout << board[i][0] << "    ";
    
    for (int j = 1; j<=2; j++)
    {
      cout << "|" << "    " << board[0][j] << "    ";
    }
    
    if (i != 2)
    {
      cout << endl << "_____________________" << endl;
    }
    
  }
  
}
