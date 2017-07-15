#include "ArrayValidate.h"

ArrayValidate::ArrayValidate(int *mainArray, int maximumRows,int maximumColumns, int discardingLimit, int averageDiscardingLimit)
{
  _mainRows=maximumRows;
  _mainColumns=maximumColumns;
  _discardingLimit=discardingLimit;
  _averageDiscardingLimit=averageDiscardingLimit;
  _mainArray=mainArray;
}
int ArrayValidate::validateArray(int *compareArray, int caLen)
{
  int i=0,j=0,element;
  
  int mainArraySingleRowLen=0;
  int possibleIndex=0;

  for(i=0;i<_mainRows;i++)
  {
    mainArraySingleRowLen=0;
    for(j=0;j<_mainColumns;j++)
    {
      element=(*(_mainArray+i*_mainColumns+j));
      if(element>0)
      {
        mainArraySingleRowLen++;
      }
    }
    if(mainArraySingleRowLen==caLen)
    {
      int x=i+1;
      possibleIndex=(possibleIndex*10)+x;
    }
  }

//  Serial.println("---------------------------------possibleIndex--------------------------------");
//  Serial.println(possibleIndex);

  if(possibleIndex==0)
  {
    return 240;
  }
  else
  {
     int totalDifference=0;
     int diff=0;
     int ind=0;
    
     while(possibleIndex!=0)
     {
      ind=possibleIndex%10;
          
      ind--;
      
      //Serial.println("---------------------------------CURRENTLY WORKING WITH INDEX--------------------------------");
      //Serial.println(ind);
      
      for (i=0;i<caLen;i++)
      {        
        diff = abs(compareArray[i] - *(_mainArray+ind*_mainColumns+i));
        
        if (diff > _discardingLimit)
        { 
          // Individual values too far off
          goto label;
        }
        totalDifference += diff;
      }
      // too inaccurate
      if (totalDifference/caLen>_averageDiscardingLimit)
      {
         label: possibleIndex=possibleIndex/10;
                totalDifference=0;
                diff=0;
                ind=0;
      }
      else
      {
//        Serial.println("---------------------------------RETURNED INDEX--------------------------------");
//        Serial.println(ind);
        return ind;     
      }
    }
    return 240;
  }
}
