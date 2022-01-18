#include "BingrowBoard1.h"
#include "BingrowSquare.h"
#include "Symbol.h"

#include <iostream>
#include<vector>
using namespace std;



int BingrowBoard::GetSize(void){
    return currSize;
}

BingrowBoard::BingrowBoard(int n){
    originalSize, currSize = n;
    cout<<"\ncreating a bingo board if size: "<<n<<"\n"<<endl;

   vector<BingrowSquare> temporaryColumn; // a temporary Column to fill the squares

   for (int r = 0; r < n; r++){           //r is the row number

      for (int c = 0; c < n; c++){        //c will be the column number

        BingrowSquare temporarySquare = BingrowSquare();

        if( c == n/2 && r == n/2 ){ //if the square is in the middle of the original board
            Symbol freeSymbol;      // then set it to free
            freeSymbol.setSymbolType(Free);
            temporarySquare.setSymbol( freeSymbol );
            // Symbol ArrowSymbol;  
            // ArrowSymbol.setSymbolType(Arrow);
            // ArrowSymbol.setArrowType(UpperLeft);
            // temporarySquare.setSymbol( ArrowSymbol );
        }
        else{
            temporarySquare.setSymbol(GenerateSymbol(c+1));
        }
        temporaryColumn.push_back(temporarySquare);
      }
      theboard.push_back(temporaryColumn);
      temporaryColumn.clear();
   }
}

BingrowBoard::~BingrowBoard(){}

ostream& operator<<(ostream& os, BingrowSquare &sq){

    if( sq.getSymbol().getSymbolType() == Free ){
        os<<"(FR)";
    }
    else if( sq.getSymbol().getSymbolType() == Arrow){
        if(sq.getSymbol().getArrowType() == UpperLeft){
            os<<"(UL)";
        }
        else if(sq.getSymbol().getArrowType() == UpperRight){
            os<<"(UR)";
        }
        else if(sq.getSymbol().getArrowType() == LowerLeft){
            os<<"(LL)";
        }
        else if(sq.getSymbol().getArrowType() == LowerRight){
            os<<"(LR)";
        }
    }
    if( sq.getSymbol().getSymbolType() == Number){
        os<<sq.getSymbol().getNumber();
    }
    return os;
}

void BingrowBoard::printBoard(){
    
    for( int r = 0; r<currSize; r++ ){//looping through s rows
        int c = 0;          //colomn restarts counting

        //cout<<"r"<<r<<":\t";

        for( c ; c<currSize; c++ ){ //looping through s colomns  
            //theboard[r][c];
            cout<<theboard[r][c]<<"\t";

        }
        cout<<endl;
    }
    cout<<"\nFinished creating "<<currSize<<"x"<< currSize <<" Bingrow Board. Taha is lit\n"<<endl;
}

Symbol BingrowBoard::GenerateSymbol(int col)
{
    Symbol tempSymbol;
    int max = 3*originalSize*(col);
    int min = 3*originalSize*(col-1)+1;

    int randNum = rand()%(max-min + 1) + min;

    if (randNum >= 3*originalSize*currSize)
    {
        tempSymbol.setSymbolType(Arrow);
        if (randNum == 3*originalSize*currSize)
        {
        tempSymbol.setArrowType(UpperLeft);
        }
        else if (randNum == 3*originalSize*currSize+1)
        {
        tempSymbol.setArrowType(UpperRight);
        }
        else if (randNum == 3*originalSize*currSize+2)
        {
        tempSymbol.setArrowType(LowerLeft);
        }
        else
        {
        tempSymbol.setArrowType(LowerRight);
        }
    }
    else
    {
        randNum = (int) (((float) rand()/RAND_MAX*(3*originalSize)));
        tempSymbol.setSymbolType(Number);
        tempSymbol.setNumber(randNum+(1+(col-1)*3*originalSize) );
    }
    return tempSymbol;
}

int main() {
    cout<<"\nProgram started.\n"<<endl;
    BingrowBoard Bingo = BingrowBoard(5);
    Bingo.printBoard();

    return 0;
}