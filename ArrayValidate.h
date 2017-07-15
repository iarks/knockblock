#ifndef av
#define av

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ArrayValidate
{
  public:
    //constructor
    ArrayValidate(int *mainArray, int maximumRows,int maximumColumns, int discardingLimit, int averageDiscardingLimit);
    int validateArray(int *compareArray, int caLen);
  private:
    int _mainRows;
    int _mainColumns;
    int _discardingLimit;
    int _averageDiscardingLimit;
    int *_mainArray;
    int element;
};
#endif

