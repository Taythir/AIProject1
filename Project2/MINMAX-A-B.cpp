#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <chrono>

using namespace std::chrono;
using namespace std;

const int SIZE = 3;

char board[SIZE][SIZE]; // tic tac toe board
bool freeSpace[SIZE][SIZE]; // same as tic tac toe board but holds false if a space has been played in and true if not

void displayBoard(char b[SIZE][SIZE]);
void initBoard();

class Node
{
  public:
  char nodeBoard[SIZE][SIZE]; //tic tac toe board for node
  int val = NULL, /* eval function value*/ depth = NULL;
  bool terminal = false; //if this is an end of game node, if one player won
  Node(); // constructor
  
  void terminalCheck() // check if node is a terminal node
  { 
    this->terminal = false;  
      
    //horizontal
    if(this->nodeBoard[0][0] != '~' && this->nodeBoard[0][0] == this->nodeBoard[0][1] && this->nodeBoard[0][1] == this->nodeBoard[0][2])
    {
      this->terminal = true;
    }
    if(this->nodeBoard[1][0] != '~' && this->nodeBoard[1][0] == this->nodeBoard[1][1] && this->nodeBoard[1][1] == this->nodeBoard[1][2])
    {
      this->terminal = true;
    }
    if(this->nodeBoard[2][0] != '~' && this->nodeBoard[2][0] == this->nodeBoard[2][1] && this->nodeBoard[2][1] == this->nodeBoard[2][2])
    {
      this->terminal = true;
    }
    
    //vertical
    if(this->nodeBoard[0][0] != '~' && this->nodeBoard[0][0] == this->nodeBoard[1][0] && this->nodeBoard[1][0] == this->nodeBoard[2][0])
    {
      this->terminal = true;
    }
    if(this->nodeBoard[0][1] != '~' && this->nodeBoard[0][1] == this->nodeBoard[1][1] && this->nodeBoard[1][1] == this->nodeBoard[2][1])
    {
      this->terminal = true;
    }
    if(this->nodeBoard[0][2] != '~' && this->nodeBoard[0][2] == this->nodeBoard[1][2] && this->nodeBoard[1][2] == this->nodeBoard[2][2])
    {
      this->terminal = true;
    }
    
    //diagonal
    if(this->nodeBoard[0][0] != '~' && this->nodeBoard[0][0] == this->nodeBoard[1][1] && this->nodeBoard[1][1] == this->nodeBoard[2][2])
    {
      this->terminal = true;
    }
    if(this->nodeBoard[0][2] != '~' && this->nodeBoard[0][2] == this->nodeBoard[1][1] && this->nodeBoard[1][1] == this->nodeBoard[2][0])
    {
      this->terminal = true;
    }
    
  }
  
  Node *parentNode = NULL;
  Node *children[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; //9 is max number of children
};

Node::Node()
{
    // To set depth
    int d = 0; //depth variable
    Node *tmp = this->parentNode;
    while (tmp != NULL)
    {
        d++;
        tmp = tmp->parentNode;
    }
    this->depth = d; 
}

Node path[9]; // 9 is max number of moves
int pathCount = 0;
Node A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
Node nodes[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z}; //array of the nodes
char nodeNames[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int nodeCount = 0;

class Player
{
  public: char peice; // x or y
  int evalNumber; // to pick which evaluation function to use;
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


///////////////////////////////////////////
int main()
{
  initBoard();
  int minMaxDepth = 0; //to use when calling MINIMAX
  
  Player XMax, OMin;
  XMax.peice = 'X';
  OMin.peice = 'O';
  
  cout << "Which evaluation function for XMax?: " << endl
       << "1: Possible wins - possible losses " << endl 
       << "2: " << endl //add explanations for other evaluation functions and their code in the corresponding switch case in the eval function definition
       << "3: " << endl
       << "4: " << endl
       << "Please enter a number: ";
  cin >> XMax.evalNumber;
  cout << endl << endl;
  
  cout << "Which evaluation function for OMin?: " << endl
       << "1: Possible wins - possible losses " << endl
       << "2: " << endl
       << "3: " << endl
       << "4: " << endl
       << "Please enter a number: ";
  cin >> OMin.evalNumber;
  cout << endl << endl;
  
  auto start = high_resolution_clock::now();
  /* actually play the game
  while(path[pathCount].terminal != null)
  {
    
  }
  */
  
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  int nodesGenerated = nodeCount + 1;
  cout << "Nodes Generated: " << nodeCount << endl
       << "Duration: " << duration.count() << " microseconds" << endl;
}
///////////////////////////////////////////


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

void moveGen(char b[SIZE][SIZE], Player p, Node node) // move generator
{
  //Node retArr[9]; // array that is returned, array of possible moves(nodes)
  int retArrCount = 0;
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
        
        Node n = Node();
        setArrEqual(n.nodeBoard, possibleBoard);
        n.terminalCheck();
        n.parentNode = &node;
        node.children[retArrCount] = &n;
        
        cout << nodeNames[nodeCount] << endl;
        displayBoard(possibleBoard);
        nodeCount++;
        
        setArrEqual(possibleBoard, b);
      }
    }
  }
  
  //return retArr;
}

int eval(char b[SIZE][SIZE], Player p)
{
    switch (p.evalNumber) // add other evaluation functions in other cases
    {
      case 1:
        int w = 0; // number of possible win lines for player
        int l = 0; //number of possible win lines for opposing player
        char op; // opposite players peice
    
        if (p.peice = 'X')
        {
          op = 'O';
        }
        else
        {
          op = 'X';
        }
     
        // horizontal possible wins
        if (b[0][0] != op && b[0][1] != op && b[0][2] != op)
        {
          w++;
        }
        if (b[1][0] != op && b[1][1] != op && b[1][2] != op)
        {
          w++;
        }
        if (b[2][0] != op && b[2][1] != op && b[2][2] != op)
        {
          w++;
        }
    
        //up and down possible wins
        if (b[0][0] != op && b[1][0] != op && b[2][0] != op)
        {
          w++;
        }
        if (b[0][1] != op && b[1][1] != op && b[2][1] != op)
        {
          w++;
        }
        if (b[0][2] != op && b[1][2] != op && b[2][2] != op)
        {
          w++;
        }
  
        //diagonal possible wins  
        if (b[0][0] != op && b[1][1] != op && b[2][2] != op)
        { 
          w++;
        }
        if (b[2][0] != op && b[1][1] != op && b[0][2] != op)
        {  
          w++;
        }
     
        // horizontal possible losses
        if (b[0][0] != p.peice && b[0][1] != p.peice && b[0][2] != p.peice)
        {
          l++;
        }
        if (b[1][0] != p.peice && b[1][1] != p.peice && b[1][2] != p.peice)
        {
          l++;
        }
        if (b[2][0] != p.peice && b[2][1] != p.peice && b[2][2] != p.peice)
        {
          l++;
        }
  
        // vertical 
        if (b[0][0] != p.peice && b[1][0] != p.peice && b[2][0] != p.peice)
        {
          l++;
        }
        if (b[0][1] != p.peice && b[1][1] != p.peice && b[2][1] != p.peice)
        {
          l++;
        }
        if (b[0][2] != p.peice && b[1][2] != p.peice && b[2][2] != p.peice)
        {
          l++;
        }
  
        //diagonal possible losses  
        if (b[0][0] != p.peice && b[1][1] != p.peice && b[2][2] != p.peice)
        { 
          l++;
        }
        if (b[2][0] != p.peice && b[1][1] != p.peice && b[0][2] != p.peice)
        {  
          l++;
        }
  
        int evalFunc = w - l;
        return evalFunc;
    }
}

bool deepEnough(Node n, int depth) // Node is position. deepEnough is for use in MINIMAX-A-B
{
  if(n.depth >= depth) 
  {
    return true;
  }
  else if(n.terminal == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}


Node MINIMAX(Node n, int depth, Player p) // node is position
{
  if (deepEnough(n, depth) == true)
  {
    return n;
  }
  else
  {
    moveGen(n.nodeBoard, p, n);
    
    if(n.children[0] == NULL)
    {
        return n;
        
    }
  }
      
}
