/*
 -------------------------------------------------------------------------------
 BMP085Example.ino
 BMP085 Project
 
 CONNECTIONS:
    VCC to 3.3V
    GND to GND
    SDA to A4
    SCL to A5
 
 Initially created by Rowland O'Flaherty on 8/5/11.
 www.rowlandoflaherty.com
 
 Version 1.0
 -------------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
// Includes and Defines
//------------------------------------------------------------------------------
#include <Arduino.h>
#include <BMP085.h>
#include <Wire.h>


//------------------------------------------------------------------------------
// Helper Function Declarations
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Global Varible Declarations
//------------------------------------------------------------------------------
BMP085 bmp;


//------------------------------------------------------------------------------
// Setup Function - Initializes Arduino
//------------------------------------------------------------------------------
void setup()
{
    pinMode(13, OUTPUT);

    Serial.begin(9600);
    bmp.initialize();
    pinMode(13, OUTPUT);

    // Initial
    Serial.println("Initial Reading");
    Serial.print("Temperature: ");
    Serial.print(bmp.temperature(),2);
    Serial.println(" deg C");
    
    Serial.print("Pressure: ");
    Serial.print(bmp.pressure());
    Serial.println(" Pa");
    
    Serial.print("Altitude: ");
    Serial.print(bmp.altitude(),2);
    Serial.println(" m\n");
    
    
    // Set with current pressure
    bmp.calibrateWithPres(101700);
    
    Serial.println("Set with current pressure of 101700");
    Serial.print("Temperature: ");
    Serial.print(bmp.temperature(),2);
    Serial.println(" deg C");
    
    Serial.print("Pressure: ");
    Serial.print(bmp.pressure());
    Serial.println(" Pa");
    
    Serial.print("Altitude: ");
    Serial.print(bmp.altitude(),2);
    Serial.println(" m\n");
    
    // Set with current altitude
    bmp.calibrateWithAlt(270);
    
    Serial.println("Set with current altitude of 307");
    Serial.print("Temperature: ");
    Serial.print(bmp.temperature(),2);
    Serial.println(" deg C");
    
    Serial.print("Pressure: ");
    Serial.print(bmp.pressure());
    Serial.println(" Pa");
    
    Serial.print("Altitude: ");
    Serial.print(bmp.altitude(),2);
    Serial.println(" m\n");
    
    // Set OSS to 3
    bmp.setOSS(3);
    
    Serial.println("Set with OSS to 3");
    Serial.print("Temperature: ");
    Serial.print(bmp.temperature(),2);
    Serial.println(" deg C");
    
    Serial.print("Pressure: ");
    Serial.print(bmp.pressure());
    Serial.println(" Pa");
    
    Serial.print("Altitude: ");
    Serial.print(bmp.altitude(),2);
    Serial.println(" m\n");
}

//------------------------------------------------------------------------------
// Loop Function - Arduino Program Loop
//------------------------------------------------------------------------------
void loop()
{
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(100);
    
    Serial.println("Updated numbers");
    Serial.print("Temperature: ");
    Serial.print(bmp.temperature(),2);
    Serial.println(" deg C");
    
    Serial.print("Pressure: ");
    Serial.print(bmp.pressure());
    Serial.println(" Pa");
    
    Serial.print("Altitude: ");
    Serial.print(bmp.altitude(),2);
    Serial.println(" m\n");
}

//------------------------------------------------------------------------------
// Helper Functions
//------------------------------------------------------------------------------


