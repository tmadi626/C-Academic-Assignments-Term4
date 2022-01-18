#include "testingRandom.h"
#include "Symbol.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

void GenerateNumb(int col, int originalSize, int currentSize){
  int randNum = (int) (((float) rand()/RAND_MAX*(3*originalSize*currentSize+4)));
  if (randNum >= 3*originalSize*currentSize)
  {
     if (randNum == 3*originalSize*currentSize)
     {
        cout<< "(UL)" ;
     }
     else if (randNum == 3*originalSize*currentSize+1)
     {
        cout<< "(UR)" ;
     }
     else if (randNum == 3*originalSize*currentSize+2)
     {
        cout<< "(LL)" ;
     }
     else // if was added, used to be just else
     {
        cout<< "(LR)" ;
     }
  }
  else
  {
     randNum = (int) (((float) rand()/RAND_MAX *(3*originalSize)));
     int num =  randNum+1+(col-1)*3*originalSize;  
     cout<< num ;
  }
}

BingrowBoard::BingrowBoard(int n){
   originalSize = n;
   currentSize = n;

   vector<int> squareoraryRow;

   for (int r = 0; r < n; r++){           //r is the row number
      for (int c = 0; c < n; c++){        //c will be the column number
         int square;

         if ( (r == (n/2) ) && (c == (n/2) ) ){
            cout<< "(F) \t ";
         }
         else{
            GenerateNumb(c+1, originalSize, currentSize); 
            cout<< " \t ";
         }
      }
      cout<< endl;
      
   }
   cout << "Finished creating "<< currentSize <<"x"<< currentSize <<" Bingrow Board\n\n" << endl;
}

BingrowBoard::~BingrowBoard(){
}


int main(){
   int length = 5;
   cout<< "\nProgram Started, board size: "<< length << endl;
   BingrowBoard Bingo = BingrowBoard(length);

   return 0;
}
