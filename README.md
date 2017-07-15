# Knock Block

## What is this repo?
This repo was made to maintain my undergrad project. It is made for personal use but feel free to look around.

## What is the project?
This is the code for an arduino knock based kodi controller. It essentially records knocks in an array and compares them to a predefined set of knocks. If recorded knocks match one of the predefined knocks, then the arsuino sends a signal to Kodi to control it. Apart from an Arduino Uno it uses an Ethernet Shield to communicate with Kodi via it [JSON-RPC API](http://kodi.wiki/?title=JSON-RPC_API)

## Similar knock detector projects exist all over the internet. Why is this special?
The uniqueness of this project lies in the fact that it does not merely count the number of knocks but rather recognises patterns within knocks. So a knock with 3 regularly spaced taps can be differentiated from a knock with 3 taps in some other pattern. 

## Can I use this pattern recognition in my projects?
Yeah. To know more about the above mentioned libraries go to the following link:<br>
[PiezoListener](https://bitbucket.org/iarks/piezolistener)<br>
[ArrayValidate](https://bitbucket.org/iarks/arrayvalidate)

## Tell me more about this project
### Hardware Requirements
a. Arduino-Uno
b. Ethernet Shield
c. A Piezo Sensor
d. LM358 Dual OpAmp IC

### Circuit Diagram
![Placeholde]()

### That looks a little complicated. Why not connect the the piezo directly to the Arduino with a 1M resistor in parallel?
We tried that. Infact that is the most common knock sensor example available on the internet. But there are a few potential problems with that approach:
1. It's very inconsistant.
2. We could not control the threshold without changing the actual code and uploading it to the arduino.

### How does the code work?
[placeholder]
