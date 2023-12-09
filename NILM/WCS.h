#ifndef _WCS_H
#define _WCS_H


#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define _WCS1800  66 // sensitivity
#define DATA_RATE  76 // data rate

typedef float (*dataFunction_t)();

class WCS
{
public:
    WCS(dataFunction_t dataFunction, uint16_t mVperA);
    void Reset();
    double getCurrentAC();
private:
    uint16_t _sensitivity;         // CT sensitivity (in mV/A)
	double _midPoint;              // store midpoint of read values (set during calibration), to accomodate to noise
    float _dataScaled[DATA_RATE];  // accumulates values for averaging (used to balance ADC (SPS) and serial throughput)
    dataFunction_t _readData;      // function pointer to sample CT voltage

    void ReadADCBuffer(float* rawData);
};

#endif // _WCS_H
