#pragma once

#include <Arduino.h>

#define LONGPRESS 5000
#define SHORTPRESS 50

class IOBridgeLib;

using ButtonPressedCallback = void(*)(void);

class ButtonHandler
{
	friend IOBridgeLib;
private:
	ButtonPressedCallback button_press_cb = nullptr;
	ButtonPressedCallback button_long_press_cb = nullptr;
	
	bool button_was_pressed = false; // previous state
	int button_pressed_counter = 0; // press running duration
	uint32_t Pin = 0;
private:
	constexpr ButtonHandler(uint32_t pin)
		:Pin(pin)
	{
	}

	ButtonHandler() = default;

	void setup(int type);
	void handle();
	void onPress(ButtonPressedCallback callback);
	void onLongPress(ButtonPressedCallback callback);
};
