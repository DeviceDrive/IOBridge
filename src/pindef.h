#ifndef _PINDEF_h
#define _PINDEF_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define SW200_PIN 4
#define SW201_PIN A2

#define MOVEMENT_DETECTOR_READ_PIN A3
#define MOTION_DETECTOR_ENABLE_PIN A1

#define DEFAULT_TEMPERATURE_PIN A4

#define DEFAULT_RED_PIN 10
#define DEFAULT_GREEN_PIN 12
#define DEFAULT_BLUE_PIN 11

#define DEFAULT_RELAY1_REL200_PIN 2
#define DEFAULT_RELAY2_REL201_PIN 3

#define SPIUART_CS_PIN 8

#define DEFAULT_OPTO_1_PIN 13
#define DEFAULT_OPTO_2_PIN A0

#define DEFAULT_REMOTE_ADC_PIN A5

#endif