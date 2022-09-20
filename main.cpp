#include <iostream>
#include "backwardChaining.h"

int main()
{
   struct carParts
   {  
     bool broken = false;
     string name;
   };
   
   carParts problem = backwardChaining(); // problem will be the carPart that is broken. 
                                          // problem will be what is passed to the forward chaining function
                                          // if problem.name == "No Problem Found" then a broken part wasn't found
   return 0;
}
