#ifndef OptoCoupler_h
#define OptoCoupler_h

#include <Arduino.h>
#include <inttypes.h>

class IOBridgeLib;

typedef void OptoCouplerCallback(int value);

class OptoCoupler 
{
	friend IOBridgeLib;
private:
	OptoCouplerCallback *onStateChangedCb = nullptr;
	int read_opto_pin = 0;
	int current_state = 0;
	int last_state = 0;
private:
	constexpr OptoCoupler() = default;
	OptoCoupler(int opto_pin);
	void handle();

	void onStateChangedCallback(OptoCouplerCallback *cb);
	int getCurrentState();
};

#endif