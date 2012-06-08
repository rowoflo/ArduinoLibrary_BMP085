/*
 -------------------------------------------------------------------------------
 BMP085.h
 BMP085 Project
 
 CLASS NAME:
    BMP085
 
 DESCRIPTION:
    This class is used to interface the Arduino with the BMP085 digital
    barometric pressure sensor.
 
 FILES:
    BMP085.h
    BMP085.cpp
 
 DEPENDENCIES:
    Arduino.h
    Wire.h
 
 CONSTRUCTORS:
    BMP085();
 
 METHODS:
    void initialize();
        Initializes the device. Must be done before device can be used.
 
    void setOSS(int value);
        Sets the oversampling setting. See BMP085 documentation for how this
        affects sampling time, current draw, and RMS noise. Default value is
        set to 3.
            value - must be an integer between 0 and 3.
 
    int getOSS();
        Gets the current oversampleing setting.
 
    void setSamplingTime(int value);
        Sets the minimum update rate of the device in milliseconds. Minimum
        update time for temperature is 1000 and minimum for pressure is set
        by current oversampling setting. See documentation for values.
            value - sampleing time value. Default is 1000.
 
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
    Example 1: Initializing sensor and printing current temperature, pressure,
    and altitude.
    ----------------------------------------------------------------------------
    #include <Arduino.h>
    #include <BMP085.h>
    BMP085 bmp;
    void setup() {
        Serial.begin(9600);
        bmp.initialize();
        Serial.println(bmp.temperature(),2);
        Serial.println(bmp.pressure());
        Serial.println(bmp.altitude(),2);
    }
    ----------------------------------------------------------------------------
 
 VERSIONS:
    1.0 - 8/5/11 - Rowland O'Flaherty (rowlandoflaherty.com)
 
 -------------------------------------------------------------------------------
 */

#ifndef _BMP085_h_
#define _BMP085_h_

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <Arduino.h>

class BMP085 {
	
public:
    //--------------------------------------------------------------------------
    // Constants, Enums, and Types
    //--------------------------------------------------------------------------


    //--------------------------------------------------------------------------
    // Lifecycle
    //--------------------------------------------------------------------------

    // Constructors
    BMP085();

    // Destructor
    ~BMP085();

    // Copy constructor
    BMP085(const BMP085& srcObj);

    //--------------------------------------------------------------------------
    // Overloaded Operators
    //--------------------------------------------------------------------------
    // Assignment operator
    const BMP085& operator=(const BMP085& rhsObj);

    //--------------------------------------------------------------------------
    // Public Member Functions
    //--------------------------------------------------------------------------
    void initialize();
    void setOSS(int value);
    int getOSS();
    void setSamplingTime(int value);
    int getSamplingTime();
    float temperature();
    long pressure();
    float altitude();
    void calibrateWithAlt(float alt0);
    void calibrateWithPres(long pres0);

private:
    //--------------------------------------------------------------------------
    // Lifecycle
    //--------------------------------------------------------------------------
    void copyHelper(const BMP085& srcObj);

    //--------------------------------------------------------------------------
    // Private Member Functions
    //--------------------------------------------------------------------------
    byte readByte(byte address); // Read 1 byte from the BMP085 from 
        // the specified address
    int readInt(byte address); // Read 2 bytes or 1 int from the BMP085
        // from the specified address and address + 1
    void writeByte(byte address, byte value); // Write 1 byte to BMP085 at the 
        // specified address
    void readCalibrationData(); // Calibrate BMP085
    void updateTemperature(); // Update temperature value
    void updatePressure(); // Update pressure value
    void calcAltitude(); // Calculate altitude given pressure at sea level

    //--------------------------------------------------------------------------
    // Private Member Variables
    //--------------------------------------------------------------------------
    // Device constant
    static const byte _BMP085Address = 0x77; // I2C address of BMP085

    // Calibration variables
    int _AC1;
    int _AC2;
    int _AC3;
    unsigned int _AC4;
    unsigned int _AC5;
    unsigned int _AC6;
    int _B1;
    int _B2;
    int _MB;
    int _MC;
    int _MD;

    // Device variables
    byte _OSS; // Oversampling setting (0 - 3). Default 0.
    int _UT; // Uncompensated Temperature
    long _UP; // Uncompensated Pressure
    long _B5; // Calculation variable

    // Class variables
    long _pres0; // Pressure at sea level (Pa). Default 101325.
    unsigned long _tempTime; // Time since last temperature update (ms)
    unsigned long _presTime; // Time since last pressure update (ms)

    // User desired variables
    int _Ts; // Sampling time (ms)
    long _temp; // True temperature (0.1 degree C)
    long _pres; // True pressure (Pa)
    float _alt; // True altitude (m)

};

#endif
