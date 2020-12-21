#include "Arduino.h"
#include "WiFi.h"

const int ledPin = 23;

void setup()
{
  // initialize LED digital pin as an output.
  Serial.begin(115200);
  // Wifi connection
  WiFi.begin("pcp", "AnggaMiMi");
  pinMode(ledPin, OUTPUT);
}

void loop()
{
    // check if wifi is connected
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wifi is not connected");
    } else {
        Serial.println("Wifi is connected");
    }

    // turn the LED on (HIGH is the voltage level)
    Serial.println("LED On");
    digitalWrite(ledPin, HIGH);

    // wait for a second
    delay(1000);

    // turn the LED off by making the voltage LOW
    Serial.println("LED OFF");
    digitalWrite(ledPin, LOW);

    // wait for a second
    delay(1000);
}