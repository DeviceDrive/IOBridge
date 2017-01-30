// Led.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct Color {
	int red;
	int green;
	int blue;
};

class Colors {
public:
	static Color RED();
	static Color ORANGE();
	static Color YELLOW();
	static Color GREEN();
	static Color BLUE();
	static Color CYAN();
	static Color MAGENTA();

};

class Led {
private:
	int _pin_red;
	int _pin_green;
	int _pin_blue;

	int current_red;
	int current_green;
	int current_blue;

	bool shouldBlink = false;
	bool blinkVal = false;
	unsigned long blinkInterval;
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
public:
	Led();
	Led(int pin_red, int pin_green, int pin_blue);
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

