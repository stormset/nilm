#ifndef _ZMPT101B_H
#define _ZMPT101B_H

#include <Arduino.h>

#define ADC_SCALE 4095

typedef float (*dataFunction_t)();

class ZMPT101B {
public:
    ZMPT101B(dataFunction_t dataFunction, float sensitivity);
    void Reset();
    float getVoltageAC(uint16_t frequency = 50, float vRef = 3.3);

private:
    double _midPoint;           // store midpoint of read values (set during calibration), to accomodate to noise
    float _sensitivity;         // ADC sensitivity
	dataFunction_t _readData;   // function pointer to sample voltage sensor
};

#endif // _ZMPT101B_H