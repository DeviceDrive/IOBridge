// Led.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct Color 
{
	int red;
	int green;
	int blue;
};

struct Colors 
{
	static constexpr Color RED = {255,0,0};
	static constexpr Color ORANGE = {255,128,0};
	static constexpr Color YELLOW = {255,255,0};
	static constexpr Color GREEN = {0,255,0};
	static constexpr Color BLUE = {0,0,255};
	static constexpr Color CYAN = {0,255,255};
	static constexpr Color MAGENTA = {255,0,255};

};

class IOBridgeLib;

class Led 
{
private:
	friend IOBridgeLib;
	int _pin_red;
	int _pin_green;
	int _pin_blue;

	int current_red = 0;
	int current_green = 0;
	int current_blue = 0;

	bool shouldBlink = false;
	bool blinkVal = false;
	unsigned long blinkInterval = 100;
	unsigned long lastBlink = 0;

	bool isCorssFading = false;
	int crossFadeWait = 5;
	unsigned long lastFade = 0;
	int current_step = 0;
	int stepR = 0;
	int stepG = 0;
	int stepB = 0;

	int calculateStep(int prevValue, int endValue);
	int calculateVal(int step, int val, int i);
	void crossFade();
private:
	Led() = default;
	constexpr Led(int pin_red, int pin_green, int pin_blue)
		:_pin_red(pin_red), _pin_green(pin_green), _pin_blue(pin_blue)
	{
	}
	
	Led(const Led& copy) = default;
	Led& operator = (const Led& copy) = default;
	void setup();
	void handle();
	void setColor(int red, int green, int blue);
	void setColor(int red, int green, int blue, bool remeber);
	void setColor(Color color);
	void setColor(Color color, bool remeber);

	void fadeTo(Color color);
	bool isFading();
	void stopFade();

	void startBlink(unsigned long intervall);
	void stopBlink();
	bool isBlinking();

	Color getColor();
};


#endif

