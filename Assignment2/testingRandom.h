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
      vector<vector<int> > theboard;
      int originalSize, currentSize;

   public:
      // Constructor for board with side length n
      BingrowBoard(int n); 
      
      // Destructor
      ~BingrowBoard();

      //Function to create a board
      void GenerateBoard(int size);                                     

      // Grow board in the specified direction
      void GrowBoard(ArrowType direction); 
      
      // Cover all occurences of symbol on board and possibly grow the board if symbol is arrow
      bool UpdateBoard(Symbol symbol);  

      // True if winning condition is satisfied, false otherwise
      bool WinningBoard(void); 

      // Returns the side length of the board
      int GetSize(void); 

      // After being called, the square corresponding to the row'th row and col'th column
      // will be set to square.  This is only to be used for testing purposes.
      void SetSquare(int row, int col, BingrowSquare square); 
      // Generates a symbol for column col on the board
      Symbol GenerateSymbol(int col);
      
      //Prints the game to the screen
      void printBoard();


      
};
#endif
