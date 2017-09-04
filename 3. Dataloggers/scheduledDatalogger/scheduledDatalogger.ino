/*
  Scheduled Datalogger

  Parts required:
  1x MKRZero
  1x GA1A12S202 log-scale light sensor
  1x DHT22 temperature and humidity sensor
*/

// Libraries
#include <SD.h>
#include <RTCZero.h>
#include <DHT.h>

// A1A log-scale light sensor parameters
int logsensorPin = A0;  // Select the input pin
float rawRange = 1024;  // 3.3V
float logRange = 5.0;   // 3.3V = 10^5 lux

// DHT22 parameters
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int chipSelect = SS1;
unsigned long previousTime;

int loadDataCheck;  // Checks if data needs to be loaded.

RTCZero rtc;

// Change these values to set the current initial time.
const byte hours = 9;
const byte minutes = 00;
const byte seconds = 00;

// Change these values to set the current initial date.
const byte day = 1;
const byte month = 8;
const byte year = 17;

// The setup function runs once when you press reset or power the board.
void setup() {
  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  Serial.println("Scheduled DataLog:");

   // See if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present...");
    // Don't do anything more:
    return;

  }
  Serial.println("Card initialized.");

  // When power is supplied to the DHT22 sensor, don't send any instruction to the sensor within one second to pass unstable status.
  delay(1000);
  Serial.println("Initialising DHT22 sensor...");
  dht.begin();

  Serial.println("Initialising log-scale light sensor...");

  Serial.println("Initialising RTC...");
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);

  rtc.setAlarmTime(0, 0, 0);
  rtc.enableAlarm(rtc.MATCH_SS); // alarm attached every minute.

  rtc.attachInterrupt(dataCheck);

  loadDataCheck = 0;

  previousTime = millis();

  Serial.println("System ready.");
}

// The loop function runs over and over again forever.
void loop() {
  unsigned long currentTime = millis();
  if ((currentTime-previousTime) > 5000)
  {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on,
    delay(100);                       // wait,
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off.
    previousTime = millis();
  }
  if (loadDataCheck) logData();
}

void dataCheck(){
  loadDataCheck = 1;
}

void logData(void) {
  int rawValue = analogRead(logsensorPin);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  String dataString = "";
  dataString += "Time: " + getTime() + "\t" + "GA1A Lux: " + String(RawToLux(rawValue)) + "\t" + "Temperature: " + String(temperature) + char(176) + "C\t" + "Humidity: " + String(humidity) + "%";
  // Open the file.
  // Note: only one file can be open at a time, so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // If the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // Print to the Serial port too:
    Serial.println(dataString);
  }
  // If the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  loadDataCheck = 0;
}

float RawToLux(int raw) {
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

String getTime(void) {
  String returnString = "";

  if (rtc.getHours() < 10)
    returnString += "0" + String(rtc.getHours());
  else
    returnString += String(rtc.getHours());

  returnString += ":";

  if (rtc.getMinutes() < 10)
    returnString += "0" + String(rtc.getMinutes());
  else
    returnString += String(rtc.getMinutes());

  returnString += ":";

  if (rtc.getSeconds() < 10)
    returnString += "0" + String(rtc.getSeconds());
  else
    returnString += String(rtc.getSeconds());

  return returnString;
}
