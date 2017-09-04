/*
    Square of Velostat with 6 conductive rows and 6 conductive columns
    parsing through this grid by switching indvidual rows/columns to be
    HIGH, LOW, or INPUT (high impedance) to detect location and pressure.
*/

#define numCols 6
int colPins[] = {
    A0, A1, A2, A3, A4, A5
};
#define numRows 6
int rowPins[] = {
    7, 8, 9, 10, 11, 12
};

#define matrixSize numRows*numCols
int sensorValues[matrixSize] = {};


void setup() {
    // Set all rows and columns to INPUT (high impedance):
    for (int i = 0; i < numCols; i++){
        pinMode(colPins[i], INPUT);
    }
    for (int i = 0; i < numRows; i++){
        pinMode(rowPins[i], INPUT);
    }

    Serial.begin(115200);
}


void loop() {
    for (int r = 0; r < numRows; r++) {
        pinMode(rowPins[r], OUTPUT);    // set as OUTPUT
        digitalWrite(rowPins[r], LOW);  // set LOW

        for (int c = 0; c < numCols; c++) {
            pinMode(colPins[c], INPUT_PULLUP);  // set as INPUT with PULLUP RESISTOR
            sensorValues[(r*numCols) + c] = analogRead(colPins[c]);  // read INPUT
            delay(10);

            pinMode(colPins[c], INPUT); // set pin back to INPUT
        }

        pinMode(rowPins[r], INPUT);     // set pin back to INPUT
    }

    // Print the sensor values of the grid to the Serial Monitor:
    for (int i = 0; i < matrixSize; i++) {
        Serial.print(sensorValues[i]);
        if (i < matrixSize-1) Serial.print(",");
    }

    Serial.println();   // Newline
    delay(10);
}
