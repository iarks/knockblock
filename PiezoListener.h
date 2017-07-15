#ifndef pl
#define pl

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class PiezoListener
{
  public:
    //constructor
    PiezoListener(int statusLED, int piezoSensor, int knockInterval, int knockComplete, int maximumKnocks, bool norm, int rangeStart, int rangeEnd);
    int *listenKnocks();
    int getSize();
  private:
    int sensorReadings[4];
    int currentIntervalNumber,piezoSensorValue,statusLED,piezoSensor,_knockInterval,knockComplete,maximumKnocks,rangeStart,rangeEnd;
    bool norm;
};
#endif

