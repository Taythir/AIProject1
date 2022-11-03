#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

const int SIZE = 3;

char board[SIZE][SIZE]; // tic tac toe board
bool freeSpace[SIZE][SIZE]; // same as tic tac toe board but holds false if a space has been played in and true if not

void displayBoard(char b[SIZE][SIZE]);
void initBoard();

class Node
{
  public:
  char nodeBoard[SIZE][SIZE];
  int val = NULL, depth = NULL;
  Node *parentNode = NULL;
};

Node path[9]; // 9 is max number of moves
int pathCount = 0;
Node A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
Node nodes[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z}; //array of the nodes
char nodeNames[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int nodeCount = 0;

class Player
{
  public: char peice; // x or y
  void play(int r, int c)
  {
    if (freeSpace[r][c] == true)
    {
      board[r][c] = peice;
      freeSpace[r][c] = false;
    }
  }
};

Node * moveGen(char b[SIZE][SIZE], Player p);
void setArrEqual(char a[SIZE][SIZE], char b[SIZE][SIZE]); //sets a = b



int main()
{
  initBoard();
  
  Player XMax, OMin;
  XMax.peice = 'X';
  OMin.peice = 'O';
  
  Node *n = moveGen(board, XMax);
}

void displayBoard(char b[SIZE][SIZE]) // prints out the current tic tac toe board
{
  for (int i = 0; i<=2; i++)
  {
    cout << b[i][0] << "    ";
    
    for (int j = 1; j<=2; j++)
    {
      cout << "|" << "    " << b[i][j] << "    ";
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

void setArrEqual(char a[SIZE][SIZE], char b[SIZE][SIZE]) //sets a = b
{
  for (int i = 0; i<=2; i++)
  {
    for (int j = 0; j<=2; j++)
    {
      a[i][j] = b[i][j];
    }
  }
}

Node * moveGen(char b[SIZE][SIZE], Player p) // move generator
{
  Node retArr[9]; // array that is returned, array of possible moves(nodes)
  char possibleBoard[SIZE][SIZE];

  setArrEqual(possibleBoard, b);
  
  for (int i = 0; i<= 2; i++)
  {
    for (int j = 0; j <=2; j++)
    {
      if(freeSpace[i][j] == true)
      {
        possibleBoard[i][j] = p.peice;
        setArrEqual(nodes[nodeCount].nodeBoard, possibleBoard);

        cout << nodeNames[nodeCount] << endl;
        displayBoard(possibleBoard);
        nodeCount++;
        
        setArrEqual(possibleBoard, b);
      }
    }
  }
  
  return retArr;
}
