#if !defined(SYMBOL_H) // include guard
#define SYMBOL_H

enum SymbolType {Number, Free, Arrow};
enum ArrowType {UpperLeft, UpperRight, LowerLeft, LowerRight};

class Symbol
{

private:
   SymbolType symbolType;
   int number;
   ArrowType arrowType; 

public:

   // Various mutators and accessors useful for this Symbol class
   SymbolType getSymbolType(void)
   {
      return symbolType;
   }
   int getNumber(void)
   {
      return number;
   }
   ArrowType getArrowType(void)
   {
      return arrowType;
   }
   void setSymbolType(SymbolType symbolType)
   {
      this->symbolType = symbolType;
   }
   void setNumber(int number)
   {
      this->number = number;
   }
   void setArrowType(ArrowType arrowType)
   {
      this->arrowType = arrowType;
   }

   // Overridden comparison operator
   bool operator==(Symbol other)
   {
      return ((symbolType == other.getSymbolType()) && (number == other.getNumber()) &&
              (arrowType == other.getArrowType()));
   }

};
#endif