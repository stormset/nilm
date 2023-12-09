#include "WCS.h"


WCS::WCS(dataFunction_t dataFunction, uint16_t mVperA)
{
	_sensitivity = mVperA;
	_readData = dataFunction;
	_midPoint = 0;
}

void WCS::Reset()
{
	ReadADCBuffer(_dataScaled);

	double sum = 0;
	for (int i = 0; i < DATA_RATE; i++)
	{
		sum += _dataScaled[i];
	}
	_midPoint = sum / DATA_RATE;
}

double WCS::getCurrentAC()
{
	ReadADCBuffer(_dataScaled);

	double sum = 0.0;
	for (int i = 0; i < DATA_RATE; i++)
	{
		sum += sq(((_dataScaled[i] - _midPoint) / 1000.0) / ((double)_sensitivity * 0.001));
	}
	return sqrt(sum / DATA_RATE);
}

void WCS::ReadADCBuffer(float *rawData)
{
	for (int i = 0; i < DATA_RATE; i++)
	{
		rawData[i] = _readData();
	}
}
