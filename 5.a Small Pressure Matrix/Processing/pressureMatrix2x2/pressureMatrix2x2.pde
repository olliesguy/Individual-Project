/*
    Reads analog inputs and visualises them by drawing a grid to represent location,
    and using grayscale shading of each square to represent pressure value.

    Code based on Tom Igoe's Serial Graphing Sketch:
    >> http://wiki.processing.org/w/Tom_Igoe_Interview
*/

import processing.serial.*;

Serial myPort;                                          // The serial port.
int numRows = 2;
int numCols = 2;
int maxNumberOfSensors = numRows*numCols;
float[] sensorValue = new float[maxNumberOfSensors];    // Global variable for storing mapped sensor values.
float[] previousValue = new float[maxNumberOfSensors];  // Array of previous values.
int rectSize = 200;
int averageMIN = 150;
int averageMAX = 300;

void setup () {
  size(600, 600);                             // Define the window size.
  println(Serial.list());                     // List all the available serial ports.
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.clear();
  myPort.bufferUntil('\n');                   // Do NOT generate a serialEvent() until you get a newline (\n) byte.
  background(255);                            // Set initial background.
  smooth();                                   // Turn on antialiasing.
  rectMode(CORNER);
}


void draw () {
  fill(sensorValue[0]);
  rect(width/2-rectSize, height/2-rectSize, rectSize,rectSize);  // top left
  fill(sensorValue[1]);
  rect(width/2, height/2-rectSize, rectSize,rectSize);           // top right
  fill(sensorValue[2]);
  rect(width/2-rectSize, height/2, rectSize,rectSize);           // bottom left
  fill(sensorValue[3]);
  rect(width/2, height/2, rectSize,rectSize);                    // bottom right
}


void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');      // Get the ASCII string.

  if (inString != null) {                              // If it's not empty.
    inString = trim(inString);                         // Trim off any whitespace.
    int incomingValues[] = int(split(inString, ","));  // Convert to an array of integers (ints).

    if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
      for (int i = 0; i < incomingValues.length; i++) {
        // Map the incoming values (0 to  1023) to an appropriate gray-scale range (0-255):
        sensorValue[i] = map(incomingValues[i], averageMIN, averageMAX, 0, 255);
      }
    }
  }
}