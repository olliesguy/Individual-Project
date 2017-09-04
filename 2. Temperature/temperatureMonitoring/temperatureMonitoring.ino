#include <DHT_U.h>
#include <DHT.h>

// DHT22 Temperature & Humidity sensor setup.
#define DHTPIN 7         // What pin the sensor is connected to
#define DHTTYPE DHT22     // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialise DHT sensor for normal 16mHz Arduino.

// LM35 Temperature sensor setup.
int aref_voltage = 5;
int lm35_Pin = A0;


// The setup function runs once when you press reset or power the board.
void setup() {
    Serial.begin(9600);
    Serial.println("Temperature Monitoring:");

    // When power is supplied to the DHT22 sensor, don't send any instruction to the sensor within one second to pass unstable status.
    delay(1000);
    Serial.println("Initialising DHT22 sensor...");
    dht.begin();

    delay(1000);
    Serial.println("Initialising LM35 sensor...");

    delay(1000);
    Serial.println("System ready.");
}


// The loop function runs over and over again forever.
void loop() {
    delay(2000);
    float humidityDHT = dht.readHumidity();
    float temperatureDHT = dht.readTemperature();

    int tempReading = analogRead(lm35_Pin);                              // raw analog reading
    float mVoltageLM = (tempReading / 1024.0) * (aref_voltage * 1000); // in milliVolts
    float temperatureLM = mVoltageLM / 10;                   // calculates temperature in Celsius with a 500mV offset

    String tempString = "";
    tempString += "LM35 Voltage: " + String(mVoltageLM) + "mV" + "\t" + "LM35 Temperature: " + String(temperatureLM) + char(176) + "C" + "\t" + "DHT22 Temperature: " + String(temperatureDHT) + char(176) + "C" + "\t" + "DHT22 Humidity: " + String(humidityDHT) + "%";
    Serial.println(tempString);

}
