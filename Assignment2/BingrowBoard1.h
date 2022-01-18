#if !defined(BINGROWBOARD_H) // include guard
#define BINGROWBOARD_H

#include "BingrowSquare.h"
#include "Symbol.h"
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;

class BingrowBoard
{
   private:
   // YOU WILL HAVE TO ADD YOUR OWN PRIVATE DATA MEMBERS AND MEMBER FUNCTIONS HERE
   vector< vector<BingrowSquare> > theboard;
   int originalSize, currSize;
   
   public:
/*done*/BingrowBoard(int n); // Constructor for board with side length n
/*done*/~BingrowBoard(); // Destructor
   
      void GrowBoard(ArrowType direction); // Grow board in the specified direction
      bool UpdateBoard(Symbol symbol); // Cover all occurences of symbol on board 
   
      // and possibly grow the board if symbol is arrow
      bool WinningBoard(void); // True if winning condition is satisfied, false otherwise
/*done*/int GetSize(void); // Returns the side length of the board

      // After being called, the square corresponding to the row'th row and col'th column
      // will be set to square.  This is only to be used for testing purposes.
      void SetSquare(int row, int col, BingrowSquare square); 

      // Generates a symbol for column col on the board
/*done*/Symbol GenerateSymbol(int col); 

   //printing the Bingrow Board
/*done*/void printBoard();
};
#endif