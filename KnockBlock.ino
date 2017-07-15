/*  This project was made as part of our undergraduate project for the final year
 *  This is the code for a knock based controller for Kodi
 *  The project utilises 2 custom libraries -
 *  The PiezoListener library records intervals between knocks and records them in an array
 *  The PatternCheck library matches the recorded knock pattern to a set of predefined knock patterns
 *   
 *  Pin Definitions
 *  Digital Pin 8: Piezo speaker (connected to ground with 1M pulldown resistor)
 *  Digital Pin 4: Status LED (To visually indicate the state of the block)
 *    
 *  Nomenclature--
 *  Henceforth, a single knock is called a tap
 *  and a consecutive number of taps is referred to as a knock
*/

//Include Libraries
#include <Ethernet.h>
#include "PiezoListener.h"
#include "ArrayValidate.h"

//Pin Definitions
const int piezoSensor = 8;     // Piezo sensor on pin 8.
const int statusLED = 4;       // Status LED

//Tuning Constants
const int discardingLimit = 25;        // If a knock is off by this percentage, the knock fails
const int averageDiscardingLimit = 15; // If a knock is off by this percentage of the knock on an average, the knock fails.
const int tapInterval = 150; // minimum required interval between 2 consecutive taps
const int maximumTaps = 5;   // Maximum number of taps to listen for in a single knock
const int maximumIntervals = maximumTaps-1;      // Maximum array cells to fill
const int maximumTriggers = 4;  // Maximum number of possible triggers. Number of things to to
const int knockComplete = 1200; // Longest time to wait for a knock before the taps are assumed complete

// Variables and objects
int secretCode[maximumTriggers][maximumIntervals] = {{100,  0,   0,  0},
                                                     {100,  45,  0,  0},
                                                     {100,  100, 0,  0},
                                                     {100,  100, 100,0}};  
int *sensorReadings;  //this is an array pointer which holds the intervals between taps in a knock
int piezoSensorValue = 0; // default value of the piezo sensor
int index = 0;  // Index of the identified Array
int currentIntervalNumber=0; //number of individual taps in the current knock

//Ethernet Variables
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192,168,1,4);
IPAddress ip(192, 168, 1, 10);
EthernetClient client;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Program start");

  pinMode(statusLED, OUTPUT);
  
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("Connecting...");

  if (client.connect(server, 8080)) 
  {
    Serial.println("connected");
    digitalWrite(statusLED, HIGH);
  } 
  else 
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    digitalWrite(statusLED, HIGH); 
    delay(1000);
    digitalWrite(statusLED, LOW);
    delay(1000);
    digitalWrite(statusLED, HIGH);
    delay(1000);
    digitalWrite(statusLED, LOW);
    delay(1000);
    digitalWrite(statusLED, HIGH);
    delay(1000);
    digitalWrite(statusLED, LOW);
  }
}

void loop()
{
  piezoSensorValue = digitalRead(piezoSensor);
  
  // Listen For Taps
  if (piezoSensorValue == HIGH)
  {
    //Knock has been detected
    Serial.println("Knock Detected");
    
    // make an object of the piezolistener type. This object contains all info about the current knock
    PiezoListener* p = new PiezoListener(statusLED, piezoSensor, tapInterval, knockComplete, maximumTaps, true, 0, 100);
    
    // allow the object to listen for knocks
    sensorReadings = p->listenKnocks();// the sensorreadings now points to an array which contains all the time intervals between taps for the current knock
    currentIntervalNumber = p->getSize();// gives the number of detected taps
    
//    Serial.println("-----------------THE ARRAY THAT HAS BEEN RECORDED - PRINTING IN LOOP()-------------");
//    for(int i=0;i<currentIntervalNumber;i++)
//    {
//        Serial.println(*(sensorReadings+i));
//    }
//    Serial.println("---------------------------------------------------------------");

    //Now Check if the Array Makes any sense----------------------------------------
    check();

    //delete the knock object because its work is done
    delete p;
  }
}

void check()
{
  ArrayValidate *a = new ArrayValidate(secretCode[0], maximumTriggers, maximumIntervals, discardingLimit, averageDiscardingLimit);
  index = a->validateArray(sensorReadings,currentIntervalNumber);
//  Serial.println("----------------------------------------returned index number---------------------------");
//  Serial.println(index);
  delete a;
  if(index!=240)
  {
    triggerLED(index);
  }
  else
  {
      Serial.println("No matching pattern detected");
      digitalWrite(statusLED, LOW);      // It did not work, so blink the status LED as visual feedback.
      for (int i=0;i<4;i++)
      {          
        digitalWrite(statusLED, HIGH);
        delay(100);
        digitalWrite(statusLED, LOW);
        delay(100);
      }
      digitalWrite(statusLED, HIGH);
  }
}

void triggerLED(int indexNumber)
{
  if(indexNumber==0)//play-pause
  {
    client.println("GET /jsonrpc?request={\"jsonrpc\": \"2.0\", \"method\": \"Player.PlayPause\", \"params\": { \"playerid\": 1 }, \"id\": 1} HTTP/1.1");
    client.println("Host: 192.168.1.3:8080");
    //client.println("Connection: close");
    client.println();
    if (client.available()) 
    {
      char c = client.read();
      Serial.print(c);
    }
    else if (!client.available()) 
    {
      Serial.println("CLIENT FAIL!");
    }
  }
  else if(indexNumber==1)//rewind
  {
    client.println("GET /jsonrpc?request={\"jsonrpc\":\"2.0\",\"method\":\"Player.SetSpeed\",\"params\":{\"playerid\":1,\"speed\":-2 },\"id\":1} HTTP/1.1");
    client.println("Host: 192.168.1.3:8080");
    //client.println("Connection: close");
    client.println();
    if (client.available()) 
    {
      char c = client.read();
      Serial.print(c);
    }
    else if (!client.available()) 
    {
      Serial.println("CLIENT FAIL!");
    }
  }
  else if(indexNumber==2)//forward
  {
    client.println("GET /jsonrpc?request={\"jsonrpc\":\"2.0\",\"method\":\"Player.SetSpeed\",\"params\":{\"playerid\":1,\"speed\":2 },\"id\":1} HTTP/1.1");
    client.println("Host: 192.168.1.3:8080");
    //client.println("Connection: close");
    client.println();
    if (client.available()) 
    {
      char c = client.read();
      Serial.print(c);
    }
    else if (!client.available()) 
    {
      Serial.println("CLIENT FAIL!");
    }
  }
  else if(indexNumber==3)//stop
  {
    client.println("GET /jsonrpc?request={\"jsonrpc\": \"2.0\", \"method\": \"Player.Stop\", \"params\": { \"playerid\": 1 }, \"id\": 1} HTTP/1.1");
    client.println("Host: 192.168.1.3:8080");
//    client.println("Connection: close");
    client.println();
    if (client.available()) 
    {
      char c = client.read();
      Serial.print(c);
    }
    else if (!client.available()) 
    {
      Serial.println("CLIENT FAIL!");
    }
  }
}
