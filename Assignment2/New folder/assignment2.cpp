#include "BingrowBoard.h"
#include "BingrowSquare.h"
#include "Symbol.h"
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

BingrowBoard::BingrowBoard(int n){
   originalSize = n;//originalSize: Original size of the board.
   currentSize = n; //currentSize: Current size of the board - changes after expantion.
   rightValues  = n;//rightValues: Right values after the original board. 
   leftValues = 0; //leftValues: Left values after the original board.
   maxURArrow = 0; maxULArrow = 0; maxLRArrow = 0; maxLLArrow = 0;
   //maxURArrow: Maximum arrow of this type
   //maxULArrow: Maximum arrow of this type
   //maxLRArrow: Maximum arrow of this type
   //maxLLArrow: Maximum arrow of this type

   vector<BingrowSquare> squareRow;

   for (int r = 0; r < n; r++){     //r is the row number
      for (int c = 0; c < n; c++){  //c will be the column number
         BingrowSquare square = BingrowSquare();
         if ( (r == (n/2) ) && (c == (n/2) ) ){
            Symbol Freespace;
            Freespace.setSymbolType(Free);
            square.setSymbol(Freespace);
            square.setCovered(true);
         }
         else{
            square.setSymbol(GenerateSymbol(c+1)); 
            square.setCovered(false);
         }
         squareRow.push_back(square); //adding column elements into rows
      }
      theboard.push_back(squareRow); //adding the rows into a vector
      squareRow.clear();
   }
}

BingrowBoard::~BingrowBoard(){}

bool BingrowBoard::WinningBoard(){
   vector<BingrowSquare> squaresHorizantal;  //vector to store the squares that are covered horizantally
   vector<BingrowSquare> squaresVertical;  //vector to store the squares that are covered Vertically

   vector<BingrowSquare> squaresDiagonallyLR;   //vector to store the squares that are covered Diagonally from Left to Right
   vector<BingrowSquare> squaresDiagonallyRL;   //vector to store the squares that are covered Diagonally from Right to Left

   for(int r = 0; r<currentSize; r++){    //checking Horizantally and vertically if squares are covered
      
      for(int c = 0; c<currentSize; c++){
         if(theboard[r][c].getCovered() == true){
            //add it in a list
            squaresHorizantal.push_back(theboard[r][c]);
         }
         if(theboard[c][r].getCovered() == true){
            //add it in a list
            squaresVertical.push_back(theboard[c][r]);
         }
      }
      if( squaresHorizantal.size() >= 5 || squaresVertical.size() >= 5){
         return true;
      }
      squaresHorizantal.clear();
      squaresVertical.clear();
   }

      int rT = currentSize-1;
   for(int rO = 0; rO<currentSize; rO++){
      
      if(theboard[rO][rO].getCovered() == true){
         squaresDiagonallyLR.push_back(theboard[rO][rO]); //add it in a list
      }
      if(theboard[rO][rT].getCovered() == true){
         squaresDiagonallyRL.push_back(theboard[rO][rT]); //add it in a list
      }

      if( squaresDiagonallyLR.size() >= 5 || squaresDiagonallyRL.size() >= 5){
         return true;
      }
      rT--;
   }
   squaresDiagonallyLR.clear();
   squaresDiagonallyRL.clear();

   return false;
}

void BingrowBoard::GrowBoard(ArrowType direction){
   vector<BingrowSquare> squareRow;

   if(direction == UpperLeft && maxULArrow<2){
      ++currentSize;
      ++maxULArrow;
      for(int c = leftValues; c < currentSize; c++){  // adding coloumn elemens to the first row 
         BingrowSquare square = BingrowSquare();
         square.setSymbol(GenerateSymbol( c ));
         squareRow.push_back(square); // adding the coloumns to a row
      }
      for(int r = 0; r < theboard.size(); r++){ // adding coloumn element to every row's begining
         BingrowSquare square = BingrowSquare();
         square.setSymbol( GenerateSymbol( (leftValues) ) );
         theboard.at(r).insert( theboard.at(r).begin(), square ); // the error is here
      }
      theboard.insert(theboard.begin(), squareRow);//adding the row of coloumn elements first row
      --leftValues;
   }
   if(direction == UpperRight && maxURArrow<2){
      ++currentSize;
      ++rightValues;
      ++maxURArrow;
      for(int c = 0; c < rightValues; c++){  // adding coloumn elemens to the first row
         BingrowSquare square = BingrowSquare();
         square.setSymbol(GenerateSymbol(  c+1 ));
         squareRow.push_back(square); // adding the coloumns to a row
      }
      for(int r = 0; r < theboard.size(); r++){ // adding coloumn elemens to every row's ending 
         BingrowSquare square = BingrowSquare();
         square.setSymbol(GenerateSymbol( theboard.at(r).size()+1 ));
         theboard.at(r).push_back(square);
      }
      theboard.insert(theboard.begin(), squareRow);//adding the row of coloumn elements first row
   }
   if(direction == LowerLeft && maxLLArrow<2){
      ++currentSize;
      ++maxLLArrow;
      for(int c = leftValues; c < currentSize; c++){  // adding coloumn elemens to the first row 
         BingrowSquare square = BingrowSquare();
         square.setSymbol(GenerateSymbol( c ));
         squareRow.push_back(square); // adding the coloumns to a row
      }
      for(int r = 0; r < theboard.size(); r++){ // adding coloumn element to every row's begining
         BingrowSquare square = BingrowSquare();
         square.setSymbol( GenerateSymbol((leftValues)));
         theboard.at(r).insert( theboard.at(r).begin(), square );
      }
      theboard.insert(theboard.end(), squareRow);//adding the row of coloumn elements first row
      --leftValues; 
   }
   if(direction == LowerRight && maxLRArrow<2){
      ++currentSize;
      ++rightValues;
      ++maxLRArrow;
      for(int c = 0; c < rightValues; c++){  // adding coloumn elemens to the first row 
         BingrowSquare square = BingrowSquare();
         square.setSymbol(GenerateSymbol(c+1));
         squareRow.push_back(square); // adding the coloumns to a row
      }
      for(int r = 0; r < theboard.size(); r++){ // adding coloumn elemens to every row's ending 
         BingrowSquare square = BingrowSquare();
         square.setSymbol(GenerateSymbol( theboard.at(r).size()+1 ));
         theboard.at(r).push_back(square);
      }
      theboard.insert(theboard.end(), squareRow); //adding the row of coloumn elements last row
   }
   // add the maxURArrow,maxULArrow,maxLRArrow,maxLLArrow;  make them equale to 0
   squareRow.clear();
}

bool BingrowBoard::UpdateBoard(Symbol symboll){// Cover all occurences of symbol on board and print the boad
   for(int r = 0; r < theboard.size(); r++){

      for(int c = 0; c < theboard.at(r).size() ; c++){
         BingrowSquare &tempSq = theboard[r][c];

         if( (tempSq.getSymbol().getSymbolType() == symboll.getSymbolType() ) ){

            if( tempSq.getSymbol().getNumber() ==  symboll.getNumber() && symboll.getSymbolType() ==Number){ // if it is a number
               tempSq.setCovered(true);
            }
            else if(tempSq.getSymbol().getArrowType() ==  symboll.getArrowType()  && symboll.getSymbolType() ==Arrow){ // if it is an arrow
               tempSq.setCovered(true);
               this->GrowBoard(tempSq.getSymbol().getArrowType()); // passes in an arrow and it grows it

            }
         }
      }
   }
   return true;
}

int BingrowBoard::GetSize(void){
   return currentSize;
}

Symbol BingrowBoard::GenerateSymbol(int col)
{
  Symbol squareSymbol;
  int randNum = (int) ( ( (float) rand()/RAND_MAX*(3*originalSize*currentSize+4) ) );

  if (randNum >= 3*originalSize*currentSize)
  {
     squareSymbol.setSymbolType(Arrow);
     if (randNum == 3*originalSize*currentSize)
     {
        squareSymbol.setArrowType(UpperLeft);
     }
     else if (randNum == 3*originalSize*currentSize+1)
     {
        squareSymbol.setArrowType(UpperRight);
     }
     else if (randNum == 3*originalSize*currentSize+2)
     {
        squareSymbol.setArrowType(LowerLeft);
     }
     else 
     {
        squareSymbol.setArrowType(LowerRight);
     }
  }
  else
  {
     randNum = (int) (((float) rand()/RAND_MAX*(3*originalSize)));
     squareSymbol.setSymbolType(Number);
     squareSymbol.setNumber(randNum+1+(col-1)*3*originalSize);
  }
  return squareSymbol;
}

void BingrowBoard::SetSquare(int row, int col, BingrowSquare square){
   theboard[row][col] = square;
}