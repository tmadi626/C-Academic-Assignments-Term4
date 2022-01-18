#if !defined(BINGROWSQUARE_H) // include guard
#define BINGROWSQUARE_H

#include "Symbol.h"
#include <iostream>
#include <string>
using namespace std;


class BingrowSquare
{
   Symbol symbol;
   bool covered;
public:
   Symbol getSymbol(void)
   {
      return symbol;
   }
   bool getCovered(void)
   {
      return covered;
   }
   void setCovered(bool covered)
   {
      //cout<<"It is covered, setCovered"<<endl;
      this->covered = covered;
   }
   void setSymbol(Symbol symbol)
   {
      this->symbol = symbol;
   }
   bool operator==(const BingrowSquare &other)
   {
      return ((this->symbol == other.symbol) && (this->covered == other.covered));
   }
};
#endif