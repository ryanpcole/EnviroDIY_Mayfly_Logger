/**************************************************************************
temp-trigger-led.ino

* Written By:  Ryan Cole <ryan.cole@oregonstate.edu>
* Documentation By: Ryan Cole <ryan.cole@oregonstate.edu>
* Creation Date: 2024
* Development Environment: Visual Studio Code - PlatformIO
* Hardware Platform: Stroud Center, EnviroDIY Mayfly Arduino Datalogger

As a simple proof of concept we will use the Mayfly's onboard temperature 
sensor to turn on an LED when a temperature threshold is exceeded.

NOTE: To trigger an ISCO we need a 5v signal. But the digital pins are 3v3. 
There is switched power (3v, 5v or 12v) available from D22. We could try and
use this power pin and one of the jumpers to send a 5v signal for the ISCO.


**************************************************************************/

#include <Arduino.h>
#include <Wire.h>           // This library is included with the Arduino IDE, and allows communication with I2C/TWI devices
#include "Sodaq_DS3231.h"   // Install this library to interact with the Real Time Clock

float TEMP_THRESH = 22.0;   // Temperature threshold (degrees C) to turn on LED
int LEDtime = 1000;   //milliseconds
float current_temp;     //variable to hold the measured temperature (what type does the function return?)
int SWITCHPIN = 22;   // pin to switch power
int LEDPIN = SWITCHPIN;       // LED pin

void setup ()
{
    pinMode(LEDPIN, OUTPUT); // LED pin on header and grove connector
    digitalWrite(LEDPIN, LOW); // initialize the LED pin to low

    pinMode(SWITCHPIN, OUTPUT); // Pin to switch power supply on and off
    digitalWrite(SWITCHPIN, LOW); // initialize this to LOW (no power) 

    Serial.begin(57600); // start up serial connection
    Wire.begin();        // TODO figure out what this is doing
    rtc.begin();         // Start the real-time clock (which has temp sensor)

    Serial.println("EnviroDIY Mayfly: Blink demo with serial temperature");
}

void loop ()
{
    rtc.convertTemperature();              //convert current temperature into registers
    current_temp = rtc.getTemperature();   //read the current temperature
    Serial.print(current_temp, 2); //display the temperature
    Serial.println(" deg C");

    // If temperature is >= threshold then turn on the LED (set pin high)
    // What happens if I set a pin to HIGH that is already HIGH?
    if (current_temp >= TEMP_THRESH) {
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);
    delay(LEDtime);
    digitalWrite(LEDPIN, LOW);
    }
    else {
    // turn LED off:
    digitalWrite(LEDPIN, LOW);
    }

    

    delay(LEDtime);
}
