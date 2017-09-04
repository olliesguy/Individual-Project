/*
  Log-scale Photocell

  Parts required:
  1x Linear Photocell
  1x GA1A12S202 Log-scale Analog Light Sensor
*/

// Log-scale analog sensor setup.
int logsensorPin = A0;  // Select the input pin

float rawRange = 1024;  // 3.3V
float logRange = 5.0;   // 3.3V = 10^5 lux

// Linear light sensor setup.
int photocellPin = A1;
int photocellReading;

// The setup function runs once when you press reset or power the board.
void setup() {
    Serial.begin(9600);

    Serial.println("Light Monitoring:");
    delay(1000);

    Serial.println("Initialising photocell sensor...");
    Serial.println("Initialising log-scale light sensor...");
//    analogReference(EXTERNAL);

    Serial.println("System ready.");
    delay(2000);
}

// The loop function runs over and over again forever.
void loop() {
    // Read the raw value from the sensor.
    int rawValue = analogRead(logsensorPin);
    photocellReading = analogRead(photocellPin);

    String lightString = "";
    lightString += "Photocell: " + String(photocellReading) + "\t" + "GA1A Raw: " + String(rawValue) + "\t" + "GA1A Lux: " + String(RawToLux(rawValue));
    Serial.println(lightString);

    delay(1000);
}

float RawToLux(int raw) {
    float logLux = raw * logRange / rawRange;
    return pow(10, logLux);
}
