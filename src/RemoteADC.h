#ifndef RemoteAdc_h
#define RemoteAdc_h

#include <Arduino.h>
#include "pindef.h"

class RemoteADC {

private:
	float read_adc();
	int adc_read_pin;
	float current_value;
	float last_value;

public:
	RemoteADC();
	RemoteADC(int pin);

	float getCurrentValue();
};

#endif