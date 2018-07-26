#ifndef RemoteAdc_h
#define RemoteAdc_h

#include <Arduino.h>
#include "pindef.h"

class IOBridgeLib;

class RemoteADC 
{
	friend IOBridgeLib;
private:
	int adc_read_pin;
	float current_value;
	float last_value;
private:
	RemoteADC();
	RemoteADC(int pin);

	float getCurrentValue();
	float read_adc();
};

#endif