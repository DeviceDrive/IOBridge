#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(uint32_t pin)
{
	this->pin = pin;
}

ButtonHandler::ButtonHandler()
{
}

void ButtonHandler::setup(int type)
{
	pinMode(pin, type);
}

void ButtonHandler::handle()
{
	int button_now_pressed = !digitalRead(pin); // pin low -> pressed
													 // Trigger current event
	if (!button_now_pressed && button_was_pressed) {
		if (button_pressed_counter < LONGPRESS) {
			if (button_pressed_counter > SHORTPRESS) {
				if (button_press_cb != NULL) {
					button_press_cb();
				}
			}
		}
		else {
			if (button_long_press_cb != NULL) {
				button_long_press_cb();
			}
		}
	}
	// Tracking button push
	if (button_now_pressed) {
		button_pressed_counter++;
	}
	else {
		button_pressed_counter = 0;
	}
	button_was_pressed = button_now_pressed;
}

void ButtonHandler::onPress(ButtonPressedCallback * callback)
{
	this->button_press_cb = callback;
}

void ButtonHandler::onLongPress(ButtonPressedCallback * callback)
{
	this->button_long_press_cb = callback;
}

