#include "RemoteADC.h"

RemoteADC::RemoteADC()
{
	this->adc_read_pin = DEFAULT_REMOTE_ADC_PIN;
	pinMode(this->adc_read_pin, INPUT);
}

RemoteADC::RemoteADC(int pin)
{
	this->adc_read_pin = pin;
	pinMode(this->adc_read_pin, INPUT);
}

float RemoteADC::read_adc() {
	return analogRead(this->adc_read_pin);
}

float RemoteADC::getCurrentValue()
{
	this->current_value = read_adc();
	return this->current_value;
}
