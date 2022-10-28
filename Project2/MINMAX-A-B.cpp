#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

char board[2][2]; // tic tac toe board
bool freeSpace[2][2]; // same as tic tac toe board but holds false if a space has been played in and true if not

void displayBoard();
void initBoard();

class Player
{
  public: char peice; // x or y
  void play(int r, int c)
  {
    board[r][c] = peice;
    freeSpace[r][c] = false;
  }
};


int main()
{
  initBoard();
  
  Player XMax, OMin;
  XMax.peice = 'X';
  OMin.peice = 'O';
  
  displayBoard();
  
  XMax.play(1,2);
  displayBoard();
  OMin.play(0,2);
  displayBoard();
  
}

void displayBoard() // prints out the current tic tac toe board
{
  for (int i = 0; i<=2; i++)
  {
    cout << board[i][0] << "    ";
    
    for (int j = 1; j<=2; j++)
    {
      cout << "|" << "    " << board[i][j] << "    ";
    }
    
    if (i != 2)
    {
      cout << endl << "_____________________" << endl;
    }
    
  }
  cout << endl << endl << endl;
}

void initBoard() //makes all spaces in the board blank
{
  for (int i = 0; i <= 2; i++)
  {
    for (int j = 0; j<=2; j++)
    {
      board[i][j] = '~'; // ~ represents empty
      freeSpace[i][j] = true;
    }
  }  
}

