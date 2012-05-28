/*
 -------------------------------------------------------------------------------
 BMP085.h
 BMP085 Project
 
 Initially created by Rowland O'Flaherty on 8/5/11.
 www.rowlandoflaherty.com
 
 Version 1.0
 -------------------------------------------------------------------------------
 */

#ifndef _BMP085_h_
#define _BMP085_h_

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <Arduino.h>

class BMP085
{
    //--------------------------------------------------------------------------
    // Friends
    //--------------------------------------------------------------------------


    //--------------------------------------------------------------------------
    // Friend Overloaded Operators
    //--------------------------------------------------------------------------

	
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

    // Assignment operator
    const BMP085& operator=(const BMP085& rhsObj);


    //--------------------------------------------------------------------------
    // Overloaded Operators
    //--------------------------------------------------------------------------


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

    //--------------------------------------------------------------------------
    // Public Member Variables
    //--------------------------------------------------------------------------


    protected:
    //--------------------------------------------------------------------------
    // Protected Member Functions
    //--------------------------------------------------------------------------


    //--------------------------------------------------------------------------
    // Protected Member Variables
    //--------------------------------------------------------------------------



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
