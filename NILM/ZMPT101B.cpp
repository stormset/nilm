#include "ZMPT101B.h"

ZMPT101B::ZMPT101B(dataFunction_t dataFunction, float sensitivity) {
	_sensitivity = sensitivity;
	_readData = dataFunction;
}

void ZMPT101B::Reset() {
	uint16_t sum = 0;
	for (int i = 0; i < 10; i++) {
		sum += _readData();
	}
	_midPoint = sum / 10.0;
}

float ZMPT101B::getVoltageAC(uint16_t frequency, float vRef) {
	uint32_t period = 1000000 / frequency;
	uint32_t t_start = micros();

	uint32_t Vsum = 0, measurements_count = 0;
	int32_t Vnow;

	while (micros() - t_start < period) {
		Vnow = _readData() - _midPoint;
		Vsum += Vnow * Vnow;
		++measurements_count;
	}

	float Vrms = sqrt(Vsum / measurements_count) / ADC_SCALE * vRef / _sensitivity;
	return Vrms;
}
