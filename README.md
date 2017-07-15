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
1. Arduino-Uno
2. Ethernet Shield
3. A Piezo Sensor
4. LM358 Dual OpAmp IC

### Circuit Diagram and working
![CircuitDiagram](https://camo.githubusercontent.com/8640fb891ddfd8c2b2df5d774fd937d076d04943/68747470733a2f2f6c68342e676f6f676c6575736572636f6e74656e742e636f6d2f366463777538502d314547544f5a616f4e654f45734765513855764c394d4459434a50454e5f716b6a5234645650723479574155347034327456433146454b6857334a4432416449515076746d30553d77313932302d68393530)<br>
The piezo sensor is connected to a non-inverting terminal of an OpAmp that produces a mild 3.22 gain (1+100/222). This amplified output is then fed to another OpAmp working as a comparator. The voltage drop across the 100K potentiometer connected to the negetive terminal of the comparator acts as a threshold. The comparator outputs a high voltage only when the voltage at the positive terminal of the comparator is higher than the voltage drop across the 100K pot.<br>
This comparator output is read by the Arduino. A successfully detected knock produces a high at the comparator output. The threshold can be adjusted by adjusting the potentiometer.
The resistor values can be adjusted as per gain and threshold requirements.

### That looks a little complicated. Why not connect the the piezo directly to the Arduino with a 1M resistor in parallel?
We tried that. Infact that is the most common knock sensor example available on the internet. But there are a few potential problems with that approach:
1. It's very inconsistant.
2. We could not control the threshold without changing the actual code and uploading it to the arduino.

### How does the code work?
[placeholder]
