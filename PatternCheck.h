#ifndef av
#define av

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class PatternCheck
{
  public:
    //constructor
    PatternCheck(int *mainArray, int maximumRows,int maximumColumns, int discardingLimit, int averageDiscardingLimit);
    int checkPattern(int *compareArray, int caLen);
  private:
    int _mainRows;
    int _mainColumns;
    int _discardingLimit;
    int _averageDiscardingLimit;
    int *_mainArray;
    int element;
};
#endif

