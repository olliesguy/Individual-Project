// ROWS = digital write
// COLS = analog read

#define numCols 16
int colPins[] = {
  9, 10, 11, 12};
#define numRows 16
int rowPins[] = {
  4, 5, 6, 7};

int COMc = A0;  // Read off values from here.
int COMr = 13;  // Apply voltage from here.

// the numbers in here represent the pin numbers on the multiplexer to which the mat is actually connected, and they refer back to the position in the multiChannel array:
int colRef [] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
};
int rowRef [] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
};

int multiChannel[16][4] = {
  {0,0,0,0}, // channel 0 (quite simply, 1 is HIGH and 0 is LOW)
  {1,0,0,0}, // channel 1
  {0,1,0,0}, // channel 2
  {1,1,0,0}, // channel 3
  {0,0,1,0}, // channel 4
  {1,0,1,0}, // channel 5
  {0,1,1,0}, // channel 6
  {1,1,1,0}, // channel 7
  {0,0,0,1}, // channel 8
  {1,0,0,1}, // channel 9
  {0,1,0,1}, // channel 10
  {1,1,0,1}, // channel 11
  {0,0,1,1}, // channel 12
  {1,0,1,1}, // channel 13
  {0,1,1,1}, // channel 14
  {1,1,1,1}  // channel 15
};

//#define matrixSize numRows*numCols
int matrixSize = 1*16;
int sensorValues[16] = {};
int rowCount;

void setup() {
  for(int i = 0; i < 4; i ++){
    pinMode(colPins[i], OUTPUT);  // sets all colPins as output
    pinMode(rowPins[i], OUTPUT);  // "          "             "
  }

  pinMode(COMc, INPUT);   // Columns = INPUT
  pinMode(COMr, OUTPUT);  // Rows = OUTPUT
  digitalWrite(COMr, HIGH);

  Serial.begin(9400);
} //end setup


void loop() {
  // ROWS
  for (int rowCount = 0; rowCount < numRows; rowCount++) {
    for (int r = 0; r < 4; r++) {
      digitalWrite(rowPins[r], multiChannel[rowRef[rowCount]][r]);
    }

    // COLS
    for (int colCount = 0; colCount < numCols; colCount++) {
      for(int c = 0; c < 4; c++){
        digitalWrite(colPins[c], multiChannel[colRef[colCount]][c]);
      }
      sensorValues[(rowCount*numCols) + colCount] = analogRead(COMc);
      delay(10);
    }

//  rowCount++;
//  if (rowCount == numRows) {
//    rowCount = 0;
//    Serial.println();
//  }

    // Print the sensor values of the grid to the Serial Monitor:
    for (int i = 0; i < matrixSize; i++) {
      Serial.print(sensorValues[i]);
      if (i < matrixSize-1) Serial.print(",");
    }

    Serial.println(); // Newline
    delay(10);
  }
}  //end loop
