#include "PiezoListener.h"
PiezoListener::PiezoListener(int statusLED, int piezoSensor, int knockInterval, int knockComplete, int maximumKnocks, bool norm, int rangeStart, int rangeEnd)
{
  //PIN Setup
  statusLED=statusLED;  
  piezoSensor=piezoSensor;
  
  //Knock Configurations
  _knockInterval=knockInterval;
  knockComplete=knockComplete;
  maximumKnocks=maximumKnocks;

  //Normalisation Variables
  norm=norm;
  rangeStart=rangeStart;
  rangeEnd=rangeEnd;
  
  //Other private Variables
  currentIntervalNumber=0; 
  piezoSensorValue=0;
  
  digitalWrite(statusLED, HIGH);
}

int *PiezoListener::listenKnocks()
{
  int i = 0;
  
  //reset the array which holds tap intervals
  for (i=0;i<maximumKnocks-1-1;i++)
  {
    sensorReadings[i]=0;
  }
  
  //control variable for maximum Taps
  currentIntervalNumber=0;

  //Reference time for when this knock started
  int startTime=millis();
  int now=millis();

  //blink LED for visual feedback of registered tap
  digitalWrite(statusLED, LOW);            
  delay(_knockInterval);   // wait for this peak to fade before we listen to the next one.                                 
  digitalWrite(statusLED, HIGH);   
  
  
  //record rest of the intervals between taps
  do
  {
    //listen for the next tap or wait for timeout
    piezoSensorValue = digitalRead(piezoSensor);
    if (piezoSensorValue == HIGH)//then a tap has been recorded
    {                   
      //Serial.println("tap detected");
      now=millis();
      sensorReadings[currentIntervalNumber] = now-startTime; //record the interval between the current tap and the previous tap
      currentIntervalNumber++;    //keeping track of array cells and number of recorded taps. Note that number of detected taps = currentIntervalNumber+1
      startTime=now;              //move the reference time
      
      //visual feedback of registered tap
      digitalWrite(statusLED, LOW);            
      delay(_knockInterval);   // wait for this peak to fade before we listen to the next one.                                 
      digitalWrite(statusLED, HIGH);   
    }
    now=millis();//record current time to check if timeout has occured
  }while ((now-startTime < knockComplete) && (currentIntervalNumber < maximumKnocks-1));

  //Now that the entire array has been recorded, we need to sent it back
  if(norm==false)//Means we are not normalising
  {
    //return the array as is
    return sensorReadings;
  }
  else//means we will have to compress
  {
    //Need to pick out the maximum interval to act as a compression reference
  
    int maxTapInterval=0;
    for(i=0;i<=currentIntervalNumber;i++)
    {
      if(sensorReadings[i]>maxTapInterval)
      {
        maxTapInterval=sensorReadings[i];
      }
    }

    //compress the array
    for (i=0;i<maximumKnocks-1-1;i++)
    { 
      // Normalize the collected times
      sensorReadings[i]= map(sensorReadings[i],0, maxTapInterval, rangeStart, rangeEnd); 
    }
    
    //return compressed array
    return sensorReadings;
  }
}

int PiezoListener::getSize()
{
  return this->currentIntervalNumber;
}
