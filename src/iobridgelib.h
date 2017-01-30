// iobridgelib.h

#ifndef _IOBRIDGELIB_h
#define _IOBRIDGELIB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pindef.h"

#include "Led.h"
#include "ButtonHandler.h"
#include "MotionDetector.h"
#include "NTCConverter.h"
#include "RelayControl.h"
#include "SpiUart.h"
#include "OptoCoupler.h"
#include "RemoteADC.h"
#include <SPI.h>

class IOBridgeLib
{
 private:
	 Led led_controller;
	 
	 ButtonHandler button_handler_sw200_controller;
	 ButtonHandler button_handler_sw201_controller;

	 MotionDetector motion_detector_controller;

	 NTCConverter ntc_controller;

	 RelayControl relay_controller;

	 OptoCoupler opto_one_controller;
	 OptoCoupler opto_two_controller;

	 RemoteADC remote_adc_controller;

 public:
	void init();
	void handle();

#pragma region Callbacks
	void set_button_sw200_press_callback(ButtonPressedCallback * cb);
	void set_button_sw201_press_callback(ButtonPressedCallback * cb);

	void set_button_sw200_longpress_callback(ButtonPressedCallback * cb);
	void set_button_sw201_longpress_callback(ButtonPressedCallback * cb);

	void set_motion_detector_on_motion_callback(MotionDetectedCallback *cb);
	void set_motion_detector_on_no_motion_callback(MotionDetectedCallback *cb);

	void set_temperature_temperature_changed_callback(TemperatureChangedCallback *cb);

	void set_opto_one_state_changed_callback(OptoCouplerCallback *cb);
	void set_opto_two_state_changed_callback(OptoCouplerCallback *cb);
#pragma endregion

#pragma region LED

	void led_setColor(int red, int green, int blue);
	void led_setColor(int red, int green, int blue, bool remember);
	void led_setColor(Color color);
	void led_setColor(Color color, bool remember);
	void led_fadeTo(Color color);
	bool led_isFading();
	void led_stopFade();
	void led_startBlink(unsigned long interval);
	void led_stopBlink();
	bool led_isBlinking();
	Color led_getColor();

#pragma endregion

#pragma region Relays
	void relay_set_relay1_on();
	void relay_set_relay1_off();
	void relay_set_relay2_on();
	void relay_set_relay2_off();
	void relay_set_relay1_toggle();
	void relay_set_relay2_toggle();
	bool relay_get_relay1();
	bool relay_get_relay2();
#pragma endregion

#pragma region Motion detector
	void motion_set_movement_levels(float low, float high);
	void motion_enable_movement_sensor();
	void motion_disable_movement_sensor();
	float motion_get_current_movement();
#pragma endregion

#pragma region NTC Temperature
	void temp_toggle_temperature_read();

	double temp_read_celsius();
	double temp_read_kelvin();
#pragma endregion

#pragma region OptoCouplers
	int opto_one_get_current_state();
	int opto_two_get_current_state();
#pragma endregion

#pragma region Remote ADC
	float adc_get_current_value();
#pragma endregion

};

extern IOBridgeLib Iobridgelib;

#endif

