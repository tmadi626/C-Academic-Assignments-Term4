#if !defined(BINGROWBOARD_H)
#define BINGROWBOARD_H

#include "Symbol.h"
#include "BingrowSquare.h"
#include <deque>
#include <algorithm>
#include <vector>

using namespace std;


class BingrowBoard{
   private:
      vector<vector<BingrowSquare> > theboard;//this vector contians rows and coloumns
      int originalSize, currentSize, rightValues, leftValues, maxURArrow,maxULArrow,maxLRArrow,maxLLArrow; 

   public:

      // Constructor for board with side length n
/*Done*/BingrowBoard(int n);

      // Destructor
/*Done*/~BingrowBoard();

      // Grow board in the specified direction
/*Done*/void GrowBoard(ArrowType direction);

      // Cover all occurences of symbol on board and possibly grow the board if symbol is arrow
/*Done*/bool UpdateBoard(Symbol symbol);// Cover all occurences of symbol on board 

      // True if winning condition is satisfied, false otherwise
      bool WinningBoard(void);

      // Returns the side length of the board
/*Done*/int GetSize(void); 

      // After being called, the square corresponding to the row'th row and col'th column
      // will be set to square.  This is only to be used for testing purposes.
      void SetSquare(int row, int col, BingrowSquare square);

      // Generates a symbol for column col on the board
/*Done*/Symbol GenerateSymbol(int col);
      
      //Prints the game to the screen
/*Done*/void printBoard();

};
#endif
