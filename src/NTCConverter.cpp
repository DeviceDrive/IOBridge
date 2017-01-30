#include "NTCConverter.h"
#include <math.h>

#define RESISTANCE 10000.0L
#define ADC_BIT 1024

double a_coeff = 0.003354016;
double b_coeff = 2.56524e-4;
double c_coeff = 2.60597e-6;
double d_coeff = 6.32926e-8;

double r_adc;
double t;

NTCConverter::NTCConverter(int pin) {
  this->read_temp_pin = pin;
}

NTCConverter::NTCConverter() {
  this->read_temp_pin = DEFAULT_TEMPERATURE_PIN;
}

void NTCConverter::setup() {
  this->should_read_temperature = false;
}

void NTCConverter::toggleTemperatureRead() {
  this->should_read_temperature = !this->should_read_temperature;
}

void NTCConverter::temperatureHandler() {
  if (this->should_read_temperature) {
    this->current_temperature = ReadCelsius();
    if (this->last_temperature - this->current_temperature >= 1 || this->last_temperature - this->current_temperature <= -1) {
        if(this->temperatureChangedCallback != NULL)
          this->temperatureChangedCallback(this->current_temperature);
        this->last_temperature = this->current_temperature;
    }
  }
}

double NTCConverter::ReadCelsius() {
  r_adc = analogRead(this->read_temp_pin);
  t = (r_adc * RESISTANCE) / (ADC_BIT - r_adc);
  return NTC_temperature_C(t, RESISTANCE);
}

double NTCConverter::ReadKelvin() {
  r_adc = analogRead(this->read_temp_pin);
  t = (r_adc * RESISTANCE) / (ADC_BIT - r_adc);
  return NTC_temperature_K(t, RESISTANCE);
}

void NTCConverter::onTemperatureChanged(TemperatureChangedCallback * temperature_changed_cb) {
  this->temperatureChangedCallback = temperature_changed_cb;
}

double NTCConverter::NTC_temperature_K(double r, double resistance)
{
	float log_r  = log(r/resistance);
	float log_r2 = log_r * log_r;
	float log_r3 = log_r * log_r * log_r;

	return 1.0L / (a_coeff + b_coeff * log_r + c_coeff * log_r2 + d_coeff * log_r3);
}

double NTCConverter::NTC_temperature_C(double r, double resistance)
{
	float log_r  = log(r/resistance);
	float log_r2 = log_r * log_r;
	float log_r3 = log_r * log_r * log_r;

	return (1.0L / (a_coeff + b_coeff * log_r + c_coeff * log_r2 + d_coeff * log_r3))-273.15L;
}
