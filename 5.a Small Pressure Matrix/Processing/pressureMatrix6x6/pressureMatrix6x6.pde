/*
    Reads analog inputs and visualises them by drawing a grid to represent location,
    and using grayscale shading of each square to represent pressure value.

    Code based on Tom Igoe's Serial Graphing Sketch:
    >> http://wiki.processing.org/w/Tom_Igoe_Interview
*/

import processing.serial.*;

Serial myPort;  // the serial port.
int numRows = 6;
int numCols = 6;
int maxNumberOfSensors = numRows*numCols;
float[] sensorValue = new float[maxNumberOfSensors];    // Global variable for storing mapped sensor values.
float[] previousValue = new float[maxNumberOfSensors];  // Array of previous values.
int rectSize = 100;
int averageMIN = 150;
int averageMAX = 300;


void setup() {
    size(600,600);          // Define the window size.
    println(Serial.list()); // list all the available serial ports.
    String portName = Serial.list()[0];
    myPort = new Serial(this, portName, 115200);
    myPort.clear();
    myPort.bufferUntil('\n');   // don't generate a serialEvent() until you get a newline (\n) byte.
    background(255);            // set initial background.
    smooth();                   // turn on antialiasing.
    rectMode(CORNER);
}


void draw() {
    // Draw a rectangle for each sensor value and shade to grayscale.
    for (int c = 0; c < numCols; c++) {
        for (int r = 0; r < numRows; r++) {
            fill(sensorValue[(r*numCols) + c]);
            rect(c*rectSize, r*rectSize, rectSize, rectSize);
        }
    }
}


void serialEvent(Serial myPort) {
    String inString = myPort.readStringUntil('\n'); // get the ASCII string.

    if (inString != null) {         // if it's not empty.
        inString = trim(inString);  // trim off any whitespace.
        int incomingValues[] = int(split(inString, ","));;  // convert to an array of ints.

        if (incomingValues.length <= maxNumberOfSensors && incomingValues.length > 0) {
            for (int i = 0; i < incomingValues.length; i++) {
                // Map the incoming values (0 to 1023) to an appropriate grayscale range (0-255):
                sensorValue[i] = map(incomingValues[i], averageMIN, averageMAX, 0, 255);
            }
        }
    }
}


void keyPressed(){
  if (key == ' ')
    saveFrame();
}