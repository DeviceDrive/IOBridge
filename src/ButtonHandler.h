#pragma once

#include <Arduino.h>

#define LONGPRESS 5000
#define SHORTPRESS 50

typedef void ButtonPressedCallback();


class ButtonHandler{
	
private:
	ButtonPressedCallback *button_press_cb = NULL;
	ButtonPressedCallback *button_long_press_cb = NULL;

	bool button_was_pressed; // previous state
	int button_pressed_counter; // press running duration
	uint32_t pin;

public:
	ButtonHandler(uint32_t pin);
	ButtonHandler();
	void setup(int type);
	void handle();
	void onPress(ButtonPressedCallback * callback);
	void onLongPress(ButtonPressedCallback * callback);
};
