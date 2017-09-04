/*
    Square of Velostat with 2 conductive rows and 2 conductive columns
    parsing through this grid by switching indvidual rows/columns to be
    HIGH, LOW, or INPUT (high impedance) to detect location and pressure.
*/

#define numCols 2
int cols[] = {
    A0, A1
};

#define numRows 2
int rows[] = {
    11, 12
};

#define matrixSize numRows*numCols
int sensorValues[4] = {};


void setup() {
    // Set all rows and columns to INPUT (high impedance):
    for (int i = 0; i < numCols; i++){
        pinMode(cols[i], INPUT);
    }
    for (int i = 0; i < numRows; i++){
        pinMode(rows[i], INPUT);
    }

    Serial.begin(9600);
}


void loop() {
    for (int r = 0; r < numRows; r++) {
        pinMode(rows[r], OUTPUT);    // set as OUTPUT
        digitalWrite(rows[r], LOW);  // set LOW

        for (int c = 0; c < numRows; c++) {
            pinMode(cols[c], INPUT_PULLUP);  // set as INPUT with PULLUP RESISTOR
            sensorValues[(r*numCols) + c] = analogRead(cols[c]);  // read INPUT
            delay(10);

            pinMode(cols[c], INPUT); // set pin back to INPUT
        }

        pinMode(rows[r], INPUT);     // set pin back to INPUT
    }

    // Print the sensor values of the grid to the Serial Monitor:
    for (int i = 0; i < matrixSize; i++) {
        Serial.print(sensorValues[i]);
        if (i < matrixSize-1) Serial.print(",");
    }
    Serial.println();   // Newline
    delay(10);
}
