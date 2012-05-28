BMP085 Project

DESCRIPTION:
    This class is used to interface the Arduino with the BMP085 digital 
    barometric pressure sensor.
 
USAGE:
    The pressure sensor only needs 4 pins hooked up to use: 3.3V, GND, I2C
    (SDA, SCL).
    
    See BMP085.h header file for class information.

NOTES:
    If running on an Arduino that orperates at 5V (e.g. UNO) it is recommended
    to use a logic level converter for the I2C interface because the sensor
    runs at 3.3V. However, it has been found that hooking that the sensor
    operates normally if it is hooked up directly.
 
EXAMPLES:
    Example 1: Initializing sensor and printing current temperature, pressure,
    and altitude.
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
    1.0 - 8/5/11 - Rowland O'Flaherty (rowlandoflaherty.com)
        Initial release.
    