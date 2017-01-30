#ifndef NTCConverter_h
#define NTCConverter_h

#include <Arduino.h>
#include <inttypes.h>
#include "pindef.h"

typedef void TemperatureChangedCallback(double temperature);

class NTCConverter
{
	public:
    NTCConverter();
    NTCConverter(int pin);
    void setup();
	void temperatureHandler();
    double ReadCelsius();
    double ReadKelvin();
    void toggleTemperatureRead();
	void onTemperatureChanged(TemperatureChangedCallback *temperatureChangedCallback);
  private:
    bool should_read_temperature;
    int read_temp_pin;
	double last_temperature;
	double current_temperature;
	TemperatureChangedCallback *temperatureChangedCallback = NULL;
	double NTC_temperature_K(double r, double resistance);
	double NTC_temperature_C(double r, double resistance);
};
#endif
