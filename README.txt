BMP085 Class
 
DESCRIPTION:
This class is used to interface the Arduino with the BMP085 digital barometric pressure sensor.

FILES:
    BMP085.h
    BMP085.cpp

DEPENDENCIES:
    Arduino.h
    Wire.h
 
CONSTRUCTORS:
    BMP085();    
 
PUBLIC PROPERTIES:
    
PUBLIC METHODS:
    void initialize();
        Initializes the device. Must be done before device can be used.
 
    void setOSS(int value);
        Sets the oversampling setting. See BMP085 documentation for how this affects sampling time, current draw, and RMS noise. Default value is set to 3.
                value - must be an integer between 0 and 3.
 
    int getOSS();
        Gets the current oversampleing setting.
 
    void setSamplingTime(int value);
        Sets the minimum update rate of the device in milliseconds. Minimum update time for temperature is 1000 and minimum for pressure is set by current oversampling setting. See documentation for values. Default value is 1000.
 
    int getSamplingTime();
        Gets current sampling time in milliseconds.
 
    float temperature();
        Returns the current temperature from the device in celcius.
 
    long pressure();
        Returns the current pressure from the device in pascals.
 
    float altitude();
        Returns the current altitude in meters MSL.
 
    void calibrateWithAlt(float alt0);
        Calibrate the device to the altitude of "alt0".
            alt0 - altitude in meters.
 
    void calibrateWithPres(long pres0);
        Calibrate the device to the sea level pressure of "pres0".
            pres0 - sea level pressure in pascals.
 
NOTES:
 
EXAMPLES:
    ---------------------------------------------------------------------------
    #include <Arduino.h>
    #include <BMP085.h>
    BMP085 bmp;
    void setup() {
        Serial.begin(9600);
        bmp.initialize();
        Serial.print(bmp.temperature(),2);
        Serial.print(bmp.pressure());
        Serial.print(bmp.altitude(),2);
    }
    ---------------------------------------------------------------------------

VERSIONS:
    1.0 - 8/5/11 - Rowland O'Flaherty (www.rowlandoflaherty.com)
        Initial release.