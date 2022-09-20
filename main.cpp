#include <iostream>
#include "backwardChaining.cpp"

int main()
{
   struct carParts
   {
       bool broken = false;
       string name;
   };
  
  backwardChaining();
  return 0;
}
