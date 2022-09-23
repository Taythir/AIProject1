#include <iostream>
#include "backwardChaining.h"
#include "backwardChaining.cpp"

using namespace std;
int main()
{
   
   carParts problem;
   problem = backwardChaining();  // problem will be the carPart that is broken. 
                                          // problem will be what is passed to the forward chaining function
                                          // if problem.name == "No Problem Found" then a broken part wasn't found
   return 0;
}
