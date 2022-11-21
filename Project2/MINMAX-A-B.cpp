#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <chrono>

using namespace std::chrono;
using namespace std;

const int SIZE = 3, USETHRESH = 100, PASSTHRESH = 100;

char board[SIZE][SIZE]; // tic tac toe board
bool freeSpace[SIZE][SIZE]; // same as tic tac toe board but holds false if a space has been played in and true if not

void displayBoard(char b[SIZE][SIZE]);
void initBoard();

class Node
{
  public:
  string name = "Blank";
  char nodeBoard[SIZE][SIZE]; //tic tac toe board for node
  int val = NULL, /* eval function value*/ depth = NULL,
      newVal = NULL;
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
  //Node *children[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; //9 is max number of children
  int numberOfChildren = 0;
};
  Node Blank;
  //Blank.name = "Blank";
  Node children[9] = {Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank};
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

void setDepth(Node n)
{
    // To set depth
    int d = 0; //depth variable
    Node *tmp = n.parentNode;
    while (tmp != NULL)
    {
        d++;
        tmp = tmp->parentNode;
    }
    n.depth = d;
}

Node path[9]; // 9 is max number of moves
int pathCount = 0;
Node A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
Node nodes[500] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z}; //array of the nodes
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

Node MINIMAX(Node n, int depth, Player p, int USETHRESH, int PASSTHRESH);

Node ret;

Player XMax, OMin;

///////////////////////////////////////////
int main()
{
  Blank.name = "Blank";
  Blank.parentNode = NULL;
  for(int i = 0; i<9; i++)
  {
      children[i] = Blank;
  }
  
  initBoard();
  int minMaxDepth = 0; //to use when calling MINIMAX
  
  XMax.peice = 'X';
  OMin.peice = 'O';
  cout << "Which evaluation function for XMax?: " << endl
       << "1: Possible wins - possible losses " << endl 
       << "2: Possible wins" << endl //add explanations for other evaluation functions and their code in the corresponding switch case in the eval function definition
       << "3: Possible losses" << endl
       << "4: " << endl
       << "Please enter a number: ";
  cin >> XMax.evalNumber;
  cout << endl << endl;
  
  cout << "Which evaluation function for OMin?: " << endl
       << "1: Possible wins - possible losses " << endl
       << "2: Possible wins" << endl
       << "3: Possible losses" << endl
       << "4: " << endl
       << "Please enter a number: ";
  cin >> OMin.evalNumber;
  cout << endl << endl;
  
  Node initialNode;
  setArrEqual(initialNode.nodeBoard, board);
  path[pathCount] = initialNode;
  
  bool Xturn = true; // true if it's x's turn
  
  auto start = high_resolution_clock::now(); //start timer
  // actually play the game
  //while(path[pathCount].terminal == false)

  for (int i = 0; i < 9; i++)
  {
      // XMax goes first
    if (Xturn)
    {
        path[i] = MINIMAX(initialNode, minMaxDepth, XMax, USETHRESH, PASSTHRESH);
        cout << "set path X" << endl;
        displayBoard(path[pathCount].nodeBoard);
        Xturn = false;
    }
    else 
    {
        path[i] = MINIMAX(initialNode, minMaxDepth, OMin, USETHRESH, PASSTHRESH);
        cout << "set path O" << endl;
        displayBoard(path[pathCount].nodeBoard);
        Xturn = true;
    }
    
    setArrEqual(board, path[i].nodeBoard);
    for(int r = 0; r < SIZE; r++)
    {
      for(int c = 0; c < SIZE; c++)
      {
        if (board[r][c] != '~')
        {
          freeSpace[r][c] = false;
        }
      }
    }
    initialNode = path[pathCount];
    pathCount++;
    minMaxDepth++;
  }
  
  auto stop = high_resolution_clock::now(); // end timer
  auto duration = duration_cast<microseconds>(stop - start);
  int nodesGenerated = nodeCount + 1;
  
  Node *tmp = &initialNode;
  cout << "actual path: " << endl;
  for (int i = 0; i < 9; i++)
  {
    displayBoard(tmp->nodeBoard);
    //initialNode = *(initialNode.parentNode);
    tmp = &path[i];
  }
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

int eval(char b[SIZE][SIZE], Player p)
{
    switch (p.evalNumber) // add other evaluation functions in other cases
    {
      case 1:
      {
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
        break;
      }
      
      case 2: //possible wins
      {
          
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
        
        return w;
        break;
      }
      
      case 3: // possible losses
      {
        int l = 0;
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
        
        return -l;
        break;
      }
    }
}

void moveGen(char b[SIZE][SIZE], Player p, Node node) // move generator
{
  //Node retArr[9]; // array that is returned, array of possible moves(nodes)
  displayBoard(node.nodeBoard);
  int retArrCount = 0;
  char possibleBoard[SIZE][SIZE];
  
  setArrEqual(possibleBoard, b);
  
  for (int i = 0; i<= 2; i++)
  {
    for (int j = 0; j <=2; j++)
    {
      if(node.nodeBoard[i][j] != 'X' && node.nodeBoard[i][j] != 'O')
      {
        //setArrEqual(children[retArrCount].nodeBoard, path[pathCount].nodeBoard);
        setArrEqual(children[retArrCount].nodeBoard, b);
        possibleBoard[i][j] = p.peice;
        children[retArrCount].nodeBoard[i][j] = p.peice;
        setArrEqual(nodes[nodeCount].nodeBoard, possibleBoard);
        
        //Node n = Node();
        //setArrEqual(n.nodeBoard, possibleBoard);
        children[retArrCount].terminalCheck();
        children[retArrCount].val = eval(children[retArrCount].nodeBoard, p);
        setDepth(children[retArrCount]);
        children[retArrCount].parentNode = &node;
        //children[retArrCount] = n;
        children[retArrCount].name = "a";
        
        node.numberOfChildren++;
        
        //cout << nodeNames[nodeCount] << endl;
        //displayBoard(node.children[retArrCount]->nodeBoard);
        nodeCount++;
        retArrCount++;
        setArrEqual(possibleBoard, b);
      }
    }
  }
  
  //return retArr;
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

int resultChildNumber;
Node MINIMAX(Node n, int depth, Player p, int USETHRESH, int PASSTHRESH) // node is position
{
  for(int i = 0; i<9; i++)
  {
      children[i] = Blank;
  }
  Node ret = n;
  Player op; // opposite player
  if (p.peice == 'X')
  {
    op = OMin;
  }
  else
  {
    op = XMax;
  }
  
  if (deepEnough(n, depth) == true)
  {
    cout << "return init 1 " << endl;
    displayBoard(n.nodeBoard);
    return n;
  }
  else
  {
    moveGen(n.nodeBoard, p, n); // puts successors in children[]
    
    if(children[0].name == "Blank")
    {
        cout << "return init" << endl;
        displayBoard(n.nodeBoard);
        //ret = n;
        return n;
    }
    else
    {
      for(int i = 0; i < 9; i++)
      {
        if(children[i].name != "Blank")      
        {
            //cout << "passed" << endl;
            //displayBoard(children[i].nodeBoard);
          Node resultChild = MINIMAX(children[i], depth + 1, op, -PASSTHRESH, -USETHRESH);
          //resultChild = children[i];
          cout << "result child" << endl;
          displayBoard(resultChild.nodeBoard);
          //ret = resultChild;
          n.newVal = -(resultChild.val);
          if(n.newVal > PASSTHRESH)
          {
            PASSTHRESH = n.newVal;
            //path[pathCount] = resultChild;
            ret = resultChild;
            resultChildNumber = i;
          }
          if(PASSTHRESH >= USETHRESH)
          {
            n.val = PASSTHRESH;
            //setArrEqual(path[pathCount].nodeBoard, n.nodeBoard);
            cout << "return h " << endl;
            displayBoard(ret.nodeBoard);
            return ret;
            //return children[resultChildNumber];
          }
          //n.val = PASSTHRESH;
          //path[pathCount] = n;
          n.val = PASSTHRESH;
          //setArrEqual(path[pathCount].nodeBoard, n.nodeBoard);
          cout << "return i" << endl;
          displayBoard(ret.nodeBoard);
          setArrEqual(path[pathCount].nodeBoard, ret.nodeBoard);
          return ret;
          //return children[resultChildNumber];
        }
      }
    }
  }
}
