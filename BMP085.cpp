/*
 -------------------------------------------------------------------------------
 BMP085.cpp
 BMP085 Project
 
 Initially created by Rowland O'Flaherty (rowlandoflaherty.com) on 8/5/11.
 www.rowlandoflaherty.com
 
 Version 1.0
 -------------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "BMP085.h"
#include <Arduino.h>
#include <Wire.h>


//------------------------------------------------------------------------------
// Friends
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Friend Overloaded Operators
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Lifecycle
//------------------------------------------------------------------------------

// Constructors
BMP085::BMP085()
:
_OSS(3),
_pres0(101325),
_Ts(1000) {
	
}


// Destructor
BMP085::~BMP085() {
	
}

// Copy constructor
BMP085::BMP085(const BMP085& srcObj)
{
    copyHelper(srcObj);
}

// Assignment operator
const BMP085& BMP085::operator=(const BMP085& rhsObj) {
    // Self-assignment check
    if (this == &rhsObj)
    {
        return (*this);
    }

    // Free old memory

    // Copy new memory
    copyHelper(rhsObj);

    return (*this);
}

// Copy helper function
void BMP085::copyHelper(const BMP085& srcObj) {
    _AC1 = srcObj._AC1;
    _AC2 = srcObj._AC2;
    _AC3 = srcObj._AC3;
    _AC4 = srcObj._AC4;
    _AC5 = srcObj._AC5;
    _AC6 = srcObj._AC6;
    _B1 = srcObj._B1;
    _B2 = srcObj._B2;
    _MB = srcObj._MB;
    _MC = srcObj._MC;
    _MD = srcObj._MD;
    
    _OSS = srcObj._OSS;
    _UT = srcObj._UT;
    _UP = srcObj._UP;
    _B5 = srcObj._B5;
    
    _pres0 = srcObj._pres0;
    _tempTime = srcObj._tempTime;
    _presTime = srcObj._presTime;
    
    _Ts = srcObj._Ts;
    _temp = srcObj._temp;
    _pres = srcObj._pres;
    _alt = srcObj._alt;
}

//------------------------------------------------------------------------------
// Overloaded Operators
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Public Member Functions
//------------------------------------------------------------------------------
void BMP085::initialize() {
    // Initialize device
    Wire.begin();
    readCalibrationData();
    updateTemperature();
    updatePressure();
}

void BMP085::setOSS(int value) {
    _OSS = (byte)constrain(value,0,3);
}

int BMP085::getOSS() {
    return _OSS;
}

void BMP085::setSamplingTime(int value) {
    switch (_OSS) {
        case 0:
            _Ts = max(value,5);
            break;
        case 1:
            _Ts = max(value,8);
            break;
        case 2:
            _Ts = max(value,14);
            break;
        case 3:
            _Ts = max(value,26);
            break;
    }
}

int BMP085::getSamplingTime() {
    return _Ts;
}

float BMP085::temperature() {
    // Get current temperature
    if (millis() - _tempTime >= max(_Ts,1000) || millis() - _tempTime < 0) {
        updateTemperature();
    }
    return (float)_temp / 10;
}

long BMP085::pressure() {
    // Get current pressure
    if (millis() - _tempTime >= max(_Ts,1000) || millis() - _tempTime < 0) {
        updateTemperature();
    }
    if (millis() - _presTime >= _Ts || millis() - _presTime < 0) {
        updatePressure();
    }
    return _pres;
}

float BMP085::altitude() {
    // Get current altitude
    return _alt;
}

void BMP085::calibrateWithAlt(float alt0) {
    // Calibrate with current altitude (m)
    updateTemperature();
    updatePressure();
    delay(30);
    _pres0 = (float)_pres / pow(1 - alt0 / 44330,5.25588);
    updatePressure();
}

void BMP085::calibrateWithPres(long pres0) {
    // Calibrate with current sea level pressure (Pa)
    _pres0 = pres0;
    updateTemperature();
    updatePressure();
}

//------------------------------------------------------------------------------
// Protected Member Functions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Member Functions
//------------------------------------------------------------------------------
byte BMP085::readByte(byte address) {
    // Read 8 bits or 1 byte out EEPROM registers at the given address
    Wire.beginTransmission(_BMP085Address);
    Wire.write(address);
    Wire.endTransmission();

    Wire.requestFrom((int)_BMP085Address, 1);
    while(!Wire.available());

    return Wire.read();
}

int BMP085::readInt(byte address) {
    byte MSB, LSB;

    // Read out E2PROM registers at the given address
    Wire.beginTransmission(_BMP085Address);
    Wire.write(address);
    Wire.endTransmission();

    // 16 bits or 2 bytes or 1 int
    Wire.requestFrom((int)_BMP085Address, 2);
    while(Wire.available() < 2);

    // MSB first
    MSB = Wire.read();
    LSB = Wire.read();

    return (int)(MSB << 8 | LSB);
}

void BMP085::writeByte(byte address, byte value) {
    // Write 8 bits or 1 byte into E2PROM registers at the given address
    Wire.beginTransmission(_BMP085Address);
    Wire.write(address);
    Wire.write(value);
    Wire.endTransmission();
}

void BMP085::readCalibrationData() {   
    // Read calibration data from the E2PROM of the BMP085
    _AC1 = readInt(0xAA);
    _AC2 = readInt(0xAC);
    _AC3 = readInt(0xAE);
    _AC4 = readInt(0xB0);
    _AC5 = readInt(0xB2);
    _AC6 = readInt(0xB4);
    _B1 = readInt(0xB6);
    _B2 = readInt(0xB8);
    _MB = readInt(0xBA);
    _MC = readInt(0xBC);
    _MD = readInt(0xBE);
}

void BMP085::updateTemperature() {
     // Read uncompensated temperature value
    writeByte(0xF4, 0x2E);
    delay(5);
    _UT = readInt(0xF6);

    // Calculate true temperature
    long X1 = (((long)_UT - (long)_AC6) * (long)_AC5) >> 15;
    long X2 = ((long)_MC << 11) / (X1 + (long)_MD);
    _B5 = X1 + X2;
    _temp = (_B5 + 8) >> 4;

    // Update temperature time
    _tempTime = millis();
}

void BMP085::updatePressure() {
    // Read uncompensated pressure value
    writeByte(0xF4,0x34 + (_OSS << 6));
    delay(2 + (3 << _OSS)); // Wait time depends on oversampling setting 
    long MSB = readByte(0xF6);
    long LSB = readByte(0xF7);
    long XLSB = readByte(0xF8);
    _UP = ((MSB << 16) | (LSB << 8) | XLSB) >> (8 - _OSS);
    
    // Calculate true pressure
    long B6 = (long)_B5 - 4000;    
    long X1 = ((long)_B2 * ((B6 * B6) >> 12)) >> 11;    
    long X2 = (long)_AC2 * B6 >> 11;   
    long X3 = X1 + X2;    
    long B3 = ((((long)_AC1 * 4 + X3) << _OSS) + 2) >> 2;   
    X1 = (long)_AC3 * B6 >> 13;
    X2 = ((long)_B1  * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    unsigned long B4 = (unsigned long)_AC4 * (unsigned long)(X3 + 32768) >> 15;    
    unsigned long B7 = ((unsigned long)_UP - B3) * (50000 >> _OSS);   
    long p;
    if (B7 < 0x80000000) {
        p = (B7 << 1) / B4;
    } else {
        p = (B7 / B4) << 2;
    }    
    X1 = (p >> 8) * (p >> 8);   
    X1 = (X1 * 3038) >> 16;   
    X2 = (-7357 * p) >> 16;    
    _pres = p + ((X1 + X2 + 3791) >> 4);
    
    // Calculate altitude
    calcAltitude();
    
    // Update pressure time
    _presTime = millis();
}

void BMP085::calcAltitude() {
    _alt = 44330 * (1 - pow((float)_pres / (float)_pres0, 1/5.25588));
}
