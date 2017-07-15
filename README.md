# Knock Block

## What is this repo?
This repo was made to maintain my undergrad project. It is made for personal use but feel free to look around.

## What is the project?
This is the code for an arduino knock based kodi controller. It essentially records knocks in an array and compares them to a predefined set of knocks. If recorded knocks match one of the predefined knocks, then the arsuino sends a signal to Kodi to control it. Apart from an Arduino Uno it uses an Ethernet Shield to communicate with Kodi via it [JSON-RPC API](http://kodi.wiki/?title=JSON-RPC_API)

## Similar knock detector projects exist all over the internet. Why is this special?
The uniqueness of this project lies in the fact that it does not merely count the number of knocks but rather recognises patterns within knocks.

## Can I use this pattern recognition in my projects?
Yeah. To know more about the above mentioned libraries go to the following link:<br>
[PiezoListener](https://bitbucket.org/iarks/piezolistener)<br>
[ArrayValidate](https://bitbucket.org/iarks/arrayvalidate)
